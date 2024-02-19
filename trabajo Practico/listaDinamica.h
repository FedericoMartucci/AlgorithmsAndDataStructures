#ifndef LISTADINAMICA_H_INCLUDED
#define LISTADINAMICA_H_INCLUDED

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(x,y) ( (x)<(y)? (x) : (y) )

#define FALSE 0
#define TRUE 1
#define SIN_MEMORIA 3
#define SIN_ELEMENTOS 2
#define TODO_OK 1
#define ERROR 0
#define INGRESO_MAS_ELEMENTO 5
#define ELIMINARON_ELEMENTOS 4
#define NO_ENCONTRADO 0

typedef struct sNodo{
    void* dato;
    unsigned tam;
    struct sNodo *sig;
}tNodo;

typedef tNodo* tLista;

typedef int (*Cmp)(const void*,const void*);
typedef void (*Accion)(void*);
typedef void (*Accion2)(void*,void*);
typedef void (*fReduce)(void*,const void*);    //dato a acumular- dato de la lista

void crearLista(tLista* l);
int listaVacia(const tLista* l);
int listaLlena(const tLista* l, unsigned tam);
void vaciarLista(tLista* l);
int verPrimeroLista(const tLista* l, void* dato, unsigned tam);
int verUltimoLista(const tLista* l, void* dato, unsigned tam);
int ponerEnPrimero(tLista* l, const void* dato, unsigned tam);
int ponerEnUltimo(tLista* l, const void* dato, unsigned tam);
int sacarElPrimero(tLista* l, void* dato, unsigned tam);
int sacarElUltimo(tLista* l, void* dato, unsigned tam);
int recorrerLista(tLista*l, Accion accion);
int recorrerLista2(tLista*l, void* contexto, Accion2 accion);
void insertarPorPosicion(tLista* l, void* dato, unsigned tam, int pos);
int insertarOrdenado(tLista* l, const void* dato, unsigned tam, Cmp cmp);

void filtrarLista(tLista* l, const void* dato, Cmp cmp);

int eliminarDatoListaOrdenada(tLista* l, void* dato, unsigned tam, Cmp cmp);
/**
funcion llamadora, es la funcion la que la llama, normalmente el inicio de todo
*/
tNodo** buscarMenor(tLista* l, Cmp cmp);
void ordenarLista(tLista* pl, Cmp cmp);
void ordenarLista2(tLista* pl, Cmp cmp);
void reducirLista(tLista* pl, fReduce reduce, void* valorReduce);   //valorReduce: aca se guardan los datos que pasan por la lista

//falta hacer
void agruparDatosRepetidos(tLista* pl, Cmp cmp);
int eliminarNUltimos(tLista* pl, int n);        //devuelve si es 0 es que se borraron todos los elementos, si sobra es el exceso

int buscarDatoPorClave(tLista* pl, void* dato, unsigned tam, Cmp cmp);
int obtenerDatoPorIndex(tLista* pl, void* dato, unsigned tam, unsigned index);
int obtenerDirrecionDatoPorIndex(tLista* pl, void* dato, unsigned tam, unsigned index);

#endif // LISTADINAMICA_H_INCLUDED
