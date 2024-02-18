#include "recursividad.h"

void testPalindromo(const char* cad, int esperado,
                             int(*esPalindromo)(const char*))
{
    int obtenido;

    obtenido = esPalindromo(cad);

    if(obtenido == esperado)
        fprintf(stdout, "OK: cadena: %s - Esperado: %d - Obtenido: %d\n",
                cad, esperado, obtenido);
    else
        fprintf(stdout, "ERROR: cadena: %s - Esperado: %d - Obtenido: %d\n",
                cad, esperado, obtenido);
}

void testBusquedaBinaria(const void* valorABuscar, const void* coleccion,
                         size_t cantElementos, size_t tamElemento, int esperado,
                         int(*cmp)(const void*, const void*),
                         int(*busquedaBinaria)(const void*, const void*, size_t,
                                               size_t, int (*cmp)(const void*, const void*)))
{
    int obtenido;

    obtenido = busquedaBinaria(valorABuscar, coleccion, cantElementos, tamElemento, cmp);

    if(obtenido == esperado)
        fprintf(stdout, "OK: Esperado: %d - Obtenido: %d\n", esperado, obtenido);
    else
        fprintf(stdout, "ERROR: Esperado: %d - Obtenido: %d\n", esperado, obtenido);
}



int main()
{
//    puts("Casos de prueba\n");
//    printf("Factorial de 0: %d\n", factorial(0));
//    printf("Factorial de 1: %d\n", factorial(1));
//    printf("Factorial de 2: %d\n", factorial(2));
//    printf("Factorial de 3: %d\n", factorial(3));
//    printf("Factorial de 4: %d\n", factorial(4));
//    printf("Factorial de 5: %d\n", factorial(5));
//    printf("Factorial de 6: %d\n", factorial(6));
//    printf("Factorial de 7: %d\n", factorial(7));
//    printf("Factorial de -1: %d\n", factorial(-1));
//    printf("Factorial de -0: %d\n", factorial(-0));
//    testPalindromo("banana", 0, esPalindromoRecursivoEnvoltorio);
//    testPalindromo("anita lava la tina", 1, esPalindromoRecursivoEnvoltorio);
//    testPalindromo("arriba   la birra   ", 1, esPalindromoRecursivoEnvoltorio);

    int vecPar[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int vecImpar[] = {1, 2, 3, 4, 5, 6, 7};
    int valorABuscar1 = 0;
    int valorABuscar2 = 1;
    int valorABuscar3 = 4;
    int valorABuscar4 = 5;
    int valorABuscar5 = 8;
    int valorABuscar6 = 7;

    puts("Busqueda en coleccion par");
    testBusquedaBinaria(&valorABuscar1, vecPar, sizeof(vecPar)/sizeof(int), sizeof(int),
                        ELEMENTO_NO_ENCONTRADO, compararEnteros, busquedaBinariaRecursiva);
    testBusquedaBinaria(&valorABuscar2, vecPar, sizeof(vecPar)/sizeof(int), sizeof(int),
                        ELEMENTO_ENCONTRADO, compararEnteros, busquedaBinariaRecursiva);
    testBusquedaBinaria(&valorABuscar3, vecPar, sizeof(vecPar)/sizeof(int), sizeof(int),
                        ELEMENTO_ENCONTRADO, compararEnteros, busquedaBinariaRecursiva);
    testBusquedaBinaria(&valorABuscar4, vecPar, sizeof(vecPar)/sizeof(int), sizeof(int),
                        ELEMENTO_ENCONTRADO, compararEnteros, busquedaBinariaRecursiva);
    testBusquedaBinaria(&valorABuscar5, vecPar, sizeof(vecPar)/sizeof(int), sizeof(int),
                        ELEMENTO_ENCONTRADO, compararEnteros, busquedaBinariaRecursiva);
    puts("\n\nBusqueda en coleccion impar");
    testBusquedaBinaria(&valorABuscar1, vecImpar, sizeof(vecImpar)/sizeof(int), sizeof(int),
                        ELEMENTO_NO_ENCONTRADO, compararEnteros, busquedaBinariaRecursiva);
    testBusquedaBinaria(&valorABuscar2, vecImpar, sizeof(vecImpar)/sizeof(int), sizeof(int),
                        ELEMENTO_ENCONTRADO, compararEnteros, busquedaBinariaRecursiva);
    testBusquedaBinaria(&valorABuscar3, vecImpar, sizeof(vecImpar)/sizeof(int), sizeof(int),
                        ELEMENTO_ENCONTRADO, compararEnteros, busquedaBinariaRecursiva);
    testBusquedaBinaria(&valorABuscar4, vecImpar, sizeof(vecImpar)/sizeof(int), sizeof(int),
                        ELEMENTO_ENCONTRADO, compararEnteros, busquedaBinariaRecursiva);
    testBusquedaBinaria(&valorABuscar5, vecImpar, sizeof(vecImpar)/sizeof(int), sizeof(int),
                        ELEMENTO_NO_ENCONTRADO, compararEnteros, busquedaBinariaRecursiva);
    testBusquedaBinaria(&valorABuscar6, vecImpar, sizeof(vecImpar)/sizeof(int), sizeof(int),
                        ELEMENTO_ENCONTRADO, compararEnteros, busquedaBinariaRecursiva);

    return 0;
}
