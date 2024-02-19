#include "arbol.h"

void crearArbol(tArbol* pa)
{
    *pa = NULL;
}

int arbolVacio(tArbol* pa)
{
    return *pa == NULL;
}

int insertarEnArbolRecursivo(tArbol*p, void *d, unsigned tam, Cmp comp)
{
    int cmp;
    if(*p)
    {
        if((cmp = comp(d, &(*p)->dato)) > 0) //averigua donde pasa el arbol
            return insertarEnArbolRecursivo(&(*p)->der, d, tam, comp);
        else if(cmp < 0)
            return insertarEnArbolRecursivo(&(*p)->izq, d, tam, comp);
        else
            return CLAVE_DUP;  //en caso que cmp=0 entonces significa que que hubo una clave duplicada
    }

    tNodo* nue = (tNodo*) malloc(sizeof(tNodo));       //ya que *p=NULL, entonces existe *p, Y se le asigna un espacio de memoria
    if(nue == NULL)
        return SIN_MEMORIA;

    nue->dato = malloc(tam);
    if(nue->dato == NULL)
    {
        free(nue);
        return SIN_MEMORIA;
    }
    memcpy(nue->dato, d, tam);

    nue->izq = NULL;
    nue->der = NULL;       //dado que es el dato es una hoja , entontes no tiene hijos por lo tanto pertenece a NULL
    *p = nue;

    return TODO_OK;
}

void mapInOrden(tArbol* pa, Accion accion)
{
    if(!*pa)     //evalua si la lista esta vacia, ademas evalua , si es un hoja.
        return;

    mapInOrden(&(*pa)->izq, accion);
    accion((*pa)->dato);
    mapInOrden(&(*pa)->der, accion);
}

void mapInOrdenConContexto(tArbol* pa,void* contexto,Accion2 accion)
{
    if(!*pa)     //evalua si la lista esta vacia, ademas evalua , si es un hoja.
        return;

    mapInOrdenConContexto(&(*pa)->izq, contexto, accion);
    accion((*pa)->dato, contexto);
    mapInOrdenConContexto(&(*pa)->der, contexto, accion);
}

void intercambiarDato(tNodo* a, tNodo* b)
{
    void* temp_dato = a->dato;
    unsigned temp_tam = a->tam;

    a->dato = b->dato;
    a->tam = b->tam;
    b->dato = temp_dato;
    b->tam = temp_tam;
}

void ordenarArbolBinario(tArbol* pa, Cmp cmp)
{
    if (*pa == NULL)
        return;

    ordenarArbolBinario(&((*pa)->izq), cmp);

    if ((*pa)->izq != NULL && cmp((*pa)->dato, (*pa)->izq->dato) < 0)
    {
        intercambiarDato(*pa, (*pa)->izq);
        ordenarArbolBinario(&((*pa)->izq), cmp);
    }

    if ((*pa)->der != NULL && cmp((*pa)->dato, (*pa)->der->dato) < 0)
    {
        intercambiarDato(*pa, (*pa)->der);
        ordenarArbolBinario(&((*pa)->der), cmp);
    }

    ordenarArbolBinario(&((*pa)->der), cmp);
}

void vaciarArbol(tArbol *pa)
{
    if(!*pa)
        return;
    if((*pa)->izq)
        vaciarArbol(&(*pa)->izq);
    if((*pa)->der)
        vaciarArbol(&(*pa)->der);

    free((*pa)->dato);
    free(*pa);

    *pa = NULL;
}

tNodo** buscarNodo(tNodo** pa, void *d, Cmp cmp)
{
    if(*pa != NULL)
    {
        if(cmp(d, (*pa)->dato) == 0)
            return pa;
        if(cmp(d, (*pa)->dato) < 0)
            return buscarNodo(&(*pa)->izq, d, cmp);
        if(cmp(d, (*pa)->dato) > 0)
            return buscarNodo(&(*pa)->der, d, cmp);
    }
    return NULL;
}

int obtenerDatoPorClaveArbol(tArbol *pa, void *d, unsigned tam, Cmp cmp)
{
    tNodo** nodo = buscarNodo(pa, d, cmp);        //busca el PUNTERO DEL PUNTERO DEL ELEMENTO A ELIMINAR
    if(nodo == NULL)    //si no lo encontro le devuelve un 0
        return 0;   //FALSO

    memcpy(d, (*nodo)->dato, MINIMO((*nodo)->tam, tam));

    return TODO_OK;
}
