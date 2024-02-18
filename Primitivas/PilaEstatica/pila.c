#include "pila.h"
void crearPila(tPila* pp)
{
    pp->tope = TAM_PILA;
}

int ponerEnPila(tPila* pp, const void* info, unsigned tamInfo)
{
    if(pp->tope < sizeof(unsigned) + tamInfo)
        return MEM_ERR;

    pp->tope -= tamInfo;
    memcpy(pp->pila + pp->tope, info, tamInfo);
    pp->tope -= sizeof(unsigned);
    memcpy(pp->pila + pp->tope, &tamInfo, sizeof(unsigned));

    return OK;
}

int sacarDePila(tPila* pp, void* info, unsigned tamInfo)
{
    unsigned tamInfoEnPila;
    if(pp->tope == TAM_PILA)
        return PILA_VACIA;

    memcpy(&tamInfoEnPila, pp->pila + pp->tope, sizeof(unsigned));
    pp->tope += sizeof(unsigned);
    memcpy(info, pp->pila + pp->tope, MINIMO(tamInfo, tamInfoEnPila));
    pp->tope += tamInfoEnPila;

    return OK;
}

int verTopePila(const tPila* pp, void* info, unsigned tamInfo)
{
    unsigned tamInfoEnPila;
    if(pp->tope == TAM_PILA)
        return PILA_VACIA;

    memcpy(&tamInfoEnPila, pp->pila + pp->tope, sizeof(unsigned));
    memcpy(info, pp->pila + pp->tope + sizeof(unsigned),
           MINIMO(tamInfo, tamInfoEnPila));

    return OK;
}

int pilaVacia(const tPila* pp)
{
    return pp->tope == TAM_PILA;
}

int pilaLlena(const tPila* pp, unsigned tamInfo)
{
    return pp->tope < sizeof(unsigned) + tamInfo;
}

void vaciarPila(tPila* pp)
{
    pp->tope = TAM_PILA;
}
