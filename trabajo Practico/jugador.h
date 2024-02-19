#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define NOMBRE_MAX 50
typedef struct{
        char nombre[NOMBRE_MAX];
        int turno;
}tJugador;

typedef struct{
    int* posiciones;
    int actual;
}tOrden;

int inicializarOrden(tOrden* orden,int cant);
void mezclarJugadores(tOrden* orden, int cant);
void liberarOrden(tOrden* orden);

int compararTurnos(const void* d1,const void* d2);
void mostrarJugador(void* dato);
void cambiarTurnos(void* jugador,void *dato);

#endif // JUGADOR_H_INCLUDED
