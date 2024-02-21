#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "arbol.h"
#include "curlReducido.h"
#include "teclado.h"
#include "jugador.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define ES_LETRA_COMUN(X) ((X >= 'a' && X <= 'z') || (X >= 'A' && X <= 'Z'))

#define VERDADERO 1
#define FALSO 0
#define SI 1
#define NO 0
#define ACTIVADO 1
#define DESACTIVADO 0
#define PUNTAJE_INICIAL -1000000

#define ERROR_API_NO_CONECTADA 5060
#define ERROR_APERTURA_ARCHIVO 5050
#define ERROR_CARGA_CURL 5040
#define ERROR_CONEXION_CURL 5030
#define ERROR_CREACION_ARCHIVO 5020
#define ERROR_PARAMETROS 5010
#define NO_HAY_ERRORES 0
#define MEMORIA_LLENA 1000

#define MAX_LINEA_OPCION 50
#define MAX_PAL 40
#define MAX_LINEA_CONFIG 30
#define TAM_NOMBRE_INFORME 50

typedef struct
{
    char palabra[MAX_PAL];
    int longitud;
    int validez;    //deberia ser boleano
    int puntos;
} tRespuesta;

typedef struct
{
    tJugador*       jugadoresCargados;
    tOrden*         ordenes;
    tArbol          jugadores;   //lista //tJugadores , que tiene arbol
    tRespuesta**    tableroResp;  //matriz que contiene las letras y puntos
    char*           letras;
    unsigned        tiempoRound;
    unsigned        cantRondas;
    unsigned        cantJugadores;
    int             puntajeGanador;
    int             codigoError;
    int             modoPrueba;
    int*           resultados;      // aca sera la suma de puntos que tengan al final
    CURL*           curl;
} tJuego;

void verificarSiPideModoPrueba(tJuego* juego, const char* opcion);
int esOpcionValida(char* opcion);
int esOpcionIniciarJuego(char* opcion);
void AccionesSiEsModoPrueba(tJuego* juego);

void crearJuego(tJuego* juego);
int cargarJuego(tJuego* juego, char* x_secret); //aca se le envia el archivo o recibe el arcivo txt de datos iniciales
int ingresarJugadores(tJuego* juego);
void ingresarNombreJugador(int numJugador, tJugador* jugadorActual);
int hayJugadores(const tJuego* juego);
int sortearOrdenJugadores(tJuego* juego);
void mostrarJugadores(tJuego* juego);
int crearTableroResp(tJuego* juego);
void iniciarJuego(tJuego* juego);
int evaluarPalabras(tJuego* juego);
void determinarPuntos(tJuego* juego);
void imprimirResultados(tJuego* juego); //faltaria enviarle por parametro el FILE*
void generarImpresion(tJuego * juego, FILE* salida);

int calcularPuntos(tRespuesta** tableroResp, tRespuesta* actual,
                   int ordenJugador, int rondaActual, int longMasLarga,
                   int cantJugadores);
int obtenerValorLongitudMasLarga(tJuego* juego,int rondaActual);
int hayOtroLargoPeroDiferente(tRespuesta** tableroResp, tRespuesta* actual,
                              int ordenJugador, int rondaActual,
                              int longMasLarga, int cantJugadores);
int esRepetido(tRespuesta** tableroResp, tRespuesta* actual, int ordenJugador,
               int rondaActual, int cantJugadores);
int esSegundoRepetido(tRespuesta** tableroResp, tRespuesta* actual,
                      int ordenJugador, int rondaActual);
void ingresarLetrasAleatoriamente(char* letras, int cantRondas);
void cerrarJuego(tJuego* juego);


void inicializarAleatoriedad();
char obtenerLetraNoRepetidaRandom(char* abecedario);

void informeErrores(tJuego* juego);

#endif // JUEGO_H_INCLUDED
