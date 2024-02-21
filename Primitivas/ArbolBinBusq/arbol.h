#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLA_DUP 0
#define SIN_MEM 0
#define SIN_INICIALIZAR 0
#define ERROR_ARCH 0
#define TODO_BIEN 1

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* izq;
    struct sNodo* der;
}tNodoArbol;

typedef tNodoArbol* tArbol;

void crearArbol(tArbol* a);
int insertarArbolIterativo(tArbol* a, const void* dato, unsigned cantBytes,
                  int(*cmp)(const void*, const void*));
int insertarArbolRecursivo(tArbol* a, const void* dato, unsigned cantBytes,
                  int(*cmp)(const void*, const void*));
int arbolVacio(const tArbol* a);
int alturaArbol(tArbol* a);
int contarNodos(tArbol* a);

void mostrarNodosHoja(const tArbol* a);
void mostrarNodosNoHoja(const tArbol* a);
void mostrarNodosSoloHijosIzq(const tArbol* a);
void mostrarNodosHijosIzq(const tArbol* a);

void recorrerArbolEnOrden(tArbol* a, void(*accion)(const void*));
void recorrerArbolPreOrden(tArbol* a, void(*accion)(const void*));
void recorrerArbolPostOrden(tArbol* a, void(*accion)(const void*));
void mostrarEntero(const void* num);
void vaciarArbol(tArbol* a);

int esCompletoANivel(const tArbol* a, int n);
int esCompleto(const tArbol* a);
int esBalanceado(const tArbol* a);
int eliminarRaiz(tArbol* a);
tNodo** menorNodo(const tArbol* a, int(*cmp)(const void*, const void*));
tNodo** mayorNodo(const tArbol* a, int(*cmp)(const void*, const void*));
int eliminarNodoPorClave(tArbol *a, void* clave,
                         int(*cmp)(const void* a, const void* b));
tNodo* buscarPorClave(tArbol *a, void* clave,
                      int(*cmp)(const void* a,const void* b));

int compararEnteros(const void* a, const void* b);

#endif // ARBOL_H_INCLUDED
