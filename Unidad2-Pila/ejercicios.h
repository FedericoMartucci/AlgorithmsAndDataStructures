#ifndef EJERCICIOS_H_INCLUDED
#define EJERCICIOS_H_INCLUDED

#include "../Primitivas/PilaDinamica/pila.h"

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

void procesarOpcionMenuEj1(tPila* p, int opcion);
int procesarOpcionMenuMain(int opcion);
int cargarArchivoEnPila(tPila* p, const char* nombreArch, size_t tamRegistro);
int cargarPilaEnArchivo(tPila* p, const char* nombreArch, size_t tamRegistro);
int cargarArchivoEnPilasOrdenando(tPila* p1, tPila* p2, const char* nombreArch,
                                  size_t tamRegistro,
                                  int(*cmp)(const void*, const void*));
void calcularSuma(tPila* p1, tPila* p2, tPila* pilaResultado);
//Funcion de carga
void cargarPilaConNumeros(tPila* p);
//Funciones archivos
int crearLoteProductosOrdenado();
int crearLoteProductosDesordenado();
int abrirArchivo(FILE** archivo, const char* nombreArch, const char* modoApertura);
int esArchivoConDatos(const char* nombreArch);
//Funciones producto
void cargarProducto(tProducto* producto);
void mostrarProducto(const tProducto* producto);
void mostrarIDProducto(const tProducto* producto);
//Funciones comparacion
int cmpProductoPorID(const void* prodA, const void* prodB);
//Ejercicios
int ejercicio1();
int ejercicio2();
int ejercicio3();
#endif // EJERCICIOS_H_INCLUDED
