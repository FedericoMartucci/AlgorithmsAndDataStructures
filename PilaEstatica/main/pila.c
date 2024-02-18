#include "pila.h"

void crearPila(tPila* pila)
{
    pila->tope = TAM_PILA;
}
int ponerEnPila(tPila* pila, const void* dato, unsigned tamDato)
{
    if(pila->tope < tamDato + sizeof(unsigned))
        return MEM_ERR;

    pila->tope -= tamDato;
    memcpy(pila->pila + pila->tope, dato, tamDato);
    pila->tope -= sizeof(unsigned);
    memcpy(pila->pila + pila->tope, &tamDato, sizeof(unsigned));

    return OK;
}
int sacarDePila(tPila* pila, void* dato, unsigned tamDato)
{
    unsigned tamInfo;

    if(pila->tope == TAM_PILA)
        return PILA_VACIA;

    memcpy(&tamInfo, pila->pila + pila->tope, sizeof(unsigned));
    pila->tope += sizeof(unsigned);
    memcpy(dato, pila->pila + pila->tope, MINIMO(tamInfo, tamDato));
    pila->tope += tamInfo;

    return OK;
}
int verTope(const tPila* pila, void* dato, unsigned tamDato)
{
    unsigned tamInfo;

    if(pila->tope == TAM_PILA)
        return PILA_VACIA;

    memcpy(&tamInfo, pila->pila + pila->tope, sizeof(unsigned));
    memcpy(dato, pila->pila + pila->tope + sizeof(unsigned), MINIMO(tamInfo, tamDato));

    return OK;
}
int pilaVacia(const tPila* pila)
{
    return pila->tope == TAM_PILA;
}
int pilaLlena(const tPila* pila, unsigned tamDato)
{
    return pila->tope < tamDato + sizeof(unsigned);
}
void vaciarPila(tPila* pila)
{
    pila->tope = TAM_PILA;
}
