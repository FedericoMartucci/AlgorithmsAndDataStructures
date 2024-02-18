#include "Batch.h"

void createBatch()
{
    int vector[TAMANIO_VECTOR];
    int vec[] = {3, 10, 100, 4, 7, 8, 80, 9, 33, 200, 108, 1, 5, 44};//caso de prueba clase
    int i;
    FILE* file;

    // Semilla para la generación de números aleatorios
    srand(time(NULL));

    // Inicialización del vector con números aleatorios
    for (i = 0; i < TAMANIO_VECTOR; i++)
    {
        vector[i] = rand() % 100; // Genera números aleatorios entre 0 y 99
    }

    if(openFile(&file, "data", "wb") != OK) return;

    fwrite(vec, sizeof(vec), 1, file);

    fclose(file);
}

int openFile(FILE** filePointer, const char* fileName, const char* mode)
{
    *filePointer = fopen(fileName, mode);

    if(!*filePointer)
    {
        perror("Oops! Something wrong occurred.");
        return FILE_ERR;
    }
    return OK;
}

int orderingElementsWithTwoStacks(FILE* file, tStack* s, int (*cmp)(const void* a, const void* b))
{
    int buffer;
    int aux;
    tStack s2;

    createStack(&s2);

    fread(&buffer, sizeof(int), 1, file);


    while(!feof(file))
    {
        printf("%d ", buffer);
        if(!seeStackTop(s, &aux, sizeof(int)))
            pushStack(s, &buffer, sizeof(int));
        else if(cmp(&buffer, &aux) < 0){
            do{
                popStack(s, &aux, sizeof(int));
                pushStack(&s2, &aux, sizeof(int));
            }while(seeStackTop(s, &aux, sizeof(int)) && cmp(&buffer, &aux) < 0 );
            pushStack(s, &buffer, sizeof(int));
        }
        else if(!seeStackTop(&s2, &aux, sizeof(int)))
            pushStack(&s2, &buffer, sizeof(int));
        else if(cmp(&buffer, &aux) < 0)
            pushStack(&s2, &buffer, sizeof(int));
        else{
            do{
                popStack(&s2, &aux, sizeof(int));
                pushStack(s, &aux, sizeof(int));
            }while(seeStackTop(&s2, &aux, sizeof(int)) && cmp(&buffer, &aux) > 0);
            pushStack(&s2, &buffer, sizeof(int));
        }
        fread(&buffer, sizeof(int), 1, file);
    }

    while(!isStackEmpty(&s2))
    {
        popStack(&s2, &buffer, sizeof(buffer));
        pushStack(s, &buffer, sizeof(buffer));
    }

    clearStack(&s2);

    return OK;
}

int cmpInt(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int loadStack(tStack* s, int quantityOfDigits){
    int digit;
    int i;

    srand(time(NULL));

    for (i = 0; i < quantityOfDigits; i++){
        digit = rand() % 10;
        printf("%d ", digit);
        if(isStackFull(s, sizeof(digit)))
            return MEM_ERR;
        pushStack(s, &digit, sizeof(digit));
    }

    printf("\n");

    return OK;
}

int sumStacks(tStack* s1, tStack* s2, int quantityOfDigits){
    int n1;
    int n2;
    int sum;
    int carry = 0;
    int nextCarry;
    tStack s3;
    FILE* file;

    createStack(&s3);

    if(openFile(&file, "results", "wt") != OK)
        return FILE_ERR;

    while(!isStackEmpty(s1) && !isStackEmpty(s2)){
        popStack(s1, &n1, sizeof(n1));
        popStack(s2, &n2, sizeof(n2));
        if((nextCarry = (n1 + n2 + carry) / 10)){
            sum =  n1 + n2 + carry - 10 * nextCarry;
            if(isStackFull(&s3, sizeof(sum))){
               clearStack(&s3);
               return MEM_ERR;
            }
            else
                pushStack(&s3, &sum, sizeof(sum));
        } else {
            sum =  n1 + n2 + carry;
            if(isStackFull(&s3, sizeof(sum))){
               clearStack(&s3);
               return MEM_ERR;
            }
            else
                pushStack(&s3, &sum, sizeof(sum));
        }
        carry = nextCarry;
    }

    completeWithRemainingStack(s1, &s3, &nextCarry);
    completeWithRemainingStack(s2, &s3, &nextCarry);

    if(nextCarry != 0){
        if(isStackFull(&s3, sizeof(sum))){
            clearStack(&s3);
            return MEM_ERR;
        }
        else
            pushStack(&s3, &nextCarry, sizeof(nextCarry));
    }

    printResults(&s3);

    clearStack(&s3);
    fclose(file);

    return OK;
}

void completeWithRemainingStack(tStack* s1, tStack* resultStack, int* remainingCarry){//no se suma el carry en casos borde 99923 + 98
    int digit;

    while(!isStackEmpty(s1)){
        popStack(s1, &digit, sizeof(digit));
        if(*remainingCarry != 0){
            digit += *remainingCarry;
            *remainingCarry = 0;
        }
        pushStack(resultStack, &digit, sizeof(digit));
    }
}

void printResults(tStack* results){
    int digit;

    while(!isStackEmpty(results)){
        popStack(results, &digit, sizeof(digit));
        fprintf(stdout, "%d ", digit);
    }
}
