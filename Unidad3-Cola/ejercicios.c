#include "ejercicios.h"

#include "ejercicios.h"
int crearLoteProductosOrdenado()
{
    int i;
    tProducto productos[] =
    {
        {"P0001", "Descripcion1", "ProveedorA", {12, 10, 2024}, {20, 7, 2026}, 21, 111.1, 222.2},
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
    for(i = 0; i < sizeof(productos)/sizeof(tProducto); i ++)
        fwrite(&productos[i], sizeof(tProducto), 1, archivoLote);
    fclose(archivoLote);

    return OK;
}
int crearLoteProductosDesordenado()
{
    tProducto productos[10] =
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



int cargarArchivoEnCola(tCola* c, const char* nombreArch, size_t tamRegistro)
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
    if(colaLlena(c, tamRegistro))
    {
        fclose(archivo);
        free(buffer);
        return MEM_ERR;
    }
    insertarEnCola(c, buffer, tamRegistro);
    while(!feof(archivo))
    {
        fread(buffer, tamRegistro, 1, archivo);

        if(colaLlena(c, tamRegistro))
        {
            fclose(archivo);
            free(buffer);
            return MEM_ERR;
        }
        insertarEnCola(c, buffer, tamRegistro);
    }


    fclose(archivo);
    free(buffer);

    return OK;
}

int cargarArchivoEnColaFiltrando(tCola* c, const char* nombreArch,
                                 size_t tamRegistro,
                                 int(*filtro)(const void*))
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
    while(!feof(archivo))
    {
        mostrarIDProducto((tProducto*)buffer);
        if(filtro(buffer))
        {

            if(colaLlena(c, tamRegistro))
            {
                fclose(archivo);
                free(buffer);
                return MEM_ERR;
            }
            insertarEnCola(c, buffer, tamRegistro);
        }
        fread(buffer, tamRegistro, 1, archivo);
    }

    fclose(archivo);
    free(buffer);

    return OK;
}

int cargarColaEnArchivo(tCola* c, const char* nombreArch, size_t tamRegistro)
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

    while(!colaVacia(c))
    {
        sacarDeCola(c, info, tamRegistro);
        mostrarIDProducto((tProducto*)info);
        fwrite(info, tamRegistro, 1, archivoACargar);
    }

    fclose(archivoACargar);
    free(info);

    return OK;
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
//Filtro
int filtrarCantidadMayorA20(const void* producto)
{
    return ((tProducto*)producto)->cantidad > 20;
}
