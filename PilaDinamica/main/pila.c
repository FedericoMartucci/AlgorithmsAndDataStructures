#include "pila.h"

void crearPila(tPila* pila)
{
    *pila = NULL;
}
int ponerEnPila(tPila* pila, const void* dato, unsigned tamDato)
{
     tNodo* nuevoNodo;

    if((nuevoNodo = malloc(sizeof(tNodo))) == NULL ||
       (nuevoNodo->dato = malloc(tamDato)) == NULL){
        free(nuevoNodo);
        return MEM_ERR;
    }

    memcpy(nuevoNodo->dato, dato, tamDato);
    nuevoNodo->tamDato = tamDato;
    nuevoNodo->sig = *pila;

    *pila = nuevoNodo;

    return OK;
}
int sacarDePila(tPila* pila, void* dato, unsigned tamDato)
{

    tNodo* nodoAEliminar;

    if(!*pila)
        return PILA_VACIA;

    nodoAEliminar = *pila;
    memcpy(dato, nodoAEliminar->dato, MINIMO(tamDato, nodoAEliminar->tamDato));
    *pila = nodoAEliminar->sig;

    free(nodoAEliminar->dato);
    free(nodoAEliminar);

    return OK;
}
int verTope(const tPila* pila, void* dato, unsigned tamDato)
{
    if(!*pila)
        return PILA_VACIA;

    memcpy(dato, (*pila)->dato, MINIMO(tamDato, (*pila)->tamDato));

    return OK;
}
int pilaVacia(const tPila* pila)
{
    return *pila == NULL;
}
int pilaLlena(const tPila* pila, unsigned tamDato)
{
    void* nuevoNodo = malloc(sizeof(tNodo));
    void* dato = malloc(tamDato);

    free(nuevoNodo);
    free(dato);

    return !dato || !nuevoNodo;
}
void vaciarPila(tPila* pila)
{
    tNodo* nodoAEliminar;

    while(*pila){
        nodoAEliminar = *pila;
        *pila = nodoAEliminar->sig;
        free(nodoAEliminar->dato);
        free(nodoAEliminar);
    }
}
