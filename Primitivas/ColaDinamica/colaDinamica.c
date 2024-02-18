#include "colaDinamica.h"

void crearCola(tCola* pc)
{
    pc->pri = NULL;
    pc->ult = NULL;
}

int insertarEnCola(tCola* pc, const void* info, unsigned tamInfo)
{
    tNodo* nuevoNodo;
    if((nuevoNodo = (tNodo*)malloc(sizeof(tNodo))) == NULL ||
    (nuevoNodo->info = malloc(tamInfo)) == NULL){
        free(nuevoNodo);
        return MEM_ERR;
    }

    memcpy(nuevoNodo->info, info, tamInfo);
    nuevoNodo->tamInfo = tamInfo;
    nuevoNodo->sig = NULL;

    if(pc->ult)
        pc->ult->sig = nuevoNodo;
    else
        pc->pri = nuevoNodo;

    pc->ult = nuevoNodo;

    return OK;
}

int sacarDeCola(tCola* pc, void* info, unsigned tamInfo)
{
    tNodo* nodoAELiminar;
    if(pc->pri == NULL)
        return COLA_VACIA;

    nodoAELiminar = (pc)->pri;
    memcpy(info, nodoAELiminar->info, MINIMO(tamInfo, nodoAELiminar->tamInfo));
    pc->pri = nodoAELiminar->sig;

    if(pc->pri == NULL)//pc->ult == nodoAELiminar
        pc->ult = NULL;

    free(nodoAELiminar->info);
    free(nodoAELiminar);

    return OK;
}

int verTopeCola(const tCola* pc, void* info, unsigned tamInfo)
{
    if(pc->pri == NULL)
        return COLA_VACIA;

    memcpy(info, pc->pri->info, MINIMO(tamInfo, pc->pri->tamInfo));

    return OK;
}

int colaLlena(const tCola* pc, unsigned tamInfo)
{
    tNodo* nuevoNodo = (tNodo*)malloc(sizeof(tNodo));
    void* infoNuevoNodo = malloc(tamInfo);

    free(nuevoNodo);
    free(infoNuevoNodo);

    return !nuevoNodo || !infoNuevoNodo;
}

int colaVacia(const tCola* pc)
{
    return pc->pri == NULL;
}

void vaciarCola(tCola* pc)
{
    tNodo* nodoAELiminar;

    while(pc->pri){
        nodoAELiminar = pc->pri;
        pc->pri = nodoAELiminar->sig;
        free(nodoAELiminar->info);
        free(nodoAELiminar);
    }
    pc->ult = NULL;
}
