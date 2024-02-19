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

int inicializarOrden(tOrden* orden, int cant);
void mezclarJugadores(tOrden* orden, int cant);
void liberarOrden(tOrden* orden);

int compararTurnos(const void* jugador1, const void* jugador2);
void mostrarJugador(const void* dato);
void cambiarTurnos(void* jugador, void *dato);
void imprimirNombreJugador(const void* jugador, void *salida);

#endif // JUGADOR_H_INCLUDED
