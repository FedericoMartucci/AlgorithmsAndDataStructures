#include "juego.h"

void crearJuego(tJuego* juego)
{
    crearLista(&juego->jugadores);
    juego->letras = NULL;
    juego->tableroResp = NULL;
    juego->tiempoRound = 0;
    juego->cantRondas = 0;
    juego->cantJugadores = 0;
    juego->resultados = NULL;
    juego->curl = NULL;
    juego->puntajeGanador = PUNTAJE_INICIAL;      //un numero bastante grande como para que sea el menor puntaje
    juego->modoPrueba = DESACTIVADO;
    inicializarAleatoriedad();
}

int esOpcionValida(char* opcion)
{
    return !(strcmp(opcion, "A") == 0 || strcmp(opcion, "B") == 0 );
}

int esOpcionIniciarJuego(char* opcion)
{
    return strcmp(opcion,"A") == 0;
}

void verificarSiPideModoPrueba(tJuego* juego, char* opcion)
{
    if(strcmp(opcion,"activarModoPrueba") == 0 && juego->modoPrueba == DESACTIVADO)
    {
        juego->modoPrueba = ACTIVADO;
        puts("Modo de prueba activado, ingrese una tecla para continuar.");
        getch();
    }
}

void ingresarLetrasAleatoriamente(char* letras, int cantRondas)         //habria que ver si hay un error de espacio
{
    char abecedario[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;

    for(i = 0; i < cantRondas; i ++)
        letras[i] = obtenerLetraNoRepetidaRandom(abecedario);
}

void ingresarLetrasEnModoPrueba(char* letras, int cantRondas)
{
    int i;

    puts("Modo de prueba. Ingrese las letras en orden.");

    for(i = 0; i < cantRondas; i ++)
    {
        fprintf(stdout, "Letra %d: ", i + 1);
        letras[i]=obtenerLetraPorTeclado();
    }
    puts("Modo de prueba. Ingreso de letras terminado.");
    getch();
    system("cls");
}

void AccionesSiEsModoPrueba(tJuego* juego)
{
    if(juego->modoPrueba == ACTIVADO)
        ingresarLetrasEnModoPrueba(juego->letras,juego->cantRondas);
}

int cargarJuego(tJuego* juego, char* xSecret)
{
    FILE *pfConfig;
    char linea[MAX_LINEA_CONFIG];

    if (cargarCurl(&juego->curl, xSecret) == NO_PUDO_CARGAR)
    {
        juego->codigoError = ERROR_CARGA_CURL;
        return ERROR_CARGA_CURL;
    }

    if(!(pfConfig = fopen("config.txt", "rt")))
    {
        juego->codigoError = ERROR_APERTURA_ARCHIVO;
        return ERROR_APERTURA_ARCHIVO;
    }

    if(fgets(linea, MAX_LINEA_CONFIG, pfConfig))
        sscanf(linea, "Rounds: %d", &juego->cantRondas);

    if(fgets(linea, MAX_LINEA_CONFIG, pfConfig))
        sscanf(linea, "Tiempo por round: %d", &juego->tiempoRound);

    fclose(pfConfig);

    if(juego->cantRondas <= 0 || juego->cantRondas > ('Z'-'A') || juego->tiempoRound <= 0)
    {
        juego->codigoError=ERROR_PARAMETROS;
        return ERROR_PARAMETROS;
    }

    if((juego->letras = malloc(juego->cantRondas * sizeof(char))) == NULL)
    {
        juego->codigoError = MEMORIA_LLENA;
        return MEMORIA_LLENA;
    }

    ingresarLetrasAleatoriamente(juego->letras, juego->cantRondas);

    return TODO_OK;
}

void ingresarJugadores(tJuego* juego)
{
    int numJugador = 1;
    tJugador jugadorActual;

    ingresarNombreJugador(numJugador, &jugadorActual);

    while(*(jugadorActual.nombre) != '0')
    {
        ponerEnPrimero(&juego->jugadores, &jugadorActual, sizeof(tJugador));    ///ingresar en arbol
        juego->cantJugadores ++;
        numJugador ++;
        ingresarNombreJugador(numJugador, &jugadorActual);
    }
}

void ingresarNombreJugador(int numJugador, tJugador* jugadorActual)
{
    fprintf(stdout, "Ingrese el nombre del jugador %d o ingrese '0' para finalizar\n", numJugador);
    scanf("%s", jugadorActual->nombre);

    jugadorActual->turno = numJugador;
    fflush(stdin);

    system("cls");
}

int hayJugadores(const tJuego* juego)
{
    return !listaVacia(&juego->jugadores);          ///arbol vacio
}

int sortearOrdenJugadores(tJuego* juego)
{
    tOrden orden;

    if(juego->modoPrueba == ACTIVADO)         //esto evita sortear la lista, si el modo de prueba esta activado
    {
        ordenarLista(&juego->jugadores, compararTurnos);     ///ordenar arbol
        return TODO_OK;
    }

    if(!inicializarOrden(&orden, juego->cantJugadores))
    {
        juego->codigoError = MEMORIA_LLENA;
        return MEMORIA_LLENA;
    }

    mezclarJugadores(&orden, juego->cantJugadores);
    recorrerLista2(&juego->jugadores, &orden, cambiarTurnos); ///recorrer arbol
    ordenarLista(&juego->jugadores, compararTurnos);         ///ordenar arbol
    liberarOrden(&orden);       //
    return TODO_OK;
}

void mostrarJugadores(tJuego* juego)
{
    puts("Orden de los jugadores.");
    recorrerLista(&juego->jugadores, mostrarJugador);        ///recorrer arbol
    puts("Ingrese alguna tecla para continuar...");
    getch();
    fflush(stdin);
    system("cls");
}


int crearTableroResp(tJuego* juego)
{
    int i;

    juego->tableroResp = (tRespuesta**)malloc(juego->cantJugadores * sizeof(tRespuesta*));

    if(juego->tableroResp == NULL)
    {
        juego->codigoError = MEMORIA_LLENA;
        return MEMORIA_LLENA;
    }

    for(i = 0; i < juego->cantJugadores; i ++)
    {
        juego->tableroResp[i] = (tRespuesta*)malloc(juego->cantRondas * sizeof(tRespuesta));
        if(juego->tableroResp[i] == NULL)
        {
            juego->codigoError = MEMORIA_LLENA;
            return MEMORIA_LLENA;
        }
    }
    juego->resultados = (int*) malloc(juego->cantJugadores * sizeof(int));
    if(juego->resultados == NULL)
    {
        juego->codigoError = MEMORIA_LLENA;
        return MEMORIA_LLENA;
    }

    return TODO_OK;
}

void iniciarJuego(tJuego* juego)
{
    int i;
    int rondaActual;
    char palabra[MAX_PAL];
    tJugador jugadorActual;

    for(i = 0; i < juego->cantJugadores; i ++)
    {
        obtenerDatoPorIndex(&juego->jugadores, &jugadorActual, sizeof(tJugador), i);   /// buscarElementoPorClaveArbol

        fprintf(stdout, "Jugador actual: %s\n", jugadorActual.nombre);
        fprintf(stdout, "Tiempo por round: %d segundos\n", juego->tiempoRound);
        fprintf(stdout, "Ingrese una tecla para comenzar...\n");

        getch();
        fflush(stdin);
        system("cls");

        fprintf(stdout, "Jugador actual: %s\n", jugadorActual.nombre);

        for(rondaActual = 0; rondaActual < juego->cantRondas; rondaActual ++)
        {
            fprintf(stdout, "Ronda %d - Letra %c -\tRespuesta: ", rondaActual + 1, juego->letras[rondaActual]);
            obtenerPalabraDuranteNSegundos(palabra, juego->tiempoRound);
            puts("");
            memcpy(juego->tableroResp[i][rondaActual].palabra, palabra, MAX_PAL);
        }
        puts("Su turno a finalizado, ingrese una tecla para continuar.");
        getch();
        system("cls");
    }
    puts("Juego terminado, ingrese cualquier tecla para continuar.");
    getch();
    system("cls");
}

int evaluarPalabras(tJuego* juego)
{
    int i;
    int rondaActual;
    int cantEnvios = juego->cantJugadores * juego->cantRondas;
    char* palabraActual;
    for(i = 0; i < juego->cantJugadores; i ++)
    {
        for(rondaActual = 0; rondaActual < juego->cantRondas; rondaActual ++)
        {
            printf("Corroborando palabras con curl...[ %d  / %d ]\n", i * juego->cantRondas + (rondaActual + 1), cantEnvios);

            palabraActual = juego->tableroResp[i][rondaActual].palabra;
            if(strcmp(palabraActual, "") == 0)
            {
                juego->tableroResp[i][rondaActual].validez = VERDADERO;
                juego->tableroResp[i][rondaActual].longitud = 0;
            }
            else
            {
                if(tolower(*palabraActual) == tolower(juego->letras[rondaActual]))     //se compara que sean la misma letra
                {
                    enviarPalabra(&juego->curl, palabraActual);
                    switch (obtenerRespuestaPalabra(&juego->curl))
                    {
                    case PALABRA_ENCONTRADA:
                        juego->tableroResp[i][rondaActual].validez = VERDADERO;
                        juego->tableroResp[i][rondaActual].longitud = strlen(palabraActual);
                        break;
                    case PALABRA_NO_ENCONTRADA:
                        juego->tableroResp[i][rondaActual].validez = FALSO;
                        juego->tableroResp[i][rondaActual].longitud = -1;
                        break;
                    default:
                        juego->tableroResp[i][rondaActual].validez = FALSO;
                        juego->tableroResp[i][rondaActual].longitud = -1;
                        juego->codigoError = ERROR_CONEXION_CURL;
                        break;
                    }
                }
                else
                {
                    juego->tableroResp[i][rondaActual].validez = FALSO;
                    juego->tableroResp[i][rondaActual].longitud = -1;
                }
            }
            system("cls");
        }
    }
    return TODO_OK;
}


void determinarPuntos(tJuego* juego)
{
    int rondaActual;
    int i;
    int longMasLarga;

    //calculo el puntaje de cada palabra
    for(rondaActual = 0; rondaActual < juego->cantRondas; rondaActual ++)
    {
        longMasLarga = obtenerValorLongitudMasLarga(juego, rondaActual);
        for(i = 0; i < juego->cantJugadores; i ++)
            juego->tableroResp[i][rondaActual].puntos = calcularPuntos(juego->tableroResp, &juego->tableroResp[i][rondaActual], i, rondaActual, longMasLarga, juego->cantJugadores);
    }

    for(i = 0; i < juego->cantJugadores; i ++)
        juego->resultados[i]=0;     //los inicializa en 0

    for(int rondaActual=0; rondaActual<juego->cantRondas; rondaActual++)    //calculo los puntos de cada jugador
        for(i = 0; i < juego->cantJugadores; i ++)
            juego->resultados[i] += juego->tableroResp[i][rondaActual].puntos;

    for(i = 0; i < juego->cantJugadores; i ++)       //calculo el puntaje ganador
        if(juego->resultados[i] > juego->puntajeGanador)
            juego->puntajeGanador = juego->resultados[i];
}

void imprimirResultados(tJuego* juego)
{
    FILE *pfInforme;
    time_t tiempoTranscurrido = time(NULL);
    struct tm *fechaHora = localtime(&tiempoTranscurrido);
    char nombreArch[TAM_NOMBRE_INFORME];

    snprintf(nombreArch, sizeof(nombreArch), "informe-juego_%4d-%02d-%02d-%02d-%02d.txt",
             fechaHora->tm_year + 1900, fechaHora->tm_mon + 1,
             fechaHora->tm_mday, fechaHora->tm_hour, fechaHora->tm_min);

    if((pfInforme = fopen(nombreArch, "wt")) == NULL)
        juego->codigoError = ERROR_CREACION_ARCHIVO;

    generarImpresion(juego, pfInforme);

    fclose(pfInforme);

    generarImpresion(juego, stdout);
}

void generarImpresion(tJuego* juego, FILE* salida)
{
    int i;
    int rondaActual;
    tJugador jugadorActual;

    fprintf(salida, "LETRA-JUGADOR");
    for(i = 0; i < juego->cantJugadores; i ++)
    {
        obtenerDatoPorIndex(&juego->jugadores, &jugadorActual, sizeof(tJugador), i);   ///buscarArbolPorClave
        fprintf(salida,"\t%-17s",jugadorActual.nombre);
    }

    fprintf(salida,"\n");

    for(rondaActual = 0; rondaActual < juego->cantRondas; rondaActual ++)
    {
        fprintf(salida,"%c:\t\t", juego->letras[rondaActual]);
        for(i = 0; i < juego->cantJugadores; i++)
        {
            fprintf(salida,"%-17s%2d\t",
                    juego->tableroResp[i][rondaActual].palabra,
                    juego->tableroResp[i][rondaActual].puntos);
        }
        fprintf(salida,"\n");
    }

    fprintf(salida,"RESULT:\t\t\t");
    for(i = 0; i < juego->cantJugadores; i ++)
        fprintf(salida,"\t%2d\t\t", juego->resultados[i]);
    fprintf(salida, "\n");

    fprintf(salida, "GANADORES: ");
    for(i = 0; i < juego->cantJugadores; i++)
    {
        if(juego->resultados[i] == juego->puntajeGanador)
        {
            obtenerDatoPorIndex(&juego->jugadores, &jugadorActual, sizeof(tJugador),i);       ///buscar por clave arbol o recorrer
            fprintf(salida,"|%s| ", jugadorActual.nombre);
        }
    }
    fprintf(salida,"\nPUNTAJE GANADOR:%d\n", juego->puntajeGanador);
}


void cerrarJuego(tJuego* juego)
{
    int i;
    ///se libera todo la informacion, tipo vaciar, liberar, free, esto debe ir despues del la funcion
    if(juego->tableroResp != NULL)
        for(i = 0; i < juego->cantJugadores; i ++)
            free(juego->tableroResp[i]);
    free(juego->tableroResp);
    free(juego->resultados);
    free(juego->letras);
    vaciarLista(&juego->jugadores);     ///vaciar arbol
    liberarCurl(&juego->curl);
}

int calcularPuntos(tRespuesta** tableroResp, tRespuesta* actual,
                   int ordenJugador, int rondaActual, int longMasLarga,
                   int cantJugadores)
{

    if(actual->validez == FALSO)
        return -2;
    if(actual->longitud == 0)
        return 0;
    if(actual->longitud == longMasLarga)
    {
        if(hayOtroLargoPeroDiferente(tableroResp, actual, ordenJugador,
                                     rondaActual, longMasLarga, cantJugadores)
           && !esRepetido(tableroResp, actual, ordenJugador, rondaActual, cantJugadores))       //se fija en toda la lista , si hay otro con misma longitud pero diferente palabra
            return 2;
        if(esSegundoRepetido(tableroResp, actual, ordenJugador, rondaActual)) //se fija si ya habia una palabra igual a esta con anterioridad
            return -1;
        return 3;
    }
    if(esRepetido(tableroResp, actual, ordenJugador, rondaActual, cantJugadores))
        return -1;

    return 1;
}

int obtenerValorLongitudMasLarga(tJuego* juego, int rondaActual)  //esto se hace con la funcion recorrer o esas cosas
{
    int mayorLongitud = 0;
    int i;

    for(i = 0; i < juego->cantJugadores; i ++)  //ya que recorre una ronda
        if(juego->tableroResp[i][rondaActual].validez == VERDADERO &&
           juego->tableroResp[i][rondaActual].longitud > mayorLongitud)
            mayorLongitud = juego->tableroResp[i][rondaActual].longitud;
    return mayorLongitud;
}

int hayOtroLargoPeroDiferente(tRespuesta** tableroResp, tRespuesta* actual,
                              int ordenJugador, int rondaActual,
                              int longMasLarga, int cantJugadores)
{
    int i;

    for(i = 0; i < ordenJugador; i ++)
    {
        if(tableroResp[i][rondaActual].validez == VERDADERO &&
           tableroResp[i][rondaActual].longitud == longMasLarga &&
           strcmp(tableroResp[i][rondaActual].palabra, actual->palabra) != 0)
            return SI;
    }

    for(i = ordenJugador + 1; i < cantJugadores; i++)
    {
        if(tableroResp[i][rondaActual].validez == VERDADERO &&
           tableroResp[i][rondaActual].longitud == longMasLarga &&
           strcmp(tableroResp[i][rondaActual].palabra, actual->palabra) != 0)
            return SI;
    }

    return NO;
}

int esRepetido(tRespuesta** tableroResp, tRespuesta* actual, int ordenJugador,
               int rondaActual, int cantJugadores)
{
    int i;

    for(i = 0; i < ordenJugador; i ++)
    {
        if(tableroResp[i][rondaActual].validez == VERDADERO &&
           tableroResp[i][rondaActual].longitud == tableroResp[ordenJugador][rondaActual].longitud &&
           strcmp(tableroResp[i][rondaActual].palabra,actual->palabra) == 0)
            return SI;
    }

    for(int i = ordenJugador + 1; i < cantJugadores; i++)
    {
        if(tableroResp[i][rondaActual].validez == VERDADERO &&
           tableroResp[i][rondaActual].longitud == tableroResp[ordenJugador][rondaActual].longitud &&
           strcmp(tableroResp[i][rondaActual].palabra,actual->palabra) == 0)
            return SI;
    }

    return NO;
}

int esSegundoRepetido(tRespuesta** tableroResp, tRespuesta* actual,
                      int ordenJugador, int rondaActual)
{
    int i;

    for(i = 0; i < ordenJugador; i ++)
    {
        if(tableroResp[i][rondaActual].validez == VERDADERO &&
           tableroResp[i][rondaActual].longitud == actual->longitud &&
           strcmp(tableroResp[i][rondaActual].palabra,actual->palabra) == 0)
            return SI;
    }
    return NO;
}

void inicializarAleatoriedad()
{
    srand(time(NULL));
}

char obtenerLetraNoRepetidaRandom(char* abecedario)
{
    char letraObtenida;
    int desde = 'A';
    int hastaNoIncluido = 'Z' + 1;
    unsigned pos = rand() % (hastaNoIncluido - desde);

    while (abecedario[pos] == '-')
        pos = (pos + 1) % (hastaNoIncluido - desde);

    letraObtenida = abecedario[pos];
    abecedario[pos] = '-';

    return letraObtenida;
}

void informeErrores(int codigoError)
{
    if(codigoError == NO_HAY_ERRORES)
        return;

    switch(codigoError)
    {
    case MEMORIA_LLENA:
        fprintf(stderr, "Error: memoria llena.");
        break;
    case ERROR_APERTURA_ARCHIVO:
        fprintf(stderr, "No se pudo cargar el archivo config.txt correctamente.");
        break;
    case ERROR_CARGA_CURL:
        fprintf(stderr, "No se pudo inicializar CURL.");
        break;
    case ERROR_CONEXION_CURL:
        fprintf(stderr, "***Paso algun error con el retorno de la llamada con CURL\n"
                "Compruebe su codigo x_secret ***");
        break;
    case ERROR_CREACION_ARCHIVO:
        fprintf(stderr, "Hubo un problema al crear el archivo.");
        break;
    case ERROR_PARAMETROS:
        fprintf(stderr, "Los parametros puestos en config.txt son invalidos.");
        break;
    default:
        break;
    }
    puts("Presione una tecla para continuar...");
    getch();
}
