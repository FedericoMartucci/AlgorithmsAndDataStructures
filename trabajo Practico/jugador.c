#include "jugador.h"

int compararTurnos(const void* jugador1, const void* jugador2)
{
    return ((tJugador*)jugador1)->turno - ((tJugador*)jugador2)->turno;
}

void mostrarJugador(const void* jugador)
{
    printf("Turno %d - Jugador: %s\n",
           ((tJugador*)jugador)->turno,
           ((tJugador*)jugador)->nombre);
}

void imprimirNombreJugador(const void* jugador,void *salida){
    fprintf((FILE*) salida, "%-17s\t", ((tJugador*)jugador)->nombre);
}

void cambiarTurnos(void* jugador, void *dato)
{
    tJugador* pJugador = jugador;
    tOrden* orden = dato;

    pJugador->turno = orden->posiciones[orden->actual];
    orden->actual ++;
}

int inicializarOrden(tOrden* orden, int cant)
{
    int i;

    orden->actual = 0;
    orden->posiciones = malloc(sizeof(int) * cant);

    if(!orden->posiciones)
        return 0;

    for(i = 0; i < cant; i ++)
        orden->posiciones[i] = i + 1;

    return 1;
}

void intercambiar(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void mezclar(int *vec, int cantidadElementos)
{
    int i,
        j;

    for(i = cantidadElementos - 1; i > 0; i --)
    {
        j = rand() % (i + 1);
        intercambiar((vec + i), (vec + j));
        if(((j % 2) == 1) && (i == j))
            i++;
    }
}

void mezclarJugadores(tOrden* orden, int cant)
{
    mezclar(orden->posiciones, cant);
}


void liberarOrden(tOrden* orden)
{
    free(orden->posiciones);
}
