#include "ejercicios.h"
int crearLoteProductosOrdenado()
{
    tProducto productos[] =
    {
        {"P0001", "Descripcion1", "ProveedorA", {12, 10, 2024}, {20, 7, 2026}, 5, 111.1, 222.2},
        {"P0002", "Descripcion2", "ProveedorA", {21, 2, 2024}, {15, 6, 2026}, 50, 222.2, 331.2},
        {"P0003", "Descripcion3", "ProveedorB", {14, 5, 2024}, {21, 2, 2026}, 45, 333.3, 456.2},
        {"P0004", "Descripcion4", "ProveedorC", {15, 11, 2024}, {17, 12, 2026}, 12, 112.1, 265.2},
        {"P0005", "Descripcion5", "ProveedorA", {1, 10, 2024}, {7, 11, 2026}, 13, 1132.1, 4355.2},
        {"P0006", "Descripcion6", "ProveedorB", {2, 12, 2024}, {9, 3, 2026}, 1, 1222.1, 6654.2},
        {"P0007", "Descripcion7", "ProveedorC", {13, 1, 2024}, {24, 8, 2026}, 27, 433.1, 1231.2},
        {"P0008", "Descripcion8", "ProveedorA", {29, 1, 2024}, {31, 10, 2026}, 93, 554.1, 587.2},
        {"P0009", "Descripcion9", "ProveedorC", {30, 11, 2024}, {12, 3, 2026}, 14, 66.1, 435.2},
        {"P00010", "Descripcion10", "ProveedorB", {27, 8, 2024}, {2, 1, 2026}, 103, 48.1, 88.2}
    };
    FILE* archivoLote;

    if(abrirArchivo(&archivoLote, "datos.bin", "wb") != OK)
        return FILE_ERR;

    fwrite(productos, sizeof(tProducto), 10, archivoLote);
    fclose(archivoLote);

    return OK;
}
int crearLoteProductosDesordenado()
{
    tProducto productos[] =
    {
        {"P0009", "Descripcion9", "ProveedorC", {30, 11, 2024}, {12, 3, 2026}, 14, 66.1, 435.2},
        {"P0006", "Descripcion6", "ProveedorB", {2, 12, 2024}, {9, 3, 2026}, 1, 1222.1, 6654.2},
        {"P0001", "Descripcion1", "ProveedorA", {12, 10, 2024}, {20, 7, 2026}, 5, 111.1, 222.2},
        {"P0004", "Descripcion4", "ProveedorC", {15, 11, 2024}, {17, 12, 2026}, 12, 112.1, 265.2},
        {"P0002", "Descripcion2", "ProveedorA", {21, 2, 2024}, {15, 6, 2026}, 50, 222.2, 331.2},
        {"P0007", "Descripcion7", "ProveedorC", {13, 1, 2024}, {24, 8, 2026}, 27, 433.1, 1231.2},
        {"P0005", "Descripcion5", "ProveedorA", {1, 10, 2024}, {7, 11, 2026}, 13, 1132.1, 4355.2},
        {"P0000", "Descripcion0", "ProveedorB", {27, 8, 2024}, {2, 1, 2026}, 103, 48.1, 88.2},
        {"P0008", "Descripcion8", "ProveedorA", {29, 1, 2024}, {31, 10, 2026}, 93, 554.1, 587.2},
        {"P0003", "Descripcion3", "ProveedorB", {14, 5, 2024}, {21, 2, 2026}, 45, 333.3, 456.2}
    };
    FILE* archivoLote;

    if(abrirArchivo(&archivoLote, "datos.bin", "wb") != OK)
        return FILE_ERR;

    fwrite(productos, sizeof(productos), 1, archivoLote);
    fclose(archivoLote);

    return OK;
}

int abrirArchivo(FILE** archivo, const char* nombreArch, const char* modoApertura)
{
    *archivo = fopen(nombreArch, modoApertura);
    if(!*archivo)
    {
        perror("Error en la apertura de archivo");
        return FILE_ERR;
    }
    return OK;
}

///Funcion menu

