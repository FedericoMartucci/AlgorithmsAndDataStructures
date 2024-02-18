#include "ejercicios.h"

///--------------------------Funciones de archivos-----------------------------
int crearLoteProductos(const char* nombreArch)
{
    tProducto productos[] =
    {
        {"P0007", "Descripcion7", "ProveedorC", {13, 1, 2024}, {24, 8, 2026}, 27, 433.1, 1231.2},
        {"P0003", "Descripcion3", "ProveedorB", {14, 5, 2024}, {21, 2, 2026}, 45, 333.3, 456.2},
        {"P0001", "Descripcion1", "ProveedorA", {12, 10, 2024}, {20, 7, 2026}, 5, 111.1, 222.2},
        {"P00010", "Descripcion10", "ProveedorB", {27, 8, 2024}, {2, 1, 2026}, 103, 48.1, 88.2},
        {"P0005", "Descripcion5", "ProveedorA", {1, 10, 2024}, {7, 11, 2026}, 13, 1132.1, 4355.2},
        {"P0002", "Descripcion2", "ProveedorA", {21, 2, 2024}, {15, 6, 2026}, 50, 222.2, 331.2},
        {"P0004", "Descripcion4", "ProveedorC", {15, 11, 2024}, {17, 12, 2026}, 12, 112.1, 265.2},
        {"P0005", "Descripcion5", "ProveedorA", {1, 10, 2024}, {7, 11, 2026}, 80, 1132.1, 4355.2},
        {"P0009", "Descripcion9", "ProveedorC", {30, 11, 2024}, {12, 3, 2026}, 14, 66.1, 435.2},
        {"P0004", "Descricion4", "ProveedorC", {15, 11, 2024}, {17, 12, 2026}, 12, 112.1, 265.2},
        {"P0002", "Descripcion2", "ProveedorA", {21, 2, 2024}, {15, 6, 2026}, 50, 122.2, 335.2},
        {"P0008", "Descripcion8", "ProveedorA", {29, 1, 2024}, {31, 10, 2026}, 93, 554.1, 587.2},
        {"P0006", "Descripcion6", "ProveedorB", {2, 12, 2024}, {9, 3, 2026}, 1, 1222.1, 6654.2},
        {"P0002", "Descripcion222", "ProveedorA", {21, 2, 2024}, {15, 6, 2026}, 50, 222.2, 331.2},
    };
    FILE* archivoLote;
    int i;

    if(abrirArchivo(&archivoLote, nombreArch, "wt") != OK)
        return FILE_ERR;

    for(i = 0; i < sizeof(productos)/sizeof(tProducto); i ++)
        grabarProducto(&archivoLote, &productos[i]);
    fclose(archivoLote);

    return OK;
}
int abrirArchivo(FILE** archivo, const char* nombreArch, const char* modo)
{
    if((*archivo = fopen(nombreArch, modo)) == NULL)
    {
        perror("Error en la apertura de archivo");
        return FILE_ERR;
    }

    return OK;
}
int cargarArchivoEnLista(tLista* l, unsigned tamDato, const char* nombreArch,
                         int (*insertar)(tLista* pl, const void* info,
                                 unsigned cantBytes))
{
    FILE* archivoDatos;
    void* buffer = malloc(tamDato);

    if(abrirArchivo(&archivoDatos, nombreArch, "rb") != OK ||
            !(buffer = malloc(tamDato)))
    {
        fclose(archivoDatos);
        return FILE_ERR;
    }

    fread(buffer, tamDato, 1, archivoDatos);
    while(!feof(archivoDatos))
    {
        insertar(l, buffer, tamDato);
        fread(buffer, tamDato, 1, archivoDatos);
    }

    fclose(archivoDatos);
    free(buffer);
    return OK;
}

