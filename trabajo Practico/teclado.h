#ifndef TECLADO_H_INCLUDED
#define TECLADO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MAX_NAME_LENGTH 100

char obtenerLetraPorTeclado();
void obtenerPalabraDuranteNSegundos(char* palabra, int tiempoLimite);
void obtenerOpcionPorTeclado(char* opcion);


#endif // TECLADO_H_INCLUDED
