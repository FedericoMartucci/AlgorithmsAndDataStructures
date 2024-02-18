#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (X < Y ? X : Y)

typedef struct sNodo
{
    void* dato;
    unsigned tamDato;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;
//insertar al inicio
//recorrer lista recursiva generica (mostrando dato)
//insertar al final
//filter (los parametros son la lista, funcion de filtro con dos parametros (el dato del nodo y un dato mandado por parametro) el dato del parametro faltante
//eliminar por posicion
//insertar ordenado
//insertar por posicion
//buscar
#endif // LISTA_H_INCLUDED
