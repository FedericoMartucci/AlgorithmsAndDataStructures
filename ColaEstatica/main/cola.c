#include "cola.h"

void crearCola(tCola *c)
{
    c->pri = 0;
    c->ult = 0;
    c->tamDis = TAM_COLA;
}

int colaLlena(const tCola *c,size_t tam)
{
    return c->tamDis<tam+sizeof(unsigned);
}

int colaVacia(const tCola *c)
{
    return c->tamDis == TAM_COLA;
}

void vaciarCola(tCola* c)
{
    c->ult = c->pri;
    c->tamDis = TAM_COLA;
}

int ponerEnCola(tCola* c, const void *d, unsigned tam)
{
    unsigned ini, fin;
    if(c->tamDis<sizeof(unsigned)+tam)
    {
        return 0;
    }
    //procesamos tam
    c->tamDis -=sizeof(unsigned)+tam;
    //ini = minimo(sizeof(unsigend), TAM_COLA - c->ult)); siendo c->ult el indice que selecciona donde termina el ultimo elemento
    if((ini = minimo(sizeof(unsigned), TAM_COLA - c->ult)) != 0)
        memcpy(c->cola +c->ult,&tam,ini); //TAM_COLA -c->ult es igual a cero solo cuando c->ult = TAM_COLA, eso quiere decir que esta parado en el final
    //fin = sizeof(tam)-ini;
    if((fin = sizeof(tam)-ini)!=0)
        memcpy(c->cola, ((char*)&tam)+ini,fin);
    c->ult = fin? fin: c->ult +ini;
    //procesamos la informacion
    //ini = minimo(tam,TAM_COLA - c->ult);
    if((ini = minimo(tam,TAM_COLA-c->ult))!=0)
        memcpy(c->cola + c->ult,d,ini);
    //fin = tam-ini;
    if((fin = tam-ini)!=0)
        memcpy(c->cola, ((char*)d)+ini,fin);
    c->ult = fin? fin: c->ult+ini; //esta pregunta siempre es necesaria cuando termino de procesar algo
    return 1;
}

int sacarDeCola(tCola*cola, void* d, unsigned tam)
{
//    unsigned ini;
//    unsigned fin;
//    unsigned tamInfo;
//    unsigned tamAux;
    unsigned ini,
             fin,
             tamInfo,
             tamAux;

    if(cola->tamDis == TAM_COLA)
        return COLA_VACIA;

    ini = minimo(sizeof(unsigned), TAM_COLA - cola->pri);
    fin = sizeof(unsigned) - ini;
    if(ini)
        memcpy(&tamAux, cola->cola + cola->pri, ini);
    if(fin)
        memcpy(((char*)&tamAux) + ini, cola->cola, fin);

    cola->pri = fin? fin : cola->pri + ini;
    cola->tamDis += tamAux + sizeof(unsigned);
    tamInfo = minimo(tamAux, tam);

    ini = minimo(tamInfo, TAM_COLA - cola->pri);
    fin = tamInfo - ini;

    if(ini)
        memcpy(d, cola->cola + cola->pri, ini);
    if(fin)
        memcpy(((char*)d) + ini, cola->cola, fin);

    cola->pri = (cola->pri + tamAux) % TAM_COLA;
    return 1;
}

int verPrimero(const tCola*c, void *d,size_t tam)
{
    unsigned tamPrimero,ini,fin,primero = c->pri;

    if(c->tamDis == TAM_COLA) // la cola esta vacia
    {
        return 0;
    }

    //proceso la tamaño
    ini = minimo(sizeof(unsigned),TAM_COLA - c->pri);

    if(ini)
    {
        memcpy(&tamPrimero, c->cola+c->pri,ini);
    }
    fin = sizeof(tamPrimero)-ini;

    if(fin)
    {
        memcpy(((char*)&tamPrimero)+ini,c->cola,fin);
    }
    primero = fin? fin: primero + ini;
    tamPrimero = minimo(tam,tamPrimero);
    //proceso la info

    ini = minimo(tamPrimero,TAM_COLA - primero);
    if(ini)
    {
        memcpy(d,c->cola+primero,ini);
    }
    fin = tamPrimero -ini;

    if(fin)
    {
        memcpy(((char*)d)+ini,c->cola,fin);
    }
    //NO HACE FALTA PREGUNTAR primero = fin? fin: primero+ini por que ya leimos lo que queriamos
    return 1;
}
