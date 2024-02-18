#include "ejercicios.h"

int main()
{
    int opcion;
    while(opcion != 4)
    {

        printf("MENU\n");
        printf("1- Carga archivo con pilas.\n");
        printf("2- Ordenar archivo con dos pilas.\n");
        printf("3- Suma de numeros muy grandes con pilas.\n");
        printf("4- Salir menu.\n");
        do {
            printf("Ingrese opcion: ");
            scanf("%d", &opcion);
        } while(opcion < 1 || opcion > 4);
        procesarOpcionMenuMain(opcion);
        system("pause");
        system("cls");
    }

    return 0;
}
