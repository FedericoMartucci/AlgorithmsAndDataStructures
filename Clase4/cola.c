#include "cola.h"


void createBatch(const char* fileName){
    int i;
    pedido products[] =
    {
        {"Ventas", "Juan", "XS23", 20},
        {"Gerencia General", "María", "XS23", 30},
        {"Marketing", "María", "XS23", 40},
        {"Marketing", "Carlos", "ABER03", 50},
        {"Marketing", "María", "XS23", 10},
        {"Marketing", "Product F", "ABER03", 15},
        {"Ventas", "María", "Carlos", 12},
        {"Gerencia General", "Carlos", "XS23", 13},
        {"Ventas", "Carlos", "JKL9", 29},
        {"Marketing", "Carlos", "ABER03", 9},
        {"Gerencia General", "Pepe", "JKL9", 6},
    };

    FILE* file = fopen(fileName, "wt");

    for (int i = 0; i < sizeof(products) / sizeof(pedido); i++) {
        fprintf(file, "%s|%s|%s|%d\n", products[i].sector, products[i].solicitante, products[i].codProd, products[i].cant);
    }

    fclose(file);
}
