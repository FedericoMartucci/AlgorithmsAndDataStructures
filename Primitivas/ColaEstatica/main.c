#include "colaEstatica.h"

int main()
{
    int opcion = 1;
    tCola cola;
    crearCola(&cola);

    while(opcion)
    {
        printf("MENU\n");
        printf("1- Poner en cola.\n");
        printf("2- Sacar de cola.\n");
        printf("3- Ver primero de cola.\n");
        printf("4- Vaciar y mostrar cola.\n");
        printf("5- Vaciar cola.\n");
        printf("6- Cola llena.\n");
        printf("7- Cola vacia.\n");
        do {
            printf("Ingrese opcion (0 para salir):");
            scanf("%d", &opcion);
        } while(opcion < 0 || opcion > 7);
        procesarOpcion(opcion, &cola);
    }

    vaciarCola(&cola);
    return 0;
}