void procesarOpcionMenuEj1(tPila* p, int opcion)
{
    tProducto producto;
    switch(opcion)
    {
    case 1:
        cargarProducto(&producto);
        if(!pilaLlena(p, sizeof(tProducto)))
            ponerEnPila(p, &producto, sizeof(tProducto));
        else
            printf("\nPila llena\n");
        break;
    case 2:
        if(!pilaVacia(p))
        {
            verTopePila(p, &producto, sizeof(tProducto));
            mostrarProducto(&producto);
        }
        else
            printf("\nPila vacia\n\n");

        break;
    case 3:
        if(!pilaVacia(p))
        {
            sacarDePila(p, &producto, sizeof(tProducto));
            mostrarProducto(&producto);
        }
        else
            printf("\nPila vacia\n\n");

        break;
    default:
        break;
    }
}
int procesarOpcionMenuMain(int opcion)
{
    int codigoRetorno;

    switch(opcion)
    {
    case 1:
        codigoRetorno = ejercicio1();
        break;
    case 2:
        codigoRetorno = ejercicio2();
        break;
    case 3:
        codigoRetorno = ejercicio3();
        break;
    default:
        break;
    }
    return codigoRetorno;
}

int esArchivoConDatos(const char* nombreArch)
{
    FILE* archivo;
    int longitudArchivo;

    if(abrirArchivo(&archivo, nombreArch, "rb") != OK)
        return FILE_ERR;

    fseek(archivo, 0, SEEK_END);
    longitudArchivo = ftell(archivo);

    fclose(archivo);

    return longitudArchivo;
}
void calcularSuma(tPila* p1, tPila* p2, tPila* pilaResultado)
{
    int sumandoPila1;
    int sumandoPila2;
    int resultado;
    int carry;
    int proximoCarry;

    carry = 0;

    while(!pilaVacia(p1) && !pilaVacia(p2)){
        sacarDePila(p1, &sumandoPila1, sizeof(int));
        sacarDePila(p2, &sumandoPila2, sizeof(int));
        if((proximoCarry = (sumandoPila1 + sumandoPila2 + carry) / 10))
            resultado = sumandoPila1 + sumandoPila2 + carry - 10;
        else


            resultado = sumandoPila1 + sumandoPila2 + carry;
        ponerEnPila(pilaResultado, &resultado, sizeof(int));
        carry = proximoCarry;
    }

    while(!pilaVacia(p1)){
        sacarDePila(p1, &sumandoPila1, sizeof(int));
        if((proximoCarry = (sumandoPila1 + carry) / 10))
            resultado = sumandoPila1 + carry - 10;
        else
            resultado = sumandoPila1 + carry;
        carry = proximoCarry;
        ponerEnPila(pilaResultado, &resultado, sizeof(int));
    }

    while(!pilaVacia(p2)){
        sacarDePila(p2, &sumandoPila1, sizeof(int));
        if((proximoCarry = (sumandoPila2 + carry) / 10))
            resultado = sumandoPila2 + carry - 10;
        else
            resultado = sumandoPila2 + carry;
        carry = proximoCarry;
        ponerEnPila(pilaResultado, &resultado, sizeof(int));
    }

    if(carry)
        ponerEnPila(pilaResultado, &carry, sizeof(int));

}

