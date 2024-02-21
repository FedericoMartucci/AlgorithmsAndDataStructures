#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(X, Y) ((X) < (Y)? (X) : (Y))

#define FALSE 0
#define TRUE 1

#define ERROR 0
#define TODO_OK 1
#define SIN_ELEMENTOS 2
#define SIN_MEMORIA 3
#define ELIMINARON_ELEMENTOS 4
#define INGRESO_MAS_ELEMENTO 5
#define CLAVE_DUP 6

#define NO_ENCONTRADO 0

typedef struct sNodo_a
{
    void* dato;
    unsigned tam;
    struct sNodo_a* izq;        //hijo izquierdo
    struct sNodo_a* der;          //hijo derecho
}tNodo;

typedef tNodo* tArbol;

typedef int (*Cmp)(const void*, const void*);
typedef void (*Accion)(void*);
typedef void (*Accion2)(void*, void*);
typedef void (*fReduce)(void*, const void*);    //dato a acumular- dato de la lista
typedef unsigned (*Leer)(void*, void*, unsigned, unsigned);

void crearArbol(tArbol* pa);
int arbolVacio(tArbol* pa);
int insertarEnArbolRecursivo(tArbol*p, void *d, unsigned tam, Cmp comp);
void mapInOrden(tArbol* pa, Accion accion);
void mapInOrdenConContexto(tArbol* pa, void* contexto, Accion2 accion);
void ordenarArbolBinario(tArbol* pa, Cmp cmp);
void vaciarArbol(tArbol *pa);
int obtenerDatoPorClaveArbol(tArbol *pa, void *d, unsigned tam, Cmp cmp);
int cargarDatosOrdenadosRecursivos(tArbol* pa, void* datos, Leer leer, int li,
                                   int ls, unsigned tam);
unsigned alturaArbol(tArbol* pa);

#endif // ARBOL_H_INCLUDED