int cargarArchivoOrdenadoEnLista(tLista* l, unsigned tamDato,
                                 const char* nombreArch,
                                 int(*cmp)(const void*, const void*))
{
    FILE* archivoDatos;
    void* buffer = malloc(tamDato);

    if(abrirArchivo(&archivoDatos, nombreArch, "rb") != OK ||
            !(buffer = malloc(tamDato)))
    {
        fclose(archivoDatos);
        return FILE_ERR;
    }

    fread(buffer, tamDato, 1, archivoDatos);
    while(!feof(archivoDatos))
    {
        insertarOrdenado(l, buffer, tamDato, cmp);
        fread(buffer, tamDato, 1, archivoDatos);
    }

    fclose(archivoDatos);
    free(buffer);
    return OK;
}
int cargarArchivoTxtEnListaAcumulando(tLista* l, const char* nombreArch,
                                      unsigned tamInfo,
                                      void(*parsear)(char*, void*),
                                      int(*cmp)(const void*, const void*),
                                      void(*acumular)(void*, const void*))
{
    FILE* archivoDatos;
    char linea[TAM_LINEA];
    void* registroParseado;

    if(abrirArchivo(&archivoDatos, nombreArch, "rb") != OK)
        return FILE_ERR;

    if(!(registroParseado = malloc(tamInfo)))
    {
        fclose(archivoDatos);
        return MEM_ERR;
    }


    while(fgets(linea, sizeof(linea), archivoDatos))
    {
        parsear(linea, registroParseado);
        mostrarProductoSP(registroParseado);
        insertarAlFinalAcumulando(l, registroParseado, tamInfo,
                                  cmp,
                                  acumular);
    }

    fclose(archivoDatos);
    free(registroParseado);
    return OK;
}
int eliminarAparicionesGrabandoEnArchivoTxt(tLista* pl, const char* nombreArch,
        int(*cmp)(const void*, const void*),
        void(*grabar)(FILE**, const void*))
{
    tNodo* nodoAEliminar;
    FILE* archivoErrores;

    if(abrirArchivo(&archivoErrores, nombreArch, "wt") != OK)
        return FILE_ERR;

    while(*pl)
    {
        if((*pl)->sig && (eliminarAparicionesGrabandoTxt(&(*pl)->sig, &archivoErrores,(*pl)->info, cmp, grabar)))
        {
            nodoAEliminar = *pl;
            grabar(&archivoErrores, nodoAEliminar->info);
            *pl = nodoAEliminar->sig;
            free(nodoAEliminar->info);
            free(nodoAEliminar);
        }
        else
            pl = &(*pl)->sig;
    }

    fclose(archivoErrores);
    return OK;

}
int cargaListaEnArchivoTxt(tLista* l, const char* nombreArch, unsigned tamInfo,
                           void(*grabar)(FILE** archivo, const void* dato))
{
    FILE* archivoACargar;
    void* buffer;

    if(abrirArchivo(&archivoACargar, nombreArch, "wt") != OK)
        return FILE_ERR;

    if(!(buffer = malloc(tamInfo)))
    {
        fclose(archivoACargar);
        return MEM_ERR;
    }

    while(!listaVacia(l))
    {
        sacarPrimero(l, buffer, tamInfo);
        grabar(&archivoACargar, buffer);
    }

    fclose(archivoACargar);
    free(buffer);

    return OK;
}
void grabarProducto(FILE** archivo, const void* dato)
{
    fprintf(*archivo, "%s|%s|%s|%d-%d-%d|%d-%d-%d|%d|%0.2f|%0.2f\n",
            ((tProducto*)dato)->codigoProducto,
            ((tProducto*)dato)->descripcion,
            ((tProducto*)dato)->proveedor,
            ((tProducto*)dato)->fechaCompra.dia,
            ((tProducto*)dato)->fechaCompra.mes,
            ((tProducto*)dato)->fechaCompra.anio,
            ((tProducto*)dato)->fechaVencimiento.dia,
            ((tProducto*)dato)->fechaVencimiento.mes,
            ((tProducto*)dato)->fechaVencimiento.anio,
            ((tProducto*)dato)->cantidad,
            ((tProducto*)dato)->precioCompra,
            ((tProducto*)dato)->precioVenta);
}
void grabarProductoSP(FILE** archivo, const void* dato)
{
    fprintf(*archivo, "%s|%s|%d-%d-%d|%d-%d-%d|%d|%0.2f|%0.2f\n",
            ((tProductoSinProveedor*)dato)->codigoProducto,
            ((tProductoSinProveedor*)dato)->descripcion,
            ((tProductoSinProveedor*)dato)->fechaCompra.dia,
            ((tProductoSinProveedor*)dato)->fechaCompra.mes,
            ((tProductoSinProveedor*)dato)->fechaCompra.anio,
            ((tProductoSinProveedor*)dato)->fechaVencimiento.dia,
            ((tProductoSinProveedor*)dato)->fechaVencimiento.mes,
            ((tProductoSinProveedor*)dato)->fechaVencimiento.anio,
            ((tProductoSinProveedor*)dato)->cantidad,
            ((tProductoSinProveedor*)dato)->precioCompra,
            ((tProductoSinProveedor*)dato)->precioVenta);
}
void parsearAProductoSinProveedor(char* producto,
                                  void* productoSP)
{
    char* aux = strrchr(producto, '\n');
    *aux = '\0';
    aux = strrchr(producto, '|');
    sscanf(aux + 1, "%f", &((tProductoSinProveedor*)productoSP)->precioVenta);
    *aux = '\0';
    aux = strrchr(producto, '|');
    sscanf(aux + 1, "%f", &((tProductoSinProveedor*)productoSP)->precioCompra);
    *aux = '\0';
    aux = strrchr(producto, '|');
    sscanf(aux + 1, "%d", &((tProductoSinProveedor*)productoSP)->cantidad);
    *aux = '\0';
    aux = strrchr(producto, '-');
    sscanf(aux + 1, "%d", &((tProductoSinProveedor*)productoSP)->fechaVencimiento.anio);
    *aux = '\0';
    aux = strrchr(producto, '-');
    sscanf(aux + 1, "%d", &((tProductoSinProveedor*)productoSP)->fechaVencimiento.mes);
    *aux = '\0';
    aux = strrchr(producto, '|');
    sscanf(aux + 1, "%d", &((tProductoSinProveedor*)productoSP)->fechaVencimiento.dia);
    *aux = '\0';
    aux = strrchr(producto, '-');
    sscanf(aux + 1, "%d", &((tProductoSinProveedor*)productoSP)->fechaCompra.anio);
    *aux = '\0';
    aux = strrchr(producto, '-');
    sscanf(aux + 1, "%d", &((tProductoSinProveedor*)productoSP)->fechaCompra.mes);
    *aux = '\0';
    aux = strrchr(producto, '|');
    sscanf(aux + 1, "%d", &((tProductoSinProveedor*)productoSP)->fechaCompra.dia);
    *aux = '\0';
    aux = strrchr(producto, '|');
    *aux = '\0';
    aux = strrchr(producto, '|');
    strcpy(((tProductoSinProveedor*)productoSP)->descripcion, aux + 1);
    *aux = '\0';
    strcpy(((tProductoSinProveedor*)productoSP)->codigoProducto, producto);
}
int insertarAlFinalAcumulando(tLista* pl, const void* info, unsigned cantBytes,
                              int(*cmp)(const void*, const void*),
                              void(*acumular)(void*, const void*))
{
    tNodo* nuevoNodo;
    while((*pl) && cmp((*pl)->info, info) != 0)
        pl = &(*pl)->sig;

    if(!*pl)
    {
        if(!(nuevoNodo = malloc(sizeof(tNodo))) ||
                !(nuevoNodo->info = malloc(cantBytes)))
        {
            free(nuevoNodo);
            return LISTA_LLENA;
        }
        memcpy(nuevoNodo->info, info, cantBytes);
        nuevoNodo->tamInfo = cantBytes;
        nuevoNodo->sig = *pl;
        *pl = nuevoNodo;
    }
    else
        acumular((*pl)->info, info);
    return OK;
}
///--------------------------Funciones de menu----------------------------------
int procesarOpcionMenuMain(int opcion)
{
    int codigoRetorno;

    switch(opcion)
    {
    case 2:
        codigoRetorno = ejercicio2();
        break;
    case 3:
        codigoRetorno = ejercicio3();
        break;
    case 4:
        break;
    case 5:
        ejercicio5();
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        break;
    case 11:
        break;
    case 12:
        break;
    default:
        break;
    }
    return codigoRetorno;
}

