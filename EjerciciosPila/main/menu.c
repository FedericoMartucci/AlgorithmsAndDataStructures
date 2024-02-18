#include "menu.h"
#include "../../PilaDinamica/main/pila.h"

void abrirMenu()
{
    int opcion;

    printf("MENU\n");
    printf("1- Crear/cargar Pila1 por teclado con 5 elementos. Poner los primeros tres elementos de la PilaAux1 y los restantes a otra PilaAux2, ambas inicializadas en null/vacias.\n");
    printf("2- Cargar PilaOrigen por teclado e inicializar en vacio PilaDestino. Pasar todos los elementos de PilaOrigen a la PilaDestino.\n");
    printf("3- Cargar desde teclado Pila1 y pasar a PilaDestino todos aquellos elementos distintos a 3(tres).\n");
    printf("4- Cargar desde taclado PilaOrigen e inicializar (null) la PilaDestino. Pasar los elementos de PilaOrigen a PilaDestino pero deben quedar en el mismo orden.\n");
    printf("5- Cargar desde teclado Pila1. Invertir la pila para que Pila1 contenga los elementos cargados originalmente en orden inverso.\n");
    printf("6- Pasar el primer elemento de la Pila1 a su última posición, dejando los restantes en el mismo orden.\n");
    printf("7- Pasar el último elemento de la Pila1 a su primera posición, dejando los restantes en el mismo orden.\n");
    printf("8- Repartir los elementos de la PilaMazo en la PilaJugador1 y PilaJugador2 en forma alternada.\n");
    printf("9- Comparar la cantidad de elementos de la PilaA y PilaB. Mostrar por pantalla el resultado.\n");
    printf("10- Comparar la cantidad de elementos de la PilaA y PilaB, evaluando si son complemente iguales (en cant de elementos, valores y posiciones). Mostrar por pantalla el resultado.\n");
    printf("11- Suponiendo la existencia de PilaModelo no vacia, eliminar de la Pila1 todos los elementos que sean iguales al tope de la PilaModelo.\n");
    printf("12- Suponiendo la existencia de PilaModelo vacia o no, eliminar de la Pila1 todos los elementos que existan en PilaModelo.\n");
    printf("13- Suponiendo la existencia de PilaLimite, pasar los elementos de la Pila1 que sean >= que el tope de PilaLimite a la PilaMayores y los menores a la pilaMenores.\n");
    do
    {
        printf("Ingrese una opcion:\n");
        scanf("%d", &opcion);
    }
    while(opcion < 1 && opcion > 13);

    switch(opcion)
    {
    case 1:
        puntoUno();
        break;
    case 2:
        puntoDos();
        break;
    case 3:
        puntoTres();
        break;
    case 4:
        puntoCuatro();
        break;
    case 5:
        puntoCinco();
        break;
    case 6:
        puntoSeis();
        break;
    case 7:
        puntoSiete();
        break;
    case 8:
        puntoOcho();
        break;
    case 9:
        puntoNueve();
        break;
    case 10:
        puntoDiez();
        break;
    case 11:
        puntoOnce();
        break;
    case 12:
        puntoDoce();
        break;
    case 13:
        puntoTrece();
        break;
    default:
        return;
    }
}

