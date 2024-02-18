#ifndef LISTASIMPLE_H_INCLUDED
#define LISTASIMPLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(X, Y) (X < Y ? (X) : (Y))

#define OK 0
#define LISTA_VACIA -1
#define LISTA_LLENA -2
#define FILE_ERR -3
#define N_ERR -4

#define MAX_ID 8
#define MAX_NOMBRE 30

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;


typedef struct
{
    char id[MAX_ID];
    char nombre[MAX_NOMBRE];
    int anioCursada;
}tMateria;

///--------------------------Primitivas basicas---------------------------------
void crearLista(tLista* pl);
void vaciarLista(tLista* pl);
int listaVacia(const tLista* pl);
int listaLlena(const tLista* pl, unsigned cantBytes);


///--------------------------Funciones de insercion-----------------------------
int insertarAlFinal(tLista* pl, const void* info, unsigned cantBytes);
int insertarAlComienzo(tLista* pl, const void* info, unsigned cantBytes);
int insertarOrdenado(tLista* pl, const void* info, unsigned cantBytes,
                     int(*cmp)(const void*, const void*));
int cargarListaVector(tLista* pl, const void* info, unsigned tamElemento,
                      int cantElementos, int (*insertar)(tLista* pl,
                      const void* info, unsigned cantBytes));
int insertarOrdenadoAcumulando(tLista* pl, const void* info, unsigned cantBytes,
                               int(* cmp)(const void*, const void*),
                               void(*acumular)(void*, const void*));
int cargarListaVectorFiltrando(tLista* l, const void* info,
                                  unsigned tamElemento, int cantElementos,
                                  int (*filtrar)(const void*),
                                  int (*insertar)(tLista* pl, const void* info,
                                                  unsigned cantBytes));

///--------------------------Funciones de archivos-----------------------------
//int crearLoteProductos(const char* nombreArch);
//int abrirArchivo(FILE** archivo, const char* nombreArch, const char* modo);
//int cargarArchivoEnLista(tLista* l, unsigned tamDato, const char* nombreArch,
//                         int (*insertar)(tLista* pl, const void* info,
//                                         unsigned cantBytes));
//int cargarArchivoOrdenadoEnLista(tLista* l, unsigned tamDato,
//                                 const char* nombreArch,
//                                 int(*cmp)(const void*, const void*));

///--------------------------Funciones de mostrar-------------------------------
void mostrarListaGenerica(const tLista* pl, void(*mostrar)(const void* info));
void mostrarNumero(const void* numero);
void mostrarListaAlRevesRecursiva(const tLista* pl,
                                  void(*mostrar)(const void* info));
void mostrarListaRecursiva(const tLista* pl, void(*mostrar)(const void* info));
void mostrarMateria(const void* materia);

///--------------------------Funciones de sacar---------------------------------
int sacarUltimo(tLista* pl, void* info, unsigned cantBytes);
int sacarPrimero(tLista* pl, void* info, unsigned cantBytes);
int sacarPorPosicion(tLista* pl, int posicion, void* info, unsigned cantBytes);
int eliminarApariciones(tLista* pl, const void* elemento,
                        int(*cmp)(const void*, const void*));
int eliminarAparicionesGrabandoTxt(tLista* pl, FILE** archivo, const void* elemento,
                                    int(*cmp)(const void*, const void*),
                                   void(*grabar)(FILE**, const void*));

///--------------------------Funciones de busqueda------------------------------
tNodo* buscarPrimeraAparicion(const tLista*, const void* elemento,
                              int(*cmp)(const void*, const void*));
tLista* buscarMenor(tLista* pl, int(*cmp)(const void*, const void*));

/** \brief funcion que busca por un elemento comparando con una clave
 *
 * \param pl tLista*: puntero a la lista que buscaremos
 * \param clave const void* comparar con cierta clave
 * \param info void*: traer la info del nodo en caso de coincidencia
 * \param eliminarNodo int: 1 o 0 si se debe eliminar el nodo o no
 * \param cmp int: funcion de comparacion
 * \return int retorna 1 o 0 (operacion exitosa/fallida)
 *
 */

int buscarPorClave(tLista* pl, const void* clave, void* info, int eliminarNodo,
                   int(*cmp)(const void*, const void*));
int buscarPorClaveRecursiva(tLista* pl, const void* clave, void* info,
                            int eliminarNodo, int(*cmp)(const void*, const void*));
int contarPorClave(tLista* pl, const void* clave, int eliminarNodo,
                   int(*cmp)(const void*, const void*));
int contarPorClaveRecursiva(tLista* pl, const void* clave, int eliminarNodo,
                            int(*cmp)(const void*, const void*));
int buscarNPorClave(tLista* pl, const void* clave, void* info, int n,
                    int eliminarNodo, int(*cmp)(const void*, const void*));
int buscarNPorClaveRecursiva(tLista* pl, const void* clave, void* info, int n,
                            int eliminarNodo, int(*cmp)(const void*, const void*));

///--------------------------Funciones de actualizacion-------------------------
//actualizarEnLista
//actualizarProducto


///--------------------------Funciones de acumulacion---------------------------
void acumularProductos(void* productoLista, const void* productoAAcumular);
//acumularApariciones
//acumularNumero


///--------------------------Funciones de ordenamiento--------------------------
void ordenarListaPorSeleccion(tLista* pl, int(* cmp)(const void*, const void*));


///--------------------------Funciones clasicas de recorrido--------------------
//map
//filter
//reduce


///--------------------------Funciones recursivas-------------------------------
//mapRecursivo
//filterRecursivo
//reduceRecursivo


///--------------------------Funciones de comparacion---------------------------
int cmpEnteros(const void* a, const void* b);
int cmpCodigoProductos(const void* a, const void* b);
int cmpClaveMateria(const void* a, const void* b);

#endif // LISTASIMPLE_H_INCLUDED
