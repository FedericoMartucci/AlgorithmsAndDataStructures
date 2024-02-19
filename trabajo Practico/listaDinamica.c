#include "listaDinamica.h"

void crearLista(tLista* l)
{
    *l=NULL;
}

int listaVacia(const tLista* l)
{
    return *l==NULL;
}

int listaLlena(const tLista* l,unsigned tam)
{
    void* aux=malloc(sizeof(tNodo) );
    void* dato=malloc(sizeof(tam));
    free(aux);
    free(aux);
    return aux==NULL || dato==NULL;
}

void vaciarLista(tLista* l)
{
    while(*l!=NULL)
    {
        tNodo* nae=*l;
        *l=nae->sig;
        free(nae->dato);
        free(nae);
    }
}

int verPrimeroLista(const tLista* l,void* dato,unsigned tam)
{
    if(*l==NULL)
        return SIN_ELEMENTOS;
    memcpy(dato,(*l)->dato,MINIMO(tam,(*l)->tam) );
    return TODO_OK;
}

int verUltimoLista(const tLista* l,void* dato,unsigned tam)
{
    if(*l==NULL)
        return SIN_ELEMENTOS;

    while((*l)->sig!=NULL)
        l=&((*l)->sig);
    memcpy(dato,(*l)->dato,MINIMO(tam,(*l)->tam) );
    return TODO_OK;
}

int ponerEnPrimero(tLista* l, const void * dato,unsigned tam)
{
// ver si hay espacio para tomar
    tNodo* nue=(tNodo*) malloc(sizeof(tNodo));
    if(nue==NULL)
        return SIN_MEMORIA;
    nue->dato=malloc(tam);
    if(nue->dato==NULL)
    {
        free(nue);
        return SIN_MEMORIA;
    }
//rellenar el dato
    memcpy(nue->dato,dato,tam);
    nue->tam=tam;
//conectarlo al dato
    nue->sig=*l;
    *l=nue;
    return TODO_OK;
}

int ponerEnUltimo(tLista* l, const void * dato,unsigned tam)
{
// ver si hay espacio para tomar
    tNodo* nue=(tNodo*) malloc(sizeof(tNodo));
    if(nue==NULL)
        return SIN_MEMORIA;
    nue->dato=malloc(tam);
    if(nue->dato==NULL)
    {
        free(nue);
        return SIN_MEMORIA;
    }
//posicionarse al ultimo nodo
    while( (*l)!=NULL )
        l=&((*l)->sig);

//rellenar el dato
    memcpy(nue->dato,dato,tam);
    nue->tam=tam;
//conectarlo los nodos
    nue->sig=NULL;
    *l=nue;
    return TODO_OK;
}

int sacarElPrimero(tLista* l, void * dato,unsigned tam)
{
    tNodo* nae=*l;
//ver si hay elementos
    if(*l==NULL)
        return SIN_ELEMENTOS;
//copiar el dato
    memcpy(dato,nae->dato,MINIMO(tam,nae->tam ) );
//retirar del nodo
    *l=nae->sig;
//liberar el nodo
    free(nae->dato);
    free(nae);
    return TODO_OK;
}

int sacarElUltimo(tLista* l, void * dato,unsigned tam)
{
    if(*l==NULL)
        return SIN_ELEMENTOS;

    //ir al ultimo de la cola
    while( (*l)->sig!=NULL )
        l=&(*l)->sig;
    tNodo* nae=*l;

    memcpy(dato,nae->dato,MINIMO(tam,nae->tam));

    free(nae->dato);
    free(nae);

    *l=NULL;

    return TODO_OK;
}

int recorrerLista(tLista*l,Accion accion)
{

    while(*l!=NULL)
    {
        accion( (*l)->dato );
        l=&(*l)->sig;
    }
    return TODO_OK;
}

int recorrerLista2(tLista*l,void * contexto,Accion2 accion)
{
    while(*l!=NULL)
    {
        accion((*l)->dato,contexto);
        l=&(*l)->sig;
    }
    return TODO_OK;
}

void insertarPorPosicion(tLista* l, void * dato,unsigned tam,int pos)
{

}
int insertarOrdenado(tLista* l, const void * dato,unsigned tam,Cmp cmp)
{
    //hay espacio?
    tNodo* nue=(tNodo*)malloc(sizeof(tNodo) );
    if(nue==NULL)
        return SIN_MEMORIA;
    nue->dato=malloc(tam);
    if(nue->dato==NULL)
    {
        free(nue);
        return SIN_MEMORIA;
    }

//copiar imformacion
    memcpy(nue->dato,dato,tam);
    nue->tam=tam;
//es la posicion encontrada; cmp
    while(*l!=NULL && cmp(dato,(*l)->dato)>0 )
        l=&(*l)->sig;
//conectarlo
    nue->sig=*l;
    *l=nue;

    return TODO_OK;
}

