#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(X, Y) (X < Y? X : Y)

#define OK 0
#define MEM_ERR -1
#define PILA_VACIA -2

#define TAM_PILA 100

typedef struct
{
    char pila[TAM_PILA];
    unsigned tope;
}tPila;

void crearPila(tPila* pila);
int ponerEnPila(tPila* pila, const void* dato, unsigned tamDato);
int sacarDePila(tPila* pila, void* dato, unsigned tamDato);
int verTope(const tPila* pila, void* dato, unsigned tamDato);
int pilaVacia(const tPila* pila);
int pilaLlena(const tPila* pila, unsigned tamDato);
void vaciarPila(tPila* pila);

#endif // PILA_H_INCLUDED
