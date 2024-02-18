#include "pila.h"

int pilaVacia(const tPila* pp){
    return *pp == NULL;
}
int pilaLlena(const tPila* pp, unsigned tamDato){
    tNodo* nodo = (tNodo*)malloc(sizeof(tNodo));
    void* dato = malloc(tamDato);

    free(nodo);
    free(dato);

    return nodo == NULL || dato == NULL;
}
void crearPila(tPila* pp){
    *pp = NULL;
}
int ponerEnPila(tPila* pp, const void* dato, unsigned tamDato);
int sacarDePila(tPila* pp, void* dato, unsigned tamDato);
int verTopePila(const tPila* pp, void* dato, unsigned tamDato);
void vaciarPila(tPila* pp){
    while(*pp){
        tNodo* aux = *pp;
        *pp = aux->sig;
        free(aux->info);
        free(aux);
    }
}