//Funcion de carga
void cargarPilaConNumeros(tPila* p)
{
    int digito;
    puts("Ingrese un digito (negativo para salir):");
    scanf("%d", &digito);
    while(digito >= 0 && digito <= 9){
        if(pilaLlena(p, sizeof(int)))
            return;
        ponerEnPila(p, &digito, sizeof(int));
        puts("Ingrese un digito (negativo para salir):");
        scanf("%d", &digito);
    }
}
int cargarArchivoEnPilasOrdenando(tPila* p1, tPila* p2, const char* nombreArch,
                                  size_t tamRegistro,
                                  int(*cmp)(const void*, const void*))
{
    FILE* archivo;
    void* registro;
    void* registroCargado;

    if(abrirArchivo(&archivo, nombreArch, "rb") != OK)
        return FILE_ERR;
    if(!(registro = malloc(tamRegistro)) ||
            !(registroCargado = malloc(tamRegistro)))
    {
        fclose(archivo);
        free(registro);
        return MEM_ERR;
    }

    fread(registro, tamRegistro, 1, archivo);
    if(pilaLlena(p1, tamRegistro))
    {
        fclose(archivo);
        free(registro);
        free(registroCargado);
        return MEM_ERR;
    }
    ponerEnPila(p1, registro, tamRegistro);
    while(!feof(archivo))
    {
        fread(registro, tamRegistro, 1, archivo);
        if(verTopePila(p1, registroCargado, tamRegistro) == OK &&
                    cmp(registroCargado, registro) > 0)
        {
            while(verTopePila(p1, registroCargado, tamRegistro) == OK &&
                    cmp(registroCargado, registro) > 0)
            {
                sacarDePila(p1, registroCargado, tamRegistro);
                if(pilaLlena(p2, tamRegistro))
                {
                    fclose(archivo);
                    free(registro);
                    free(registroCargado);
                    return MEM_ERR;
                }
                ponerEnPila(p2, registroCargado, tamRegistro);
            }
            if(pilaLlena(p1, tamRegistro))
            {
                fclose(archivo);
                free(registro);
                free(registroCargado);
                return MEM_ERR;
            }
            ponerEnPila(p1, registro, tamRegistro);
        }
        else
        {
            while(verTopePila(p2, registroCargado, tamRegistro) != PILA_VACIA &&
                    cmp(registroCargado, registro) < 0)
            {
                sacarDePila(p2, registroCargado, tamRegistro);
                if(pilaLlena(p1, tamRegistro))
                {
                    fclose(archivo);
                    free(registro);
                    free(registroCargado);
                    return MEM_ERR;
                }
                ponerEnPila(p1, registroCargado, tamRegistro);
            }
            if(pilaLlena(p2, tamRegistro))
            {
                fclose(archivo);
                free(registro);
                free(registroCargado);
                return MEM_ERR;
            }
            ponerEnPila(p2, registro, tamRegistro);
        }
    }
    while(!pilaVacia(p2))
    {
        sacarDePila(p2, registroCargado, tamRegistro);
        if(pilaLlena(p1, tamRegistro))
        {
            fclose(archivo);
            free(registro);
            free(registroCargado);
            return MEM_ERR;
        }
        ponerEnPila(p1, registroCargado, tamRegistro);
    }

    fclose(archivo);
    free(registro);
    free(registroCargado);

    return OK;
}

int cargarArchivoEnPila(tPila* p, const char* nombreArch, size_t tamRegistro)
{
    FILE* archivo;
    void* buffer;

    if(abrirArchivo(&archivo, nombreArch, "rb") != OK)
        return FILE_ERR;

    if((buffer = malloc(tamRegistro)) == NULL)
    {
        fclose(archivo);
        return MEM_ERR;
    }

    fread(buffer, tamRegistro, 1, archivo);
    if(pilaLlena(p, tamRegistro))
    {
        fclose(archivo);
        free(buffer);
        return MEM_ERR;
    }
    ponerEnPila(p, buffer, tamRegistro);
    while(!feof(archivo))
    {
        fread(buffer, tamRegistro, 1, archivo);

        if(pilaLlena(p, tamRegistro))
        {
            fclose(archivo);
            free(buffer);
            return MEM_ERR;
        }
        ponerEnPila(p, buffer, tamRegistro);
    }


    fclose(archivo);
    free(buffer);

    return OK;
}

