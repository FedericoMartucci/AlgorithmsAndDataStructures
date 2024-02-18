#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "../../PilaDinamica/main/pila.h"

void abrirMenu();
void puntoUno();
void puntoDos();void puntoTres();void puntoCuatro();void puntoCinco();void puntoSeis();void puntoSiete();void puntoOcho();void puntoNueve();void puntoDiez();void puntoOnce();void puntoDoce();void puntoTrece();

//Funciones de pila
void cargarPila(tPila* pila);
int vaciarPilaMostrandoEntero(tPila* pila);
void volcarPilaEnteroAOtraPila(tPila* pilaAVaciar, tPila* pilaALlenar);
void volcarPilaEnteroAOtrasPilasAlternando(tPila* pilaAVaciar,
                                           tPila* pilaALlenar1,
                                           tPila* pilaALlenar2);
int vaciarPilasComparandoEntero(tPila* pilaA, tPila* pilaB);
int compararEntero(int numeroA, int numeroB);
#endif // MENU_H_INCLUDED
