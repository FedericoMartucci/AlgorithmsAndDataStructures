#include "pila.h"
void crearPila(tPila* pp)
{
    *pp = NULL;
}

int ponerEnPila(tPila* pp, const void* info, unsigned tamInfo)
{
    tNodo* nuevoNodo;
    if((nuevoNodo = (tNodo*)malloc(sizeof(tNodo))) == NULL ||
        (nuevoNodo->info = malloc(tamInfo)) == NULL)
    {
        free(nuevoNodo);
        return MEM_ERR;
    }
    memcpy(nuevoNodo->info, info, tamInfo);
    nuevoNodo->tamInfo = tamInfo;
    nuevoNodo->sig = *pp;
    *pp = nuevoNodo;

    return OK;
}

int sacarDePila(tPila* pp, void* info, unsigned tamInfo)
{
    tNodo* nodoAEliminar;
    if(!*pp)
        return PILA_VACIA;

    nodoAEliminar = *pp;

    memcpy(info, nodoAEliminar->info, MINIMO(tamInfo, nodoAEliminar->tamInfo));
    *pp = nodoAEliminar->sig;

    free(nodoAEliminar->info);
    free(nodoAEliminar);

    return OK;
}

int verTopePila(const tPila* pp, void* info, unsigned tamInfo)
{
    if(!*pp)
        return PILA_VACIA;

    memcpy(info, (*pp)->info, MINIMO(tamInfo, (*pp)->tamInfo));

    return OK;
}

int pilaVacia(const tPila* pp)
{
    return *pp == NULL;
}

int pilaLlena(const tPila* pp, unsigned tamInfo)
{
    void* nuevoNodo = malloc(sizeof(tNodo));
    void* infoNuevoNodo = malloc(tamInfo);

    free(nuevoNodo);
    free(infoNuevoNodo);

    return !nuevoNodo || !infoNuevoNodo;
}

void vaciarPila(tPila* pp)
{
    tNodo* elim;

    while(*pp)
    {
        elim = *pp;
        *pp = elim->sig;
        free(elim->info);
        free(elim);
    }
}
