#include "colaEstatica.h"

void crearCola(tCola* pc)
{
    pc->pri = 0;
    pc->ult = 0;
    pc->tamDisp = TAM_COLA;
}

int insertarEnCola(tCola* pc, const void* info, unsigned tamInfo)
{
    unsigned ini;
    unsigned fin;

    if(pc->tamDisp < tamInfo + sizeof(unsigned)){
        return MEM_ERR;
    }

    pc->tamDisp -= tamInfo + sizeof(unsigned);

    ini = MINIMO(sizeof(unsigned), TAM_COLA - pc->ult);
    if(ini)
        memcpy(pc->cola + pc->ult, &tamInfo, ini);

    fin = sizeof(unsigned) - ini;
    if(fin)
        memcpy(pc->cola, ((char*)&tamInfo) + ini, fin);

    pc->ult = fin? fin : pc->ult + ini;

    ini = MINIMO(tamInfo, TAM_COLA - pc->ult);
    if(ini)
        memcpy(pc->cola + pc->ult, info, ini);

    fin = tamInfo - ini;
    if(fin)
        memcpy(pc->cola, ((char*)info) + ini, fin);

    pc->ult = fin? fin : pc->ult + ini;
    return OK;
}

int sacarDeCola(tCola* pc, void* info, unsigned cantBytes)
{
    unsigned ini;
    unsigned fin;
    unsigned tamInfo;
    unsigned tamAux;

    if(pc->tamDisp == TAM_COLA)
        return COLA_VACIA;

    ini = MINIMO(sizeof(unsigned), TAM_COLA - pc->pri);
    if(ini)
        memcpy(&tamInfo, pc->cola + pc->pri, ini);

    fin = sizeof(unsigned) - ini;
    if(fin)
        memcpy(((char*)&tamInfo) + ini, pc->cola, fin);

    pc->tamDisp += sizeof(unsigned) + tamInfo;
    pc->pri = fin? fin : pc->pri + ini;
    tamAux = MINIMO(cantBytes, tamInfo);

    ini = MINIMO(tamAux, TAM_COLA - pc->pri);
    if(ini)
        memcpy(info, pc->cola + pc->pri, ini);

    fin = tamAux - ini;
    if(fin)
        memcpy(((char*)info) + ini, pc->cola, fin);

    pc->pri = (pc->pri + tamInfo) % TAM_COLA;

    return OK;
}

int verTopeCola(const tCola* pc, void* info, unsigned cantBytes)
{
    unsigned ini;
    unsigned fin;
    unsigned tamInfo;
    unsigned primero = pc->pri;

    if(pc->tamDisp == TAM_COLA)
        return COLA_VACIA;

    ini = MINIMO(sizeof(unsigned), TAM_COLA - primero);
    if(ini)
        memcpy(&tamInfo, pc->cola + primero, ini);

    fin = sizeof(unsigned) - ini;
    if(fin)
        memcpy(((char*)&tamInfo) + ini, pc->cola, fin);

    primero = fin? fin : primero + ini;
    tamInfo = MINIMO(cantBytes, tamInfo);

    ini = MINIMO(tamInfo, TAM_COLA - primero);
    if(ini)
        memcpy(info, pc->cola + primero, ini);

    fin = tamInfo - ini;
    if(fin)
        memcpy(((char*)info) + ini, pc->cola, fin);

    return OK;
}

int colaLlena(const tCola* pc, unsigned tamInfo)
{
    return pc->tamDisp < tamInfo + sizeof(unsigned);
}

int colaVacia(const tCola* pc)
{
    return pc->tamDisp == TAM_COLA;
}

void vaciarCola(tCola* pc)
{
    pc->ult = pc->pri;
    pc->tamDisp = TAM_COLA;
}
///Funciones de menu
void procesarOpcion(int opcion, tCola* pc)
{
    int numero;

    switch(opcion){
    case 1:
        printf("Ingrese numero a encolar:");
        scanf("%d", &numero);
        printf("%d", numero);
        if(insertarEnCola(pc, &numero, sizeof(int)) == MEM_ERR)
            printf("La cola esta llena.\n");
        break;
    case 2:
        sacarDeCola(pc, &numero, sizeof(int));
        printf("Numero sacado: %d\n", numero);
        break;
    case 3:
        verTopeCola(pc, &numero, sizeof(int));
        printf("Primero en cola: %d\n", numero);
        break;
    case 4:
        while(!colaVacia(pc)){
            sacarDeCola(pc, &numero, sizeof(int));
            printf("%d\n", numero);
        }
        break;
    case 5:
        vaciarCola(pc);
        break;
    case 6:
        if(colaLlena(pc, sizeof(int)))
            printf("Cola llena\n");
        break;
    case 7:
        if(colaVacia(pc))
            printf("Cola vacia\n");
        break;
    default:
        break;

    }
}
