#include "arbol.h"

void crearArbol(tArbol* a)
{
    *a = NULL;
}

int insertarArbolIterativo(tArbol* a, const void* dato, unsigned cantBytes,
                           int(* cmp)(const void*, const void*))
{
    tNodoArbol* nuevoNodo;
    int resultadoComparacion;

    if((nuevoNodo = (tNodoArbol*) malloc(sizeof(tNodoArbol))) == NULL ||
            (nuevoNodo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevoNodo);
        return SIN_MEM;
    }

    while(*a)
    {
        resultadoComparacion = cmp(dato, (*a)->info);
        if(resultadoComparacion > 0)
            a = &(*a)->der;
        else if(resultadoComparacion < 0)
            a = &(*a)->izq;
        else
        {
            free(nuevoNodo->info);
            free(nuevoNodo);
            return CLA_DUP;
        }
    }

    memcpy(nuevoNodo->info, dato, cantBytes);
    nuevoNodo->tamInfo = cantBytes;
    nuevoNodo->izq = nuevoNodo->der = NULL;
    *a = nuevoNodo;

    return TODO_BIEN;
}

int insertarArbolRecursivo(tArbol* a, const void* dato, unsigned cantBytes,
                           int(* cmp)(const void*, const void*))
{
    tNodoArbol* nuevoNodo;
    int resultadoComparacion;

    if(!*a)
    {
        if((nuevoNodo = (tNodoArbol*) malloc(sizeof(tNodoArbol))) == NULL ||
                (nuevoNodo->info = malloc(cantBytes)) == NULL)
        {
            free(nuevoNodo);
            return SIN_MEM;
        }
        memcpy(nuevoNodo->info, dato, cantBytes);
        nuevoNodo->tamInfo = cantBytes;
        nuevoNodo->izq = nuevoNodo->der = NULL;
        *a = nuevoNodo;
    }
    else
    {
        resultadoComparacion = cmp(dato, (*a)->info);
        if(resultadoComparacion > 0)
            return insertarArbolRecursivo(&(*a)->der, dato, cantBytes, cmp);
        else if(resultadoComparacion < 0)
            return insertarArbolRecursivo(&(*a)->izq, dato, cantBytes, cmp);
        else
            return CLA_DUP;
    }
    return TODO_BIEN;
}

int arbolVacio(const tArbol* a)
{
    return *a == NULL;
}

int alturaArbol(tArbol* a)
{
    int alturaIzquierda;
    int alturaDerecha;

    if(!*a)
        return 0;

    alturaIzquierda = alturaArbol(&(*a)->izq);
    alturaDerecha = alturaArbol(&(*a)->der);

    return alturaIzquierda > alturaDerecha? alturaIzquierda + 1 : alturaDerecha + 1;
}

int contarNodos(tArbol* a)
{
//    if(!*a)
//        return 0;
//    return contarNodos(&(*a)->izq) + contarNodos(&(*a)->der) + 1;
    return *a? (contarNodos(&(*a)->izq) + contarNodos(&(*a)->der) + 1) : 0;
}

void mostrarNodosHoja(const tArbol* a)
{
    if(!*a)
        return;
    if(!(*a)->izq && !(*a)->der)
        printf("%d ", *(int*)(*a)->info);
    mostrarNodosHoja(&(*a)->der);
    mostrarNodosHoja(&(*a)->izq);
}

void mostrarNodosNoHoja(const tArbol* a)
{
    if(!*a)
        return;
    if((*a)->izq || (*a)->der)
        printf("%d ", *(int*)(*a)->info);
    mostrarNodosNoHoja(&(*a)->der);
    mostrarNodosNoHoja(&(*a)->izq);
}

void mostrarNodosSoloHijosIzq(const tArbol* a)
{
    if(!*a)
        return;
    if((*a)->izq && !(*a)->der)
        printf("%d ", *(int*)(*a)->info);
    mostrarNodosSoloHijosIzq(&(*a)->der);
    mostrarNodosSoloHijosIzq(&(*a)->izq);
}

