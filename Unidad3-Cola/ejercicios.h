#ifndef EJERCICIOS_H_INCLUDED
#define EJERCICIOS_H_INCLUDED

#include "../Primitivas/ColaDinamica/colaDinamica.h"

#define TAM_CODIGO 8
#define TAM_DESCRIPCION 16
#define TAM_PROVEEDOR 16

#define FILE_ERR -3

typedef struct
{
    int dia;
    int mes;
    int anio;
}tFecha;

typedef struct
{
    char codigoProducto[TAM_CODIGO];
    char descripcion[TAM_DESCRIPCION];
    char proveedor[TAM_PROVEEDOR];
    tFecha fechaCompra;
    tFecha fechaVencimiento;
    int cantidad;
    float precioCompra;
    float precioVenta;
}tProducto;

int crearLoteProductosOrdenado();
int crearLoteProductosDesordenado();
int abrirArchivo(FILE** archivo, const char* nombreArch, const char* modoApertura);
//Funciones de carga
int cargarArchivoEnCola(tCola* c, const char* nombreArch, size_t tamRegistro);
int cargarColaEnArchivo(tCola* c, const char* nombreArch, size_t tamRegistro);
int cargarArchivoEnColaFiltrando(tCola* c, const char* nombreArch,
                                 size_t tamRegistro,
                                 int(*filtro)(const void*));
//Funciones producto
void mostrarProducto(const tProducto* producto);
void mostrarIDProducto(const tProducto* producto);
int cmpProductoPorID(const void* prodA, const void* prodB);

//filtros
int filtrarCantidadMayorA20(const void* producto);

#endif // EJERCICIOS_H_INCLUDED
