#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#define MAX_ID 8
#define MAX_PROVIDER 16
#define MAX_DESCRIPTION 16

//Error Codes
#define OK 1
#define FILE_ERR -1
#define MEM_ERR -2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNode
{
    void* data;
    unsigned dataSize;
    struct sNode* nextNode;
}tNode;
typedef tNode* tList;

typedef struct
{
    char id[MAX_ID];
    int counter;
}tIndex;

typedef struct
{
    int day;
    int month;
    int year;
}tDate;

typedef struct
{
    char id[MAX_ID];
    char provider[MAX_PROVIDER];
    char description[MAX_DESCRIPTION];
    tDate purchaseDate;
    tDate expirationDate;
    int quantity;
    float buyingPrice;
    float sellingPrice;
}tProduct;

typedef struct
{
    char id[MAX_ID];
    char description[MAX_DESCRIPTION];
    tDate purchaseDate;
    tDate expirationDate;
    int quantity;
    float buyingPrice;
    float sellingPrice;
}tProductWithoutProvider;

void createList(tList* l);
void clearList(tList* l);
int insertToEnd(tList* l, const void* data, unsigned dataSize);
int insertToEndWithoutProvider(tList* l, const void* data, unsigned dataSize);

/**File functions*/
int createBatch(const char* fileName);
int openFile(FILE** file, const char* fileName, const char* openMode);
int traverseFileWithList(const char* fileName, unsigned dataSize, int(*action)(tList*, const void*, unsigned));

/**Show functions*/
void showProduct(const void* product);
void showProductWithoutProvider(const void* product);



#endif // FILE_H_INCLUDED
