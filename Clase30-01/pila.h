#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define MINIMO(X, Y) (X < Y? X : Y)

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;//puede ser size-t
    struct sNodo* sig;
}tNodo;

typedef tNodo* tPila;

int pilaVacia(const tPila* pp);
int pilaLlena(const tPila* pp, unsigned tamDato);
void crearPila(tPila* pp);
int ponerEnPila(tPila* pp, const void* dato, unsigned tamDato);
int sacarDePila(tPila* pp, void* dato, unsigned tamDato);
int verTopePila(const tPila* pp, void* dato, unsigned tamDato);
void vaciarPila(tPila* pp);


#endif // PILA_H_INCLUDED