///--------------------------Funciones de ejercicios----------------------------
int ejercicio2()
{
    int codigoError;

    tLista listaDatos1;
    tLista listaDatos2;

    crearLista(&listaDatos1);
    crearLista(&listaDatos2);
    if((codigoError = crearLoteProductos("datos1.bin")))
    {
        vaciarLista(&listaDatos1);
        vaciarLista(&listaDatos2);
        return codigoError;
    }
    if((codigoError = crearLoteProductos("datos2.bin")))
    {
        vaciarLista(&listaDatos1);
        vaciarLista(&listaDatos2);
        return codigoError;
    }

    if((codigoError = cargarArchivoEnLista(&listaDatos1, sizeof(tProducto), "datos1.bin", insertarAlFinal)))
    {
        vaciarLista(&listaDatos1);
        vaciarLista(&listaDatos2);
        return codigoError;
    }

    if((codigoError = cargarArchivoOrdenadoEnLista(&listaDatos2, sizeof(tProducto), "datos2.bin", cmpCodigoProductos)))
    {
        vaciarLista(&listaDatos1);
        vaciarLista(&listaDatos2);
        return codigoError;
    }

    mostrarListaGenerica(&listaDatos1, mostrarProducto);
    mostrarListaGenerica(&listaDatos2, mostrarProducto);

    puts("\n\n");

    ordenarListaPorSeleccion(&listaDatos2, cmpCodigoProductos);
    mostrarListaGenerica(&listaDatos2, mostrarProducto);

    vaciarLista(&listaDatos1);
    vaciarLista(&listaDatos2);

    return codigoError;
}

