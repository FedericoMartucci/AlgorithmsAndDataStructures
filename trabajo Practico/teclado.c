#include "teclado.h"

char obtenerLetraPorTeclado()
{
    char opcion;
    scanf("%c",&opcion);
    fflush(stdin);
    return opcion;      //deolver siempre en mayuscula la opcion
}

void obtenerOpcionPorTeclado(char* opcion){
    scanf("%s",opcion);
    fflush(stdin);
}

void obtenerPalabraduranteNSegundos(char* palabra,int tiempoLimite)
{
    *palabra='\0';

    time_t startTime = time(NULL);
    int cursorPosition = 0;  // Posición del cursor en el buffer

    while (difftime(time(NULL), startTime) < tiempoLimite)
    {
        usleep(1000);  // duerme la entrada cada 1 milisegundos //importante asi para no cargar al procesador en un bucle hiper rapido
        if (_kbhit())
        {
            // Si el usuario presiona una tecla, la almacenamos en el palabra
            char key = _getch();
            if (key == 13)    // Enter key
            {
                break;        // Salir si se presiona Enter
            }
            else if (key == 8)      // Retroceso (Backspace)
            {
                if (cursorPosition > 0)
                {
                    // Solo retroceder si no estamos al principio del buffer
                    cursorPosition--;
                    printf("\b \b");  // Retrocede y borra un carácter en la pantalla
                    palabra[cursorPosition] = '\0';  // Borra el carácter retrocedido en el buffer
                }
            }
            else
            {
                // Almacena el carácter en el buffer y muestra en pantalla
                palabra[cursorPosition] = key;
                palabra[cursorPosition+1] = '\0';
                printf("%c", key);
                cursorPosition = (cursorPosition + 1) % (MAX_NAME_LENGTH - 1);      //si supera a max, significa que vuelve a la misma
            }
        }
    }
    fflush(stdin);  // por la dudas, habria que fijarse si deberia estar

}