void filtrarLista(tLista* l,const void * dato, Cmp cmp)
{
    tNodo* nae;
    while(*l!=NULL)
    {

        if( cmp((*l)->dato,dato)==0)
        {
            nae=*l;
            *l=nae->sig;
            free(nae->dato);
            free(nae);
        }
        else
            l=&(*l)->sig;
    }
}

int eliminarDatoListaOrdenada(tLista* l,void * dato,unsigned tam, Cmp cmp)  //considerando que la lista esta ordenada
{
    if(*l==NULL)
        return SIN_ELEMENTOS;
//buscar el dato a eliminar
    while(*l!=NULL && cmp(dato,(*l)->dato )>0 ) //si la lista no esta ordenada solo basta cmp()!=0
        l=&(*l)->sig;

    if(*l==NULL)
        return -1; //nodo no encontrado

    tNodo * nae=*l;
//conexion del nodo
    *l=nae->sig;

//copio la informacion
    memcpy(dato,nae->dato, MINIMO (tam,nae->tam));

    free(nae->dato);
    free(nae);

    return TODO_OK;
}

tNodo** buscarMenor(tLista* l,Cmp cmp)
{
    if(*l==NULL)
        return NULL;
    tNodo** menor=l;

    while(*l!=NULL)
    {
        if(cmp( (*l)->dato,(*menor)->dato)<0  )     //el dato nuevo, si resulta ser menor al "menor"
            menor=l;                                //entonces el dato sera el nuevo menor
        l=&(*l)->sig;                               //posiciono al siguiente numero;
    }
    return menor;
}

void ordenarLista(tLista*pl,Cmp cmp)
{
    tLista lista=*pl;                       //pl:contendra la lista ordenada
    tNodo** menor;
    while(lista!=NULL)                      //mientras lista no este vacio
    {
        menor=buscarMenor(&lista,cmp);      //obtiene el menor
        *pl=*menor;                         //lo apilo a la lista ordenada
        pl=&(*pl)->sig;                     //posiciono el puntero de la lista ordenada
        *menor=(*menor)->sig;               //desconecto ese nodo menor de la lista principal
    }
}
/**
void agruparDatosRepetidos(tLista* pl,Cmp cmp){
    //mientras lista no este vacias
    tLista* plAux;
    while(*pl!=NULL){
        pl;
        plAux=&(*pl)->sig;
        while(*pl ){


        }
        pl=&(*pl)->sig;
    }

}
*/
int eliminarNUltimos(tLista* pl,int n)
{
    if((*pl)->sig)  //si hay elementos mos
    {
        n=eliminarNUltimos(&(*pl)->sig,n);
        n--;
    }

    if(n>0)
    {
        free( (*pl)->dato );
        free( *pl );
        *pl=NULL;
    }

    return n;
    /**
    if(*pl!= NULL)
        eliminarNUltimos(pl,n); //recursiva y si pasa esto es que no llego a null

    if(n<=0)    //tiene elementos para eliminar?
        return  ;
    */
}



void reducirLista(tLista* pl,fReduce reduce,void * valorReduce)
{
    while(*pl!=NULL)
    {
        reduce( valorReduce,(*pl)->dato );
        pl=&(*pl)->sig;
    }
}

int buscarDatoPorClave(tLista* pl, void* dato,unsigned tam,Cmp cmp)
{

    while( *pl!=NULL && cmp(dato,(*pl)->dato)>0 )
        pl=&(*pl)->sig;

    if( cmp(dato,(*pl)->dato)!=0 )
        return NO_ENCONTRADO;       //NO ENCONTRADO;

    memcpy(dato,(*pl)->dato,MINIMO(tam,(*pl)->tam ) );

    return TODO_OK;
}

int obtenerDatoPorIndex(tLista* pl, void* dato,unsigned tam,unsigned index)
{

    while( *pl!=NULL && index>0)
    {
        index--;
        pl=&(*pl)->sig;
    }
    if(*pl==NULL)
        return NO_ENCONTRADO;

    memcpy(dato,(*pl)->dato,MINIMO(tam,(*pl)->tam ) );

    return TODO_OK;
}

int obtenerDireccionDatoPorIndex(tLista* pl, void* dato, unsigned tam, unsigned index)
{
    while( *pl != NULL && index > 0)
    {
        index--;
        pl=&(*pl)->sig;
    }
    if(*pl==NULL)
        return NO_ENCONTRADO;

    dato=(*pl)->dato;

    return TODO_OK;
}

