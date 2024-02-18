#include "listaSimple.h"
void crearLista(tLista* pl)
{
    *pl = NULL;
}

void vaciarLista(tLista* pl)
{
    tNodo* nodoAELiminar;

    while(*pl)
    {
        nodoAELiminar = *pl;
        *pl = nodoAELiminar->sig;
        free(nodoAELiminar->info);
        free(nodoAELiminar);
    }
}

int listaVacia(const tLista* pl)
{
    return *pl == NULL;
}

int listaLlena(const tLista* pl, unsigned cantBytes)
{
    tNodo* nuevoNodo = (tNodo*) malloc(sizeof(tNodo));
    void* infoNodo = malloc(cantBytes);

    free(nuevoNodo);
    free(infoNodo);

    return !nuevoNodo || !infoNodo;
}

int insertarAlFinal(tLista* pl, const void* info, unsigned cantBytes)
{
    tNodo* nuevoNodo;

    if((nuevoNodo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
            (nuevoNodo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevoNodo);
        return LISTA_LLENA;
    }

    while(*pl)
        pl = &(*pl)->sig;

    memcpy(nuevoNodo->info, info, cantBytes);
    nuevoNodo->tamInfo = cantBytes;
    nuevoNodo->sig = *pl;
    *pl = nuevoNodo;

    return OK;
}

int insertarAlComienzo(tLista* pl, const void* info, unsigned cantBytes)
{
    tNodo* nuevoNodo;

    if((nuevoNodo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
            (nuevoNodo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevoNodo);
        return LISTA_LLENA;
    }

    memcpy(nuevoNodo->info, info, cantBytes);
    nuevoNodo->tamInfo = cantBytes;
    nuevoNodo->sig = *pl;
    *pl = nuevoNodo;

    return OK;
}

int insertarOrdenado(tLista* pl, const void* info, unsigned cantBytes,
                     int(* cmp)(const void*, const void*))
{
    tNodo* nuevoNodo;

    if((nuevoNodo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
            (nuevoNodo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevoNodo);
        return LISTA_LLENA;
    }

    while(*pl && cmp((*pl)->info, info) < 0)
        pl = &(*pl)->sig;

    memcpy(nuevoNodo->info, info, cantBytes);
    nuevoNodo->tamInfo = cantBytes;
    nuevoNodo->sig = *pl;
    *pl = nuevoNodo;

    return OK;

}
int cargarListaVector(tLista* pl, const void* info, unsigned tamElemento,
                      int cantElementos, int (*insertar)(tLista* pl,
                              const void* info, unsigned cantBytes))
{
    if(!cantElementos)
        return LISTA_VACIA;

    while(--cantElementos > 0)
    {
        insertar(pl, info, tamElemento);
        info = ((char*)info) + tamElemento;
    }
    insertar(pl, info, tamElemento);

    return OK;
}
int insertarOrdenadoAcumulando(tLista* pl, const void* info, unsigned cantBytes,
                               int(*cmp)(const void*, const void*),
                               void(*acumular)(void*, const void*))
{
    tNodo* nuevoNodo;

    while(*pl && cmp((*pl)->info, info) < 0)
    {
        pl = &(*pl)->sig;
    }
    if(!(*pl) || cmp((*pl)->info, info) > 0)
    {
        if((nuevoNodo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
                (nuevoNodo->info = malloc(cantBytes)) == NULL)
        {
            free(nuevoNodo);
            return LISTA_LLENA;
        }
        memcpy(nuevoNodo->info, info, cantBytes);
        nuevoNodo->tamInfo = cantBytes;
        nuevoNodo->sig = *pl;
        *pl = nuevoNodo;
    }
    else
        acumular((*pl)->info, info);

    return OK;
}

int cargarListaVectorFiltrando(tLista* pl, const void* info,
                                  unsigned tamElemento, int cantElementos,
                                  int (*filtrar)(const void*),
                                  int (*insertar)(tLista* pl, const void* info,
                                                  unsigned cantBytes))
{
    int i;
    if(!cantElementos)
        return LISTA_VACIA;

    for(i = 0; i < cantElementos; i++)
    {
        if(filtrar(info)){
            parsearPosicion(i, cf, cc);
            insertar(pl, info, tamElemento);
        }
        info = ((char*)info) + tamElemento;
    }
    if(filtrar(info)){

        insertar(pl, info, tamElemento);
    }

    return OK;
}


///--------------------------Funciones de mostrar-------------------------------
void mostrarListaGenerica(const tLista* pl, void(* mostrar)(const void* info))
{
    while(*pl)
    {
        mostrar((*pl)->info);
        pl = &(*pl)->sig;
    }
}
void mostrarNumero(const void* numero)
{
    fprintf(stdout, "%d ", *((int*)numero));
}

void mostrarMateria(const void* materia)
{
//    printf("Materia: %s\nNombre: %s\nAnio cursada: %d\n",
//           ((tMateria*)materia)->id,
//           ((tMateria*)materia)->nombre,
//           ((tMateria*)materia)->anioCursada);
    printf("Nombre: %s\n", ((tMateria*)materia)->nombre);
}

void mostrarListaAlRevesRecursiva(const tLista* pl, void(* mostrar)(const void* info))
{
    if(!*pl)
        return;
    else
        mostrarListaAlRevesRecursiva(&(*pl)->sig, mostrar);
    mostrar((*pl)->info);
}

void mostrarListaRecursiva(const tLista* pl, void(* mostrar)(const void* info))
{
    if(!*pl)
        return;
    mostrar((*pl)->info);
    mostrarListaRecursiva(&(*pl)->sig, mostrar);
}

int sacarUltimo(tLista* pl, void* info, unsigned cantBytes)
{
    tNodo* nodoAEliminar;
    if(!*pl)
        return LISTA_VACIA;

    while((*pl)->sig)
        pl = &(*pl)->sig;

    nodoAEliminar = *pl;
    memcpy(info, nodoAEliminar->info, MINIMO(cantBytes, nodoAEliminar->tamInfo));

    *pl = NULL;

    free(nodoAEliminar->info);
    free(nodoAEliminar);

    return OK;
}

int sacarPrimero(tLista* pl, void* info, unsigned cantBytes)
{
    tNodo* nodoAEliminar;

    if(!*pl)
        return LISTA_VACIA;

    nodoAEliminar = *pl;
    memcpy(info, nodoAEliminar->info, MINIMO(cantBytes, nodoAEliminar->tamInfo));
    *pl = nodoAEliminar->sig;

    free(nodoAEliminar->info);
    free(nodoAEliminar);

    return OK;
}

int sacarPorPosicion(tLista* pl, int posicion, void* info, unsigned cantBytes)
{
    tNodo* nodoAEliminar;

    if(!*pl)
        return LISTA_VACIA;

    while((*pl)->sig && posicion--)
        pl = &(*pl)->sig;

    nodoAEliminar = *pl;
    memcpy(info, nodoAEliminar->info, MINIMO(cantBytes, nodoAEliminar->tamInfo));

    if(!nodoAEliminar->sig)
        *pl = NULL;

    free(nodoAEliminar->info);
    free(nodoAEliminar);

    return OK;
}

int eliminarApariciones(tLista* pl, const void* elemento,
                        int(*cmp)(const void*, const void*))
{
    tNodo* nodoAEliminar;

    while(*pl)
    {
        if(cmp((*pl)->info, elemento) == 0)
        {
            nodoAEliminar = *pl;
            *pl = nodoAEliminar->sig;
            free(nodoAEliminar->info);
            free(nodoAEliminar);
        }
        else
            pl = &(*pl)->sig;
    }

    return OK;
}
int eliminarAparicionesGrabandoTxt(tLista* pl, FILE** archivo, const void* elemento,
                                   int(*cmp)(const void*, const void*),
                                   void(*grabar)(FILE**, const void*))
{
    tNodo* nodoAEliminar;
    int eliminados = 0;

    while(*pl)
    {
        if(cmp((*pl)->info, elemento) == 0)
        {
            nodoAEliminar = *pl;
            grabar(archivo, nodoAEliminar->info);
            *pl = nodoAEliminar->sig;
            free(nodoAEliminar->info);
            free(nodoAEliminar);
            eliminados++;
        }
        else
            pl = &(*pl)->sig;
    }

    return eliminados;
}
tNodo* buscarPrimeraAparicion(const tLista* pl, const void* elemento,
                              int(*cmp)(const void*, const void*))
{
    while(*pl)
    {
        if(!cmp((*pl)->info, elemento))
            return *pl;
        else
            pl = &(*pl)->sig;
    }

    return NULL;
}

tLista* buscarMenor(tLista* pl, int(* cmp)(const void*, const void*))
{
    tLista* menor;

    menor = pl;
    pl = &(*pl)->sig;

    while(*pl)
    {
        if(cmp((*menor)->info, (*pl)->info) > 0)
            menor = pl;
        pl = &(*pl)->sig;
    }

    return menor;
}

int buscarPorClave(tLista* pl, const void* clave, void* info, int eliminarNodo,
                   int(*cmp)(const void*, const void*))
{
    tNodo* nodoBuscado;

    while(*pl)
    {
        if(cmp((*pl)->info, clave) == 0)
        {
            memcpy(info, (*pl)->info, (*pl)->tamInfo);
            if(eliminarNodo)
            {
                nodoBuscado = *pl;
                *pl = nodoBuscado->sig;
                free(nodoBuscado->info);
                free(nodoBuscado);
            }
            return 1;
        }
        pl = &(*pl)->sig;
    }

    return 0;
}
int buscarPorClaveRecursiva(tLista* pl, const void* clave, void* info,
                            int eliminarNodo, int(*cmp)(const void*, const void*))
{
    tNodo* nodoBuscado;

    if(!*pl)
        return 0;
    buscarPorClaveRecursiva(&(*pl)->sig, clave, info, eliminarNodo, cmp);
    if(cmp((*pl)->info, clave) == 0)
    {
        memcpy(info, (*pl)->info, (*pl)->tamInfo);
        if(eliminarNodo)
        {
            nodoBuscado = *pl;
            *pl = nodoBuscado->sig;
            free(nodoBuscado->info);
            free(nodoBuscado);
        }
        return 1;
    }

    return 0;
}

int contarPorClave(tLista* pl, const void* clave, int eliminarNodo,
                   int(*cmp)(const void*, const void*))
{
    int ocurrencias = 0;
    tNodo* nodoAEliminar;

    while(*pl)
    {
        if(cmp((*pl)->info, clave) == 0)
        {
            ocurrencias++;
            if(eliminarNodo)
            {
                nodoAEliminar = *pl;
                *pl = nodoAEliminar->sig;
                free(nodoAEliminar->info);
                free(nodoAEliminar);
            }
            else
                pl = &(*pl)->sig;
        }
        else
            pl = &(*pl)->sig;
    }

    return ocurrencias;

}
int contarPorClaveRecursiva(tLista* pl, const void* clave, int eliminarNodo,
                            int(*cmp)(const void*, const void*))
{
    int ocurrencias = 0;
    tNodo* nodoAEliminar;

    if(!*pl)
        return 0;
    ocurrencias = contarPorClaveRecursiva(&(*pl)->sig, clave, eliminarNodo, cmp);
    if(cmp((*pl)->info, clave) == 0)
    {
        if(eliminarNodo)
        {
            nodoAEliminar = *pl;
            *pl = nodoAEliminar->sig;
            free(nodoAEliminar->info);
            free(nodoAEliminar);
        }
        return ocurrencias + 1;
    }

    return ocurrencias;
}
int buscarNPorClave(tLista* pl, const void* clave, void* info, int n,
                    int eliminarNodo, int(*cmp)(const void*, const void*))
{
    tNodo* nodoBuscado;
    if(!n)
        return N_ERR;
    while(*pl)
    {
        if(cmp((*pl)->info, clave) == 0 && --n == 0)
        {
            memcpy(info, (*pl)->info, (*pl)->tamInfo);
            if(eliminarNodo)
            {
                nodoBuscado = *pl;
                *pl = nodoBuscado->sig;
                free(nodoBuscado->info);
                free(nodoBuscado);
            }
            return 1;
        }
        pl = &(*pl)->sig;
    }

    return 0;
}
int buscarNPorClaveRecursiva(tLista* pl, const void* clave, void* info, int n,
                            int eliminarNodo, int(*cmp)(const void*, const void*))
{
    tNodo* nodoBuscado;

    if(!*pl)
        return 0;

    if(cmp((*pl)->info, clave) == 0 && --n == 0)
    {
        memcpy(info, (*pl)->info, (*pl)->tamInfo);
        if(eliminarNodo)
        {
            nodoBuscado = *pl;
            *pl = nodoBuscado->sig;
            free(nodoBuscado->info);
            free(nodoBuscado);
        }
        return 1;
    }
    buscarNPorClaveRecursiva(&(*pl)->sig, clave, info, n, eliminarNodo, cmp);

    return 0;
}
void ordenarListaPorSeleccion(tLista* pl, int(* cmp)(const void*, const void*))
{
    tNodo* nodoAux;
    tLista* menor;

    if(!*pl)
        return;

    while((*pl)->sig)
    {
        menor = buscarMenor(pl, cmp);
        if(menor != pl)
        {
            nodoAux = *menor;
            *menor = (*menor)->sig;
            nodoAux->sig = *pl;
            *pl = nodoAux;
        }
        pl = &(*pl)->sig;
    }

}

int cmpEnteros(const void* a, const void* b)
{
    return *((int*)a) - *((int*)b);
}
int cmpClaveMateria(const void* a, const void* b)
{
    return strcmp(((tMateria*)a)->nombre, (char*)b);
}