int ejercicio3()
{
    tLista l;

    crearLista(&l);
    crearLoteProductos("datos.txt");

    cargarArchivoTxtEnListaAcumulando(&l, "datos.txt", sizeof(tProductoSinProveedor),
                                      parsearAProductoSinProveedor, cmpCodigoProductosSP,
                                      acumularProductosSP);
    eliminarAparicionesGrabandoEnArchivoTxt(&l, "errores2.txt", cmpCodigoProductosSP, grabarProductoSP);
    ordenarListaPorSeleccion(&l, cmpCodigoProductosSP);
    cargaListaEnArchivoTxt(&l, "depurado.txt", sizeof(tProductoSinProveedor),
                           grabarProductoSP);

    vaciarLista(&l);
    return OK;
}
int ejercicio5()
{
    tLista l;
    int opcion;
    int fila;
    int columna;
    int valor;
    int mat[FIL][COL] =
    {
        {0, 1, 0, 2, 0},
        {0, 20, 0, 0, 1},
        {19, 0, 0, 2, 0},
        {0, 0, 1, 0, 0},
    };

    crearLista(&l);

    cargarListaVectorFiltrando(&l, mat, sizeof(int), sizeof(mat)/sizeof(int),
                               filtrarDistintoCero, insertarAlFinal);

    while(opcion != 5)
    {
        puts("MENU");
        puts("1- Ingresar fila y columna y mostrar el valor correspondiente.");
        puts("2- Ingresar una fila y mostrar los elementos de la misma.");
        puts("3- Ingresar una columna y mostrar los elementos de la misma.");
        puts("4- Mostrar elementos matriz.");
        puts("5- Salir.");
        printf("Ingrese un valor: ");
        scanf("%d", &opcion);
        switch(opcion)
        {
        case 1:
            printf("Ingrese una fila: ");
            scanf("%d", &fila);
            printf("Ingrese una columna: ");
            scanf("%d", &columna);

            break;
        case 2:
            printf("Ingrese una fila: ");
            scanf("%d", &fila);
            break;
        case 3:
            printf("Ingrese una columna: ");
            scanf("%d", &columna);
            break;
        case 4:
            break;
        default:
            break;
        }lj
    }


    vaciarLista(&l);
    return OK;
}

