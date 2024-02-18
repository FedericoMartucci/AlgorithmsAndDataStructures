#include "../ADT/Static/Stack.h"
#include "../ADT/Static/Batch.h"

int main()
{
    /** Ejercicio 2.6 **////preguntar si esta bien
//    int buffer;
//    tStack s;
//    FILE* file;
//    FILE* fileToWrite;
//
//    createStack(&s);
//    createBatch();
//
//    if(openFile(&fileToWrite, "orderedData", "wt") != OK ||
//       openFile(&file, "data", "rb") != OK){
//        fclose(fileToWrite);
//        return FILE_ERR;
//    }
//
//    orderingElementsWithTwoStacks(file, &s, cmpInt);
//
//    printf("\n");
//
//    while(!isStackEmpty(&s)){
//        popStack(&s, &buffer, sizeof(buffer));
//        fprintf(fileToWrite, "%d ", buffer);
//        printf("%d ", buffer);
//    }
//
//    fclose(fileToWrite);
//    fclose(file);
//    return 0;
    /** Ejercicio 2.7 **/
    int digits = 30;

    tStack s1;
    tStack s2;

    createStack(&s1);
    createStack(&s2);

    if(loadStack(&s1, digits) != OK ||
       loadStack(&s2, 3) != OK){
        clearStack(&s1);
        clearStack(&s2);
        return MEM_ERR;
    }

    sumStacks(&s1, &s2, digits);

    clearStack(&s1);
    clearStack(&s2);

    return 0;
}
