#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define NOMBRE_MAX 50

typedef struct
{
    char nombre[NOMBRE_MAX];
    int turno;
} tJugador;

typedef struct
{
    int posRealRegistro;
    int posSorteado;
} tOrden;

int compararTurnos(const void* jugador1, const void* jugador2);
void mostrarJugador(void* dato);
void imprimirNombreJugador(void* jugador, void *salida);

int inicializarOrden(tOrden** orden, int cant);
void mezclarJugadores(tOrden* orden, int cant);
void ordenarPorInsercionPorDatoSorteo(tOrden* vec, int ce);
void liberarOrden(tOrden* orden);

#endif // JUGADOR_H_INCLUDED