int cargarPilaEnArchivo(tPila* p, const char* nombreArch, size_t tamRegistro)
{
    FILE* archivoACargar;
    void* info;

    if(abrirArchivo(&archivoACargar, nombreArch, "wb") != OK)
        return FILE_ERR;

    if((info = malloc(tamRegistro)) == NULL)
    {
        fclose(archivoACargar);
        return MEM_ERR;
    }

    while(!pilaVacia(p))
    {
        sacarDePila(p, info, tamRegistro);
        mostrarIDProducto((tProducto*)info);
        fwrite(info, tamRegistro, 1, archivoACargar);
    }

    fclose(archivoACargar);
    free(info);

    return OK;
}
void cargarProducto(tProducto* producto)
{
    printf("Codigo: ");
    fflush(stdin);
    scanf("%s", producto->codigoProducto);
    printf("Descripcion: ");
    fflush(stdin);
    scanf("%s", producto->descripcion);
    printf("Proveedor: ");
    fflush(stdin);
    scanf("%s", producto->proveedor);
    printf("Dia compra: ");
    scanf("%d", &producto->fechaCompra.dia);
    printf("Mes compra: ");
    scanf("%d", &producto->fechaCompra.mes);
    printf("Anio compra: ");
    scanf("%d", &producto->fechaCompra.anio);
    printf("Dia vencimiento: ");
    scanf("%d", &producto->fechaVencimiento.dia);
    printf("Mes vencimiento: ");
    scanf("%d", &producto->fechaVencimiento.mes);
    printf("Anio vencimiento: ");
    scanf("%d", &producto->fechaVencimiento.anio);
    printf("Cantidad: ");
    scanf("%d", &producto->cantidad);
    printf("Precio compra: ");
    scanf("%f", &producto->precioCompra);
    printf("Precio venta: ");
    scanf("%f", &producto->precioVenta);
}
//Funciones de mostrar
void mostrarProducto(const tProducto* producto)
{
    fprintf(stdout, "Codigo: %s\nDescripcion: %s\nProveedor: %s\nFechaCompra: "
            "%02d-%02d-%d\nFechaVencimiento: %02d-%02d-%d\nCantidad: %d\n"
            "PrecioCompra: %0.2f\nPrecioVenta: %0.2f\n",
            producto->codigoProducto,
            producto->descripcion,
            producto->proveedor,
            producto->fechaCompra.dia,
            producto->fechaCompra.mes,
            producto->fechaCompra.anio,
            producto->fechaVencimiento.dia,
            producto->fechaVencimiento.mes,
            producto->fechaVencimiento.anio,
            producto->cantidad,
            producto->precioCompra,
            producto->precioVenta
           );
}
void mostrarIDProducto(const tProducto* producto)
{
    fprintf(stdout, "Codigo: %s\n", producto->codigoProducto);
}
//Funciones comparacion
int cmpProductoPorID(const void* prodA, const void* prodB)
{
    return strcmp(((tProducto*)prodB)->codigoProducto,
                  ((tProducto*)prodA)->codigoProducto);
}
//Ejercicios
int ejercicio1()
{
    int opcion = 1;
    int codigoError;
    tPila pila;
    crearPila(&pila);
    crearLoteProductosOrdenado();

    if((codigoError = cargarArchivoEnPila(&pila, "datos.bin", sizeof(tProducto))))
    {
        vaciarPila(&pila);
        return codigoError;
    }

    while(opcion != 4)
    {
        printf("MENU\n");
        printf("1- Cargar mas info en pila.\n");
        printf("2- Ver tope.\n");
        printf("3- Sacar de pila.\n");
        printf("4- Salir menu.\n");
        do
        {
            printf("Ingrese opcion: ");
            scanf("%d", &opcion);
        }
        while(opcion < 1 || opcion > 4);
        procesarOpcionMenuEj1(&pila, opcion);
        system("pause");
        system("cls");
    }

    cargarPilaEnArchivo(&pila, "datos.bin", sizeof(tProducto));
    if(!esArchivoConDatos("datos.bin"))
    {
        remove("datos.bin");
        fprintf(stdout, "\nArchivo borrado\n");
    }

    vaciarPila(&pila);
    return OK;
}
int ejercicio2()
{
    //int  codigo;
    tPila p1;
    tPila p2;
    crearLoteProductosDesordenado();
    crearPila(&p1);
    crearPila(&p2);
    cargarArchivoEnPilasOrdenando(&p1, &p2, "datos.bin",
                                  sizeof(tProducto), cmpProductoPorID);
    cargarPilaEnArchivo(&p1, "datos.bin", sizeof(tProducto));

    vaciarPila(&p1);
    vaciarPila(&p2);

    return OK;
}
int ejercicio3()
{
    int digito;
    tPila p1;
    tPila p2;
    tPila pilaResultado;

    crearPila(&p1);
    crearPila(&p2);
    crearPila(&pilaResultado);

    puts("\nCargando Pila 1:");
    cargarPilaConNumeros(&p1);
    puts("\nCargando Pila 2:");
    cargarPilaConNumeros(&p2);
    calcularSuma(&p1, &p2, &pilaResultado);

    printf("Resultado:\n");
    while(!pilaVacia(&pilaResultado)){
        sacarDePila(&pilaResultado, &digito, sizeof(int));
        printf("%d", digito);
    }
    puts("");

    vaciarPila(&p1);
    vaciarPila(&p2);
    vaciarPila(&pilaResultado);
    return OK;
}
