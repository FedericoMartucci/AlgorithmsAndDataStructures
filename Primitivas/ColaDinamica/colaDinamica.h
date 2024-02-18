#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(X, Y) (X < Y ? X : Y)

#define OK 0
#define MEM_ERR -1
#define COLA_VACIA -2

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef struct
{
    tNodo* pri;
    tNodo* ult;
}tCola;

void crearCola(tCola* pc);
int insertarEnCola(tCola* pc, const void* info, unsigned tamInfo);
int sacarDeCola(tCola* pc, void* info, unsigned tamInfo);
int verTopeCola(const tCola* pc, void* info, unsigned tamInfo);
int colaLlena(const tCola* pc, unsigned tamInfo);
int colaVacia(const tCola* pc);
void vaciarCola(tCola* pc);

#endif // COLADINAMICA_H_INCLUDED
