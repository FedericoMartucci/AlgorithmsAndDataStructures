#ifndef COLAESTATICA_H_INCLUDED
#define COLAESTATICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(X, Y) (X < Y ? X : Y)

#define OK 0
#define MEM_ERR -1
#define COLA_VACIA -2

#define TAM_COLA 68

typedef struct
{
    char cola[TAM_COLA];
    unsigned pri;
    unsigned ult;
    unsigned tamDisp;
}tCola;

void crearCola(tCola* pc);
int insertarEnCola(tCola* pc, const void* info, unsigned tamInfo);
int sacarDeCola(tCola* pc, void* info, unsigned tamInfo);
int verTopeCola(const tCola* pc, void* info, unsigned tamInfo);
int colaLlena(const tCola* pc, unsigned tamInfo);
int colaVacia(const tCola* pc);
void vaciarCola(tCola* pc);


///Funciones de menu
void procesarOpcion(int opcion, tCola* pc);


#endif // COLAESTATICA_H_INCLUDED
