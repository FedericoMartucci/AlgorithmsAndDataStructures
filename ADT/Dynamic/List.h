#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (X < Y ? (X) : (Y))
#define MAX_ID 8
#define MAX_DESCRIPTION 16
#define MAX_PROVIDER 16

#define OK 0
#define MEM_ERR -1
#define FILE_ERR -2

typedef struct sNode{
    void* data;
    unsigned dataSize;
    struct sNode* nextNode;
}tNode;

typedef tNode* tStack;
typedef tNode* tList;

typedef struct{
    int day;
    int month;
    int year;
}tDate;

typedef struct{
    char id[MAX_ID];
    char description[MAX_DESCRIPTION];
    char provider[MAX_PROVIDER];
    tDate purchaseDate;
    tDate expirationDate;
    int quantity;
    float buyingPrice;
    float sellingPrice;
}tProduct;

typedef struct{
    char id[MAX_ID];
    char description[MAX_DESCRIPTION];
    tDate purchaseDate;
    tDate expirationDate;
    int quantity;
    float buyingPrice;
    float sellingPrice;
}tProductWithoutProvider;

/** Dynamic Stack primitives for figuring out some specific cases in List*/
void createStack(tStack* s);
int pushStack(tStack* s, const void* data, unsigned dataSize);
int popStack(tStack* s, void* data, unsigned dataSize);

/** List Primitives*/
int _removeFirstFromList(tList* l, size_t dataSize);

void createList(tList* l);
int isEmptyList(const tList* l);
int isFullList(const tList* l, unsigned dataSize);
void clearList(tList* l);
int addToStartList(tList *l, const void* data, unsigned dataSize);
int removeFirstFromList(tList* l, void* data, unsigned dataSize);
int viewFirstList(const tList* l, void* data, unsigned dataSize);
int addToEndList(tList* l, const void* data, unsigned dataSize);
int removeLastFromList(tList* l, void* data, unsigned dataSize);
int viewTopList(const tList* l, void* data, unsigned dataSize);
void showList(const tList* l, void(*show)(const void*));
void showAndClearList(tList* l, void(*show)(const void*));
void showListReverse(const tList* l, void(*show)(const void*));
void showAndClearListReverse(tList* l, void(*show)(const void*));
void showListReverseFiltered(const tList* l, const void* key,
                             void(*show)(const void*),
                             int(*cmp)(const void*, const void*));
void removeElementByPosition(tList* l, int position);
void removeCoincidencesFromList(tList* l, const void* key,
                                int(*cmp)(const void*, const void*));
void sortList(tList* l, int(*cmp)(const void*, const void*));
void sortListBySelection(tList* l, int(*cmp)(const void*, const void*));
tList* findMinor(tList* l, int(*cmp)(const void*, const void*));
int insertSorted(tList* l, const void* data, size_t dataSize,
                  int(*cmp)(const void*, const void*));
int removeNLastElements(tList* l, unsigned n);
int loadListWithMostExpensiveProducts(tList* listPointer,
                                      int nElements, const char* fileName,
                                      size_t dataSize,
                                      int(*cmp)(const void*, const void*));
/** Show functions */
void showInt (const void* data);
void showString (const void* data);
void showProduct(const void* product);
void showIdExpDateProvider(const void* product);

/** Comparison functions*/
int cmpKey(const void* a, const void* b);
int cmpDateProviderId (const void* a, const void* b);
int cmpId (const void* a, const void* b);
int cmpProvider (const void* a, const void* b);
int cmpDate (const void* a, const void* b);
int cmpPrice(const void* a, const void* b);

/** Test cases and file functions*/
void createBatch(const char* fileName);
int openFile(FILE** file, const char* fileName, const char* openMode);
int traverseBinaryFile(const char* fileName, size_t dataSize,
                        void(*show)(const void*));
//Ask about doing the same function generic instead of two different functions
int traverseAndRecordBinaryFileWithList(const char* fileName, size_t dataSize,
                                        int(*cmp)(const void*, const void*),
                                        int(*action)(tList*, const void*, size_t,
                                        int(*cmp)(const void*, const void*)));
int traverseAndRecordBinaryFileSortingList(const char* fileName, unsigned dataSize,
                                        int(*cmp)(const void*, const void*),
                                        int(*action)(tList*, const void*, unsigned));

#endif // LIST_H_INCLUDED
