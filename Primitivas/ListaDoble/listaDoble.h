#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_ERR -1
#define OK 1

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* ant;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* pl);
void vaciarLista(tLista* pl);
int ordenarLista(tLista* pl, int(*cmp)(const void*, const void*));
tLista* buscarMenor(tLista* pl, int(*cmp)(const void*, const void*));
int insertarOrdenado(tLista* pl, const void* info, unsigned cantBytes,
                     int(*cmp)(const void*, const void*));
int insertarAlInicio(tLista* pl, const void* info, unsigned cantBytes);
int insertarAlFinal(tLista* pl, const void* info, unsigned cantBytes);
int listaVacia(const tLista* pl);
int listaLlena(const tLista* pl, unsigned cantBytes);
int mmap(tLista* pl, void(*accion)(void*));
int ffilter(tLista* pl, void(*filtro)(void*));
int rreduce(tLista* pl, void(*reductor)(void*), void* redu);

///Mostrar
void mostrarIzqADer(tLista* pl, void(*mostrar)(const void*));
void mostrarDerAIzq(tLista* pl, void(*mostrar)(const void*));

void mostrarEntero(const void* num);

///Comparar
int cmpEnteros(const void* a, const void* b);

#endif // LISTADOBLE_H_INCLUDED