void puntoUno()
{
    int i;
    int numero;

    tPila pila1;
    tPila pilaAux1;
    tPila pilaAux2;

    crearPila(&pila1);
    crearPila(&pilaAux1);
    crearPila(&pilaAux2);

    for(i = 0; i < 5; i ++)
    {
        printf("Ingrese un numero:\n");
        scanf("%d", &numero);
        if(pilaLlena(&pila1, sizeof(numero)) == OK)
            ponerEnPila(&pila1, &numero, sizeof(numero));
    }
    for(i = 0; i < 2; i ++)
    {
        if(!pilaVacia(&pila1))
        {
            sacarDePila(&pila1, &numero, sizeof(numero));
            if(pilaLlena(&pilaAux2, sizeof(numero)) == OK)
                ponerEnPila(&pilaAux2, &numero, sizeof(numero));
        }
    }
    for(i = 0; i < 3; i ++)
    {
        if(!pilaVacia(&pila1))
        {
            sacarDePila(&pila1, &numero, sizeof(numero));
            if(pilaLlena(&pilaAux1, sizeof(numero)) == OK)
                ponerEnPila(&pilaAux1, &numero, sizeof(numero));
        }
    }
    printf("Pila 1:\n");
    vaciarPilaMostrandoEntero(&pila1);
    printf("Pila Aux 1:\n");
    vaciarPilaMostrandoEntero(&pilaAux1);
    printf("Pila Aux 2:\n");
    vaciarPilaMostrandoEntero(&pilaAux2);

    vaciarPila(&pila1);
    vaciarPila(&pilaAux1);
    vaciarPila(&pilaAux2);

}
void puntoDos()
{
    tPila pilaOrigen;
    tPila pilaDestino;

    crearPila(&pilaOrigen);
    crearPila(&pilaDestino);

    cargarPila(&pilaOrigen);

    volcarPilaEnteroAOtraPila(&pilaOrigen, &pilaDestino);

    printf("Pila Origen:\n");
    vaciarPilaMostrandoEntero(&pilaOrigen);
    printf("Pila Destino:\n");
    vaciarPilaMostrandoEntero(&pilaDestino);

    vaciarPila(&pilaOrigen);
    vaciarPila(&pilaDestino);
}
void puntoTres()
{
    tPila pila1;
    tPila pilaDestino;

    crearPila(&pila1);
    crearPila(&pilaDestino);

    cargarPila(&pila1);

    volcarPilaEnteroAOtraPila(&pila1, &pilaDestino);

    printf("Pila 1:\n");
    vaciarPilaMostrandoEntero(&pila1);
    printf("Pila Destino:\n");
    vaciarPilaMostrandoEntero(&pilaDestino);

    vaciarPila(&pila1);
    vaciarPila(&pilaDestino);
}
void puntoCuatro()
{
    tPila pilaOrigen;
    tPila pilaDestino;
    tPila pilaAux;

    crearPila(&pilaOrigen);
    crearPila(&pilaDestino);
    crearPila(&pilaAux);

    cargarPila(&pilaOrigen);

    volcarPilaEnteroAOtraPila(&pilaOrigen, &pilaAux);
    volcarPilaEnteroAOtraPila(&pilaAux, &pilaDestino);

    printf("Pila Origen:\n");
    vaciarPilaMostrandoEntero(&pilaOrigen);
    printf("Pila Destino:\n");
    vaciarPilaMostrandoEntero(&pilaDestino);
    printf("Pila Aux:\n");
    vaciarPilaMostrandoEntero(&pilaAux);

    vaciarPila(&pilaOrigen);
    vaciarPila(&pilaDestino);
    vaciarPila(&pilaAux);
}
void puntoCinco()
{
    tPila pila1;
    tPila pilaAux1;
    tPila pilaAux2;

    crearPila(&pila1);
    crearPila(&pilaAux1);
    crearPila(&pilaAux2);

    cargarPila(&pila1);

    volcarPilaEnteroAOtraPila(&pila1, &pilaAux1);
    volcarPilaEnteroAOtraPila(&pilaAux1, &pilaAux2);
    volcarPilaEnteroAOtraPila(&pilaAux2, &pila1);

    printf("Pila 1:\n");
    vaciarPilaMostrandoEntero(&pila1);
    printf("Pila Aux 1:\n");
    vaciarPilaMostrandoEntero(&pilaAux1);
    printf("Pila Aux 2:\n");
    vaciarPilaMostrandoEntero(&pilaAux2);

    vaciarPila(&pila1);
    vaciarPila(&pilaAux1);
    vaciarPila(&pilaAux2);
}
void puntoSeis()
{
    int numero;

    tPila pila1;
    tPila pilaAux1;
    tPila pilaAux2;

    crearPila(&pila1);
    crearPila(&pilaAux1);
    crearPila(&pilaAux2);

    cargarPila(&pila1);

    volcarPilaEnteroAOtraPila(&pila1, &pilaAux1);
    if(!pilaVacia(&pilaAux1)){
        sacarDePila(&pilaAux1, &numero, sizeof(numero));
        if(pilaLlena(&pilaAux2, sizeof(numero)) == OK)
            ponerEnPila(&pilaAux2, &numero, sizeof(numero));
    }
    volcarPilaEnteroAOtraPila(&pilaAux1, &pila1);
    if(!pilaVacia(&pilaAux2)){
        sacarDePila(&pilaAux2, &numero, sizeof(numero));
        if(pilaLlena(&pila1, sizeof(numero)) == OK)
            ponerEnPila(&pila1, &numero, sizeof(numero));
    }
    printf("Pila 1:\n");
    vaciarPilaMostrandoEntero(&pila1);
    printf("Pila Aux 1:\n");
    vaciarPilaMostrandoEntero(&pilaAux1);
    printf("Pila Aux 2:\n");
    vaciarPilaMostrandoEntero(&pilaAux2);

    vaciarPila(&pila1);
    vaciarPila(&pilaAux1);
    vaciarPila(&pilaAux2);
}
void puntoSiete()
{
    int numero;

    tPila pila1;
    tPila pilaAux1;
    tPila pilaAux2;

    crearPila(&pila1);
    crearPila(&pilaAux1);
    crearPila(&pilaAux2);

    cargarPila(&pila1);

    if(!pilaVacia(&pila1)){
        sacarDePila(&pila1, &numero, sizeof(numero));
        if(pilaLlena(&pilaAux2, sizeof(numero)) == OK)
            ponerEnPila(&pilaAux2, &numero, sizeof(numero));
    }
    volcarPilaEnteroAOtraPila(&pila1, &pilaAux1);
    if(!pilaVacia(&pilaAux2)){
        sacarDePila(&pilaAux2, &numero, sizeof(numero));
        if(pilaLlena(&pila1, sizeof(numero)) == OK)
            ponerEnPila(&pila1, &numero, sizeof(numero));
    }
    volcarPilaEnteroAOtraPila(&pilaAux1, &pila1);

    printf("Pila 1:\n");
    vaciarPilaMostrandoEntero(&pila1);

    printf("Pila Aux 1:\n");
    vaciarPilaMostrandoEntero(&pilaAux1);

    printf("Pila Aux 2:\n");
    vaciarPilaMostrandoEntero(&pilaAux2);

    vaciarPila(&pila1);
    vaciarPila(&pilaAux1);
    vaciarPila(&pilaAux2);
}
void puntoOcho()
{
    tPila pilaMazo;
    tPila pilaJugador1;
    tPila pilaJugador2;

    crearPila(&pilaMazo);
    crearPila(&pilaJugador1);
    crearPila(&pilaJugador2);

    cargarPila(&pilaMazo);

    volcarPilaEnteroAOtrasPilasAlternando(&pilaMazo, &pilaJugador1, &pilaJugador2);

    printf("Pila Mazo:\n");
    vaciarPilaMostrandoEntero(&pilaMazo);

    printf("Pila Jugador 1:\n");
    vaciarPilaMostrandoEntero(&pilaJugador1);

    printf("Pila Jugador 2:\n");
    vaciarPilaMostrandoEntero(&pilaJugador2);

    vaciarPila(&pilaMazo);
    vaciarPila(&pilaJugador1);
    vaciarPila(&pilaJugador2);
}
void puntoNueve()
{
    int contador;

    tPila pilaA;
    tPila pilaB;

    crearPila(&pilaA);
    crearPila(&pilaB);

    cargarPila(&pilaA);
    cargarPila(&pilaB);

    printf("PilaA:\n");
    contador = vaciarPilaMostrandoEntero(&pilaA);
    printf("Cantidad de elementos PilaA: %d\n", contador);

    printf("PilaB:\n");
    contador = vaciarPilaMostrandoEntero(&pilaB);
    printf("Cantidad de elementos PilaB: %d\n", contador);

    vaciarPila(&pilaA);
    vaciarPila(&pilaB);
}
void puntoDiez()
{
    int comparacion;

    tPila pilaA;
    tPila pilaB;

    crearPila(&pilaA);
    crearPila(&pilaB);

    cargarPila(&pilaA);
    cargarPila(&pilaB);

    comparacion = vaciarPilasComparandoEntero(&pilaA, &pilaB);

    if(comparacion != 0 || pilaA || pilaB)
        printf("Las pilas son distintas\n");
    else
        printf("Las pilas son iguales\n");

    vaciarPila(&pilaA);
    vaciarPila(&pilaB);
}
void puntoOnce()
{

}
void puntoDoce()
{

}
void puntoTrece()
{

}

