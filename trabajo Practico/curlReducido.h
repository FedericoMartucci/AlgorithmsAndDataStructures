#ifndef CURLREDUCIDO_H_INCLUDED
#define CURLREDUCIDO_H_INCLUDED

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

#define NO_PUDO_CARGAR -1
#define TODO_OK 1
#define ERROR_SOLICITUD 2
#define PALABRA_ENCONTRADA 200
#define PALABRA_NO_ENCONTRADA 204

int cargarCurl(CURL** curl, char* x_secret);
int enviarPalabra(CURL** curl, char* palabra);
int obtenerRespuestaPalabra(CURL** curl);
void liberarCurl(CURL** curl);

#endif // CURLREDUCIDO_H_INCLUDED