void mostrarNodosHijosIzq(const tArbol* a)
{
    if(!*a)
        return;
    if((*a)->izq)
        printf("%d ", *(int*)(*a)->info);
    mostrarNodosHijosIzq(&(*a)->der);
    mostrarNodosHijosIzq(&(*a)->izq);
}

void recorrerArbolEnOrden(tArbol* a, void(* accion)(const void*))
{
    if(!*a)
        return;
    recorrerArbolEnOrden(&(*a)->izq, accion);
    accion((*a)->info);
    recorrerArbolEnOrden(&(*a)->der, accion);
}
void recorrerEnOrdenInversoRecArbolBinBusq(const tArbol * p, unsigned n, void * params,
                                           void (*accion)(void *, unsigned, unsigned, void *))
{
    if(!*p)
        return;
    recorrerEnOrdenInversoRecArbolBinBusq(&(*p)->der, n+1, params, accion);
    accion((*p)->info, (*p)->tamInfo, n, params);
    recorrerEnOrdenInversoRecArbolBinBusq(&(*p)->izq, n+1, params, accion);
}

void recorrerEnOrdenInversoArbolBinBusq(const tArbol * p, void * params,
                                        void (*accion)(void *, unsigned, unsigned, void *))
{
   recorrerEnOrdenInversoRecArbolBinBusq(p, 0, params, accion);
}


void recorrerArbolPreOrden(tArbol* a, void(* accion)(const void*))
{
    if(!*a)
        return;
    accion((*a)->info);
    recorrerArbolPreOrden(&(*a)->izq, accion);
    recorrerArbolPreOrden(&(*a)->der, accion);
}

void recorrerArbolPostOrden(tArbol* a, void(* accion)(const void*))
{
    if(!*a)
        return;
    recorrerArbolPostOrden(&(*a)->izq, accion);
    recorrerArbolPostOrden(&(*a)->der, accion);
    accion((*a)->info);
}

void mostrarEntero(const void* num)
{
    fprintf(stdout, "%d ", *(int*)num);
    //printf("%*s-%3d-\n",n*3,"", *i);
}

void vaciarArbol(tArbol* a)
{
    tNodoArbol* nodoAEliminar;
    if(!*a)
        return;
    vaciarArbol(&(*a)->izq);
    vaciarArbol(&(*a)->der);
    nodoAEliminar = *a;
    *a = NULL;
    free(nodoAEliminar->info);
    free(nodoAEliminar);
}

int esCompletoANivel(const tArbol* a, int n)
//{

}
int esCompleto(const tArbol* a)
{

}
int esBalanceado(const tArbol* a)
{

}
int eliminarRaiz(tArbol* a)
{

}
tNodo** menorNodo(const tArbol* a, int(*cmp)(const void*, const void*))
{
    int resultadoComparacion;

    if(!*a)
        return NULL;

    resultadoComparacion = cmp(clave, (*a)->info);
    if(resultadoComparacion < 0)
        return menorNodo(&(*a)->izq, clave, cmp);
    if(resultadoComparacion > 0)
        return menorNodo(&(*a)->der, clave, cmp);
    if(resultadoComparacion == 0)
        return *a;
}
tNodo** mayorNodo(const tArbol* a, int(*cmp)(const void*, const void*))
{

}
int eliminarNodoPorClave(tArbol *a, void* clave,
                         int(*cmp)(const void* a, const void* b))
{

}
tNodo* buscarPorClave(tArbol* a, void* clave,
                      int(*cmp)(const void* a,const void* b))
{
    int resultadoComparacion;

    if(!*a)
        return NULL;

    resultadoComparacion = cmp(clave, (*a)->info);
    if(resultadoComparacion < 0)
        return buscarPorClave(&(*a)->izq, clave, cmp);
    if(resultadoComparacion > 0)
        return buscarPorClave(&(*a)->der, clave, cmp);
    if(resultadoComparacion == 0)
        return *a;
}


int compararEnteros(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}
