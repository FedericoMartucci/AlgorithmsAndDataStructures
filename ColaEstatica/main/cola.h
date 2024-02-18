#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_COLA 500

#define COLA_VACIA 0
#define minimo(X,Y) (((X)>(Y))? (Y) : (X) )

typedef struct
{
    unsigned pri;
    unsigned ult;
    unsigned tamDis;
    char cola[TAM_COLA];
}tCola;

void crearCola(tCola *c);
int ponerEnCola(tCola* c,const void* d, unsigned tam);
int sacarDeCola(tCola* c, void* d, unsigned tam);
int colaVacia(const tCola* c);
int colaLlena(const tCola* c, size_t tam);
void vaciarCola(tCola* c);
int verPrimero(const tCola *c, void*d ,size_t tam );


#endif // COLA_H_INCLUDED