///--------------------------Funciones de filtrar-------------------------------
int filtrarDistintoCero(const void* a)
{
    return *(int*)a != 0;
}
///--------------------------Funciones de acumular------------------------------
void acumularProductos(void* productoLista, const void* productoAAcumular)
{
    ((tProducto*)productoLista)->cantidad += ((tProducto*)productoAAcumular)->cantidad;
    if(((tProducto*)productoLista)->precioVenta < ((tProducto*)productoAAcumular)->precioVenta)
        ((tProducto*)productoLista)->precioVenta = ((tProducto*)productoAAcumular)->precioVenta;
}
void acumularProductosSP(void* productoLista, const void* productoAAcumular)
{
    ((tProductoSinProveedor*)productoLista)->cantidad += ((tProductoSinProveedor*)productoAAcumular)->cantidad;
    if(((tProductoSinProveedor*)productoLista)->precioVenta < ((tProductoSinProveedor*)productoAAcumular)->precioVenta)
        ((tProductoSinProveedor*)productoLista)->precioVenta = ((tProductoSinProveedor*)productoAAcumular)->precioVenta;
    if(((tProductoSinProveedor*)productoLista)->precioCompra < ((tProductoSinProveedor*)productoAAcumular)->precioCompra)
    {
        ((tProductoSinProveedor*)productoLista)->precioCompra = ((tProductoSinProveedor*)productoAAcumular)->precioCompra;
    }
}
///--------------------------Funciones de comparacion---------------------------
int cmpCodigoProductos(const void* a, const void* b)
{
    return strcmp(((tProducto*)a)->codigoProducto, ((tProducto*)b)->codigoProducto);
}
int cmpCodigoProductosSP(const void* a, const void* b)
{
    return strcmp(((tProductoSinProveedor*)a)->codigoProducto, ((tProductoSinProveedor*)b)->codigoProducto);
}

int cmpCodigoYDescripcionProductos(const void* a, const void* b)
{
    int comparacion;
    comparacion = strcmp(((tProducto*)a)->codigoProducto, ((tProducto*)b)->codigoProducto);
    if(comparacion == 0)
        return strcmp(((tProducto*)a)->descripcion, ((tProducto*)b)->descripcion);
    return comparacion;
}

///--------------------------Funciones de mostrar-------------------------------
void mostrarProducto(const void* producto)
{
    fprintf(stdout, "Codigo: %s\nCantidad: %d\nPrecio: %0.2f\n\n",
            ((tProducto*)producto)->codigoProducto,
            ((tProducto*)producto)->cantidad,
            ((tProducto*)producto)->precioVenta);
}
void mostrarProductoSP(const void* producto)
{
    fprintf(stdout, "Codigo: %s\nCantidad: %d\nPrecioVenta: %0.2f\n"
            "PrecioCompra: %0.2f\n\n",
            ((tProductoSinProveedor*)producto)->codigoProducto,
            ((tProductoSinProveedor*)producto)->cantidad,
            ((tProductoSinProveedor*)producto)->precioVenta,
            ((tProductoSinProveedor*)producto)->precioCompra);
}
