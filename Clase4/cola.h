#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(X, Y) (X < Y ? X : Y)
#define MEM_ERR -1
#define OK 1
#define COLA_VACIA -2

#define MAX_SECTOR 30
#define MAX_SOLICITANTE 30
#define MAX_CODPROD 30

/**
struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
};

typedef struct sNodo tNodo;

es lo mismo que lo de abajo
*/
typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;//es una estructura recursiva (hace referencia a cosas que todavia no termine de definir con lo cual necesito que tenga nombre la estructura
//el typedef hace referencia al tNodo, evita que pongamos struct sNodo siempre que declaremos un nodo.

typedef struct {
    char sector[50];
    char solicitante[50];
    char codProd[10];
    int cant;
}pedido;

typedef struct {
    char codProd[10];
    int stock;
    int ptoRep;
}stock;


void createBatch(const char* fileName);

#endif // COLA_H_INCLUDED
