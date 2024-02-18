#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(X, Y) (X < Y ? X : Y)

#define OK 0
#define MEM_ERR -1
#define PILA_VACIA -2

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tPila;

void crearPila(tPila* pp);
int ponerEnPila(tPila* pp, const void* info, unsigned tamInfo);
int sacarDePila(tPila* pp, void* info, unsigned tamInfo);
int verTopePila(const tPila* pp, void* info, unsigned tamInfo);
int pilaVacia(const tPila* pp);
int pilaLlena(const tPila* pp, unsigned tamInfo);
void vaciarPila(tPila* pp);

#endif // PILA_H_INCLUDED
