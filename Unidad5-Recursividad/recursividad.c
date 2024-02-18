#include "recursividad.h"

unsigned factorial(unsigned n)
{
    if(n < 2)
        return 1;
    return n * factorial(n - 1);
}
//funcion recibe cadena de caracteres e indicar si la cadena es palindromo o no
//una recursiva (palabra sola)
//una iterativa (palabra sola)
//tolera espacios intermedios (mejora)
int esPalindromoIterativo(const char* cad)
{
    const char* ini = cad;
    const char* fin = cad + strlen(cad) - 1;

    while(ini < fin)
    {
        while(!ES_LETRA(*ini))
            ini++;
        while(!ES_LETRA(*fin))
            fin--;
        if(*ini != *fin)
        {
            return 0;
        }
        ini++;
        fin--;
    }

    return 1;
}
int esPalindromoRecursivoEnvoltorio(const char* cad)
{
    const char* ini = cad;
    const char* fin = cad + strlen(cad) - 1;

    return esPalindromoRecursivo(ini, fin);
}

int esPalindromoRecursivo(const char* ini, const char* fin)
{
    if(ini >= fin)
        return 1;
    if(!ES_LETRA(*ini))
        return esPalindromoRecursivo(ini + 1, fin);
    if(!ES_LETRA(*fin))
        return esPalindromoRecursivo(ini, fin - 1);
    if(*ini == *fin)
        return esPalindromoRecursivo(ini + 1, fin - 1);
    else
        return 0;
    return 1;
}

int busquedaBinariaIterativa(const int* coleccion, size_t cantElementos,
                             int elementoABuscar,
                             int(*cmp)(const void*, const void*))
{
    int i;
    int posicion;
    int resultadoComparacion;

    posicion = cantElementos / 2 - 1;

    for(i = 0; i < cantElementos / 2; i++)
    {
        if(!(resultadoComparacion = cmp(coleccion + posicion, &elementoABuscar)))
            return ELEMENTO_ENCONTRADO;
        if(resultadoComparacion > 0)
            posicion -= posicion / 2 - 1;
        else
            posicion += posicion / 2 - 1;
    }

    return ELEMENTO_NO_ENCONTRADO;
}


int busquedaBinariaRecursiva(const void* valorABuscar, const void* coleccion,
                             size_t cantElementos, size_t tamElemento,
                             int (*cmp)(const void*, const void*))
{
    void* coleccionDesplazada = (void*)coleccion + (cantElementos / 2) * tamElemento;
    if(!cmp(valorABuscar, coleccionDesplazada))
        return ELEMENTO_ENCONTRADO;
    if(coleccion == coleccionDesplazada)
        return ELEMENTO_NO_ENCONTRADO;
    if(cmp(valorABuscar, coleccionDesplazada) < 0)
        return busquedaBinariaRecursiva(valorABuscar, coleccion, cantElementos / 2, tamElemento, cmp);
    if(cmp(valorABuscar, coleccionDesplazada) > 0)
        return busquedaBinariaRecursiva(valorABuscar, coleccionDesplazada + tamElemento,
                       cantElementos / 2 - !(cantElementos % 2), tamElemento, cmp);
}


int compararEnteros(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}
