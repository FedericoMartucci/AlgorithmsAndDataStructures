#include "jugador.h"

int compararTurnos(const void* jugador1, const void* jugador2)
{
    return ((tJugador*)jugador1)->turno - ((tJugador*)jugador2)->turno;
}

void mostrarJugador(void* jugador)
{
    printf("Turno %d - Jugador: %s\n",
           ((tJugador*)jugador)->turno,
           ((tJugador*)jugador)->nombre);
}

void imprimirNombreJugador(void* jugador, void* salida)
{
    fprintf((FILE*) salida, "%-17s\t", ((tJugador*)jugador)->nombre);
}

int inicializarOrden(tOrden** orden, int cant)
{
    int i;
    tOrden* nueOrden = malloc(sizeof(tOrden) * cant);

    if(nueOrden == NULL)
        return 0;

    for(i = 0; i < cant; i ++)
    {
        nueOrden[i].posRealRegistro = i;
        nueOrden[i].posSorteado = i + 1;
    }

    *orden = nueOrden;

    return 1;
}

void intercambiar(int* a, int* b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void mezclar(tOrden* vec, int ce)
{
    int i;
    int j;

    for(i = ce - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        intercambiar(&(vec[i].posSorteado), &(vec [j].posSorteado));
        if(((j % 2) == 1) && (i == j))
            i++;
    }
}

void ordenarPorInsercionPorDatoSorteo(tOrden* vec, int ce)
{
    int i;
    int j;
    tOrden* menor;
    tOrden aux;

    if(vec == NULL)
        return;

    for(i = 0; i < ce; i ++)
    {
        menor = &vec[i];
        for(j = i; j < ce; j ++)
            if(vec[j].posSorteado < menor->posSorteado)
                menor = &vec[j];

        aux = vec[i];
        vec[i] = *menor;
        *menor = aux;
    }
}

void mezclarJugadores(tOrden* orden, int cant)
{
    mezclar(orden, cant);
}


void liberarOrden(tOrden* orden)
{
    free(orden);
    orden = NULL;
}
