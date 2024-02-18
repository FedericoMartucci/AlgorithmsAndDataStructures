#ifndef EJERCICIOS_H_INCLUDED
#define EJERCICIOS_H_INCLUDED

#include "../Primitivas/ListaSimple/listaSimple.h"

#define TAM_CODIGO 8
#define TAM_DESCRIPCION 16
#define TAM_PROVEEDOR 16

#define TAM_LINEA 1024

#define MEM_ERR -5
#define FIL 4
#define COL 5

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

typedef struct
{
    int fila;
    int columna;
    int valor;
}tMatriz;

typedef struct
{
    char codigoProducto[TAM_CODIGO];
    char descripcion[TAM_DESCRIPCION];
    tFecha fechaCompra;
    tFecha fechaVencimiento;
    int cantidad;
    float precioCompra;
    float precioVenta;
}tProductoSinProveedor;

///Funciones ejercicio 3
void parsearAProductoSinProveedor(char* producto,
                                  void* productoSP);
int insertarAlFinalAcumulando(tLista* l, const void* info, unsigned cantBytes,
                              int(*cmp)(const void*, const void*),
                              void(*acumularProductos)(void*, const void*));
int eliminarAparicionesGrabandoEnArchivoTxt(tLista* pl, const char* nombreArch,
                                            int(*cmp)(const void*, const void*),
                                            void(*grabar)(FILE**, const void*));
///--------------------------Funciones de archivos-----------------------------
int crearLoteProductos(const char* nombreArch);
int abrirArchivo(FILE** archivo, const char* nombreArch, const char* modo);
int cargarArchivoEnLista(tLista* l, unsigned tamDato, const char* nombreArch,
                         int (*insertar)(tLista* pl, const void* info,
                                         unsigned cantBytes));
int cargarArchivoOrdenadoEnLista(tLista* l, unsigned tamDato,
                                 const char* nombreArch,
                                 int(*cmp)(const void*, const void*));
int cargarArchivoTxtEnListaAcumulando(tLista* l, const char* nombreArch,
                                      unsigned tamInfo,
                                      void(*parsear)(char*, void*),
                                      int(*cmp)(const void*, const void*),
                                      void(*acumular)(void*, const void*));
void grabarProductoSP(FILE** archivo, const void* dato);
void grabarProducto(FILE** archivo, const void* dato);
int cargaListaEnArchivoTxt(tLista* l, const char* nombreArch, unsigned tamInfo,
                           void(*grabar)(FILE** archivo, const void* dato));
///--------------------------Funciones de menu----------------------------------
int procesarOpcionMenuMain(int opcion);

///--------------------------Funciones de comparacion---------------------------
int cmpCodigoProductos(const void* a, const void* b);
int cmpCodigoProductosSP(const void* a, const void* b);
int cmpCodigoYDescripcionProductos(const void* a, const void* b);

///--------------------------Funciones de acumular------------------------------
void acumularProductos(void* productoLista, const void* productoAAcumular);
void acumularProductosSP(void* productoLista, const void* productoAAcumular);
///--------------------------Funciones de ejercicios----------------------------
int ejercicio2();
int ejercicio3();
int ejercicio5();

///--------------------------Funciones de filtrar-------------------------------
int filtrarDistintoCero(const void* a);
///--------------------------Funciones de mostrar-------------------------------
void mostrarProducto(const void* producto);
void mostrarProductoSP(const void* producto);


#endif // EJERCICIOS_H_INCLUDED
