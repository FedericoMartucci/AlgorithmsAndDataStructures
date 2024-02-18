#include "ejercicios.h"

int main()
{
    tCola c;

    crearCola(&c);

    crearLoteProductosOrdenado();
    puts("Registros leidos:");
    cargarArchivoEnColaFiltrando(&c, "datos.bin", sizeof(tProducto),
                                 filtrarCantidadMayorA20);

    puts("\n\nRegistros filtrados:");
    cargarColaEnArchivo(&c, "datos2.bin", sizeof(tProducto));

    vaciarCola(&c);
    return 0;
}
