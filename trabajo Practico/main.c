#include "juego.h"

int main()
{
    char opcion[MAX_LINEA_OPCION];
    tJuego juego;
    crearJuego(&juego);

    if(cargarJuego(&juego, "X-Secret: a0a16e77b741c7ef61af030eeb24a4027dfb64dd50b7f7c34bbb499b20b15eef") != TODO_OK)   //escribir aca su codigo secreto de la pagina pons
    {
        fprintf(stderr, "No se pudo cargar el juego");
        informeErrores(&juego);
        cerrarJuego(&juego);
        return 0;
    }

    do
    {
        puts("Ingrese una de las opciones.");
        puts("[A]: Ingresar jugadores.");
        puts("[B]: Salir del juego.");
        obtenerOpcionPorTeclado(opcion);
        verificarSiPideModoPrueba(&juego, opcion);
        system("cls");
    }
    while(esOpcionValida(opcion));

    AccionesSiEsModoPrueba(&juego);

    if(esOpcionIniciarJuego(opcion))
    {
        if(ingresarJugadores(&juego) == TODO_OK && hayJugadores(&juego))
        {
            if(crearTableroResp(&juego) == TODO_OK &&
               sortearOrdenJugadores(&juego) == TODO_OK)
            {
                mostrarJugadores(&juego);
                iniciarJuego(&juego);
                evaluarPalabras(&juego);
                determinarPuntos(&juego);
                imprimirResultados(&juego);
            }
        }
        else
            puts("No se han ingresado jugadores...");
    }

    puts("Fin del juego, ingrese una tecla para continuar...");
    getch();

    informeErrores(&juego);

    cerrarJuego(&juego);

    return 0;
}
