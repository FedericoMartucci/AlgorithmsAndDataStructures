#include "listaDoble.h"

int main()
{
    int vec[] = {2, 8, 7, 9, 3, 5, 23, 12};
    int i;
    tLista lista;

    crearLista(&lista);

    for(i = 0; i < sizeof(vec)/sizeof(int); i ++)
        insertarAlInicio(&lista, &vec[i], sizeof(int));

    mostrarDerAIzq(&lista, mostrarEntero);
    puts("");
    ordenarLista(&lista, cmpEnteros);
    mostrarDerAIzq(&lista, mostrarEntero);


    vaciarLista(&lista);
    return 0;
}
