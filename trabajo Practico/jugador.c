#include "jugador.h"

int compararTurnos(const void* d1,const void* d2)
{
    const tJugador* dato1=d1;
    const tJugador* dato2=d2;
    return dato1->turno-dato2->turno;
}
void mostrarJugador(void* dato)
{
    tJugador* jugador=dato;
    printf("turno:%d nombre:%s\n",jugador->turno,jugador->nombre);
}

void cambiarTurnos(void* jugador,void *dato)
{
    tJugador* pJugador=jugador;
    tOrden* orden=dato;
    pJugador->turno=orden->posiciones[orden->actual];
    orden->actual++;
}

int inicializarOrden(tOrden* orden,int cant)
{
    orden->actual=0;
    orden->posiciones = malloc(sizeof(int) * cant);

    if(!orden->posiciones)
        return 0;

    for(int i = 0; i < cant; i++)
        orden->posiciones[i] = i + 1;

    return 1;
}

void intercambiar(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void mezclar(int *vec, int ce)
{
    int i,
        j;

    for(i = ce - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        intercambiar((vec + i), (vec + j));
        if(((j % 2) == 1) && (i == j))
            i++;
    }
}

void ramdomizarOrden(tOrden* orden,int cant)
{
    mezclar(orden->posiciones,cant);
}


void liberarOrden(tOrden* orden)
{
    free(orden->posiciones);
}