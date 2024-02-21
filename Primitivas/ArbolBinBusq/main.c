#include "arbol.h"
void imprimirConForma(void * info, unsigned tam, unsigned n, void * params)
{
    int * i = (int *) info;
    printf("%*s-%3d-\n",n*3,"", *i);
}

int main()
{
    int vec[] = {5, 2, 8, 1, 3, 7, 9, 4, 6, 10};
    int vec2[] = {3, 1, 5, 2, 4, 6, 7, 9, 8, 10};
    int i;
    tArbol a;

    crearArbol(&a);

    for(i = 0; i < sizeof(vec)/sizeof(int); i ++)
        insertarArbolIterativo(&a, vec + i, sizeof(int), compararEnteros);

    recorrerArbolPreOrden(&a, mostrarEntero);
    puts("\n");
    recorrerEnOrdenInversoArbolBinBusq(&a, NULL, imprimirConForma);
    //recorrerArbolEnOrden(&a, mostrarEntero);
    puts("\n");
    puts("Nodos hoja:");
    mostrarNodosHoja(&a);
    puts("\n\nNodos NO hoja:");
    mostrarNodosNoHoja(&a);
    puts("\n\nNodos SOLO hijos izquierdos:");
    mostrarNodosSoloHijosIzq(&a);
    puts("\n\nNodos hijos izquierdos:");
    mostrarNodosHijosIzq(&a);
    printf("\n\nAltura arbol: %d", alturaArbol(&a));
    printf("\n\nCantidad nodos arbol: %d", contarNodos(&a));
    //recorrerArbolPostOrden(&a, mostrarEntero);

    vaciarArbol(&a);
    return 0;
}
