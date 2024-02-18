#ifndef RECURSIVIDAD_H_INCLUDED
#define RECURSIVIDAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ES_LETRA(X) ((X >= 'A' && X <= 'Z') || (X >= 'a' && X <= 'z'))

#define ELEMENTO_ENCONTRADO 1
#define ELEMENTO_NO_ENCONTRADO 0

unsigned factorial(unsigned n);
int esPalindromoIterativo(const char* cad);

int esPalindromoRecursivoEnvoltorio(const char* cad);
int esPalindromoRecursivo(const char* ini, const char* fin);

int busquedaBinariaIterativa(const int* coleccion, size_t cantElementos,
                             int elementoABuscar,
                             int(*cmp)(const void*, const void*));

int busquedaBinariaRecursiva(const void* valorABuscar, const void* coleccion,
                             size_t cantElementos, size_t tamElemento,
                             int (*cmp)(const void*, const void*));

int compararEnteros(const void* a, const void* b);

#endif // RECURSIVIDAD_H_INCLUDED
