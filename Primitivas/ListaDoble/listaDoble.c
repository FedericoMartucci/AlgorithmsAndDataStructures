#include "listaDoble.h"

void crearLista(tLista* pl)
{
    *pl = NULL;
}

void vaciarLista(tLista* pl)
{
    tNodo* nodoAEliminar;
    if(*pl)
        while((*pl)->ant)
            *pl = (*pl)->ant;
    while(*pl)
    {
        nodoAEliminar = *pl;
        *pl = nodoAEliminar->sig;
        free(nodoAEliminar->info);
        free(nodoAEliminar);
    }
}

int ordenarLista(tLista* pl, int(* cmp)(const void*, const void*))
{
    tLista* menor;
    tNodo* nodoAuxiliar;

    if(*pl)
        while((*pl)->ant)
            *pl = (*pl)->ant;

    while(*pl)
    {
        menor = buscarMenor(pl, cmp);
        if(pl != menor)
        {
            (*menor)->ant = (*pl)->ant;
            (*pl)->ant = *menor;
            nodoAuxiliar = *menor;
            menor = &(*menor)->sig;
            nodoAuxiliar->sig = *pl;
        }
        else
            *pl = (*pl)->sig;
    }

    return OK;
}

tLista* buscarMenor(tLista* pl, int(*cmp)(const void*, const void*))
{
    tLista* menor;

    menor = pl;
    pl = &(*pl)->sig;
    while(*pl)
    {
        if(cmp((*menor)->info, (*pl)->info) < 0)
            menor = pl;
        pl = &(*pl)->sig;
    }

    return menor;
}

int insertarOrdenado(tLista* pl, const void* info, unsigned cantBytes, int(* cmp)(const void*, const void*))
{
    return OK;
}

int insertarAlInicio(tLista* pl, const void* info, unsigned cantBytes)
{
    tNodo* nuevoNodo;

    if((nuevoNodo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
            (nuevoNodo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevoNodo);
        return MEM_ERR;
    }
    if(*pl)
        while((*pl)->ant)
            *pl = (*pl)->ant;

    memcpy(nuevoNodo->info, info, cantBytes);
    nuevoNodo->tamInfo = cantBytes;
    nuevoNodo->sig = *pl;
    nuevoNodo->ant = NULL;
    if((*pl))
        (*pl)->ant = nuevoNodo;
    *pl = nuevoNodo;

    return OK;
}

int insertarAlFinal(tLista* pl, const void* info, unsigned cantBytes)
{
    tNodo* nuevoNodo;

    if((nuevoNodo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
            (nuevoNodo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevoNodo);
        return MEM_ERR;
    }
    if(*pl)
        while((*pl)->sig)
            *pl = (*pl)->sig;

    memcpy(nuevoNodo->info, info, cantBytes);
    nuevoNodo->tamInfo = cantBytes;
    nuevoNodo->ant = *pl;
    nuevoNodo->sig = NULL;
    if((*pl))
        (*pl)->sig = nuevoNodo;
    *pl = nuevoNodo;

    return OK;
}

int listaVacia(const tLista* pl)
{
    return OK;
}

int listaLlena(const tLista* pl, unsigned cantBytes)
{
    return OK;
}

int mmap(tLista* pl, void(*accion)(void*))
{
    return OK;
}

int ffilter(tLista* pl, void(*filtro)(void*))
{
    return OK;
}

int rreduce(tLista* pl, void(*reductor)(void*), void* redu)
{
    return OK;
}


void mostrarIzqADer(tLista* pl, void(*mostrar)(const void*))
{
    if(*pl)
    {

        while((*pl)->ant)
            pl = &(*pl)->ant;
        while(*pl)
        {
            mostrar((*pl)->info);
            pl = &(*pl)->sig;
        }
    }
}
void mostrarDerAIzq(tLista* pl, void(*mostrar)(const void*))
{
    if(*pl)
    {

        while((*pl)->sig)
            pl = &(*pl)->sig;
        while(*pl)
        {
            mostrar((*pl)->info);
            pl = &(*pl)->ant;
        }
    }
}

void mostrarEntero(const void* num)
{
    fprintf(stdout, "%d ", *(int*)num);
}

///Comparar
int cmpEnteros(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}