void cargarPila(tPila* pila)
{
    int numero;


    printf("Ingrese un numero (0 para salir):\n");
    scanf("%d", &numero);
    while(numero != 0)
    {
        if(pilaLlena(pila, sizeof(numero)) == OK)
            ponerEnPila(pila, &numero, sizeof(numero));

        printf("Ingrese un numero (0 para salir):\n");
        scanf("%d", &numero);
    }


}

int vaciarPilaMostrandoEntero(tPila* pila)
{
    int numero;
    int contador = 0;

    while(*pila)
    {
        sacarDePila(pila, &numero, sizeof(numero));
        contador++;
        printf("%d\n", numero);
    }

    return contador;
}

void volcarPilaEnteroAOtraPila(tPila* pilaAVaciar, tPila* pilaALlenar)
{
    int numero;

    while(!pilaVacia(pilaAVaciar))
    {
        sacarDePila(pilaAVaciar, &numero, sizeof(numero));
        if(pilaLlena(pilaALlenar, sizeof(numero)) == OK)
            ponerEnPila(pilaALlenar, &numero, sizeof(numero));
    }
}

void volcarPilaEnteroAOtrasPilasAlternando(tPila* pilaAVaciar,
                                           tPila* pilaALlenar1,
                                           tPila* pilaALlenar2)
{
    int numero;

    while(!pilaVacia(pilaAVaciar))
    {
        sacarDePila(pilaAVaciar, &numero, sizeof(numero));
        if(pilaLlena(pilaALlenar1, sizeof(numero)) == OK)
            ponerEnPila(pilaALlenar1, &numero, sizeof(numero));
        if(!pilaVacia(pilaAVaciar)){
            sacarDePila(pilaAVaciar, &numero, sizeof(numero));
            if(pilaLlena(pilaALlenar2, sizeof(numero)) == OK)
                ponerEnPila(pilaALlenar2, &numero, sizeof(numero));
        }
    }
}

int vaciarPilasComparandoEntero(tPila* pilaA, tPila* pilaB)
{
    int numeroA;
    int numeroB;

    while(*pilaA && *pilaB)
    {
        sacarDePila(pilaA, &numeroA, sizeof(numeroA));
        sacarDePila(pilaB, &numeroB, sizeof(numeroB));
        printf("%d - %d\n", numeroA, numeroB);
        if(compararEntero(numeroA, numeroB) != 0)
            return -1;
    }

    return 0;
}

int compararEntero(int numeroA, int numeroB)
{
    return numeroA - numeroB;
}
