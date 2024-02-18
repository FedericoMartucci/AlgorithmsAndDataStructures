#include "ejercicios.h"

int main()
{
    int opcion;

    while(opcion != 13){
        puts("MENU");
        puts("2- Ordenar archivos datos1 y datos2");
        puts("3- Carga con acumulacion ordenando");
        puts("5- Ejercicio matriz");
        puts("13- Salir.");
        printf("Ingrese opcion: ");
        scanf("%d", &opcion);
        procesarOpcionMenuMain(opcion);
        system("pause");
        system("cls");
    }
}
