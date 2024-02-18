#ifndef BATCH_H_INCLUDED
#define BATCH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Stack.h"

#define TAMANIO_VECTOR 20

#define PRODUCT_ID 8
#define DESCRIPTION 16
#define PROVIDER 16
#define YEAR 4
#define MONTH 2
#define DAY 2

#define TAMANIO_VECTOR 20

#define MEM_ERR -2
#define FILE_ERR -1
#define OK 0

typedef struct
{
    char year[YEAR];
    char month[MONTH];
    char day[DAY];
}tDate;

typedef struct
{
    char productID[PRODUCT_ID];
    char description[DESCRIPTION];
    char provider[PROVIDER];
    tDate purchaseDate;
    tDate expirationDate;
    int quantity;
    float purchasePrice;
    float sellingPrice;
}tProduct;

void createBatch();
int openFile(FILE** filePointer, const char* fileName, const char* mode);
int orderingElementsWithTwoStacks(FILE* file, tStack* s,
                                  int (*cmp)(const void* a, const void* b));
int cmpInt(const void* a, const void* b);

int loadStack(tStack* s, int quantityOfDigits);
int sumStacks(tStack* s1, tStack* s2, int quantityOfDigits);
void completeWithRemainingStack(tStack* s1, tStack* resultStack, int* remainingCarry);
void printResults(tStack* results);
#endif // BATCH_H_INCLUDED
