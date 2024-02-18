#include "List.h"
/**
typedef struct sNode{
    void* data;
    unsigned dataSize;
    struct sNode* nextNode;
}tNode;
*/

void createList(tList* l){
    *l = NULL;
}

int addToStartList(tList *l, const void* data, unsigned dataSize){
    tNode* node;
    if((node = (tNode*)malloc(sizeof(tNode))) == NULL ||
       (node->data = malloc(dataSize)) == NULL){
        free(node);
        return 0;
    }

    memcpy(node->data, data, dataSize);
    node->dataSize = dataSize;
    node->nextNode = *l;
    *l = node;

    return 1;
}
int removeFirstFromList(tList* l, void* data, unsigned dataSize){
    tNode* node;

    if(!(*l))
        return 0;

    node = *l;
    *l = node->nextNode;
    memcpy(data, node->data, MIN(node->dataSize, dataSize));

    free(node->data);
    free(node);

    return 1;

}
int addToEndList(tList* l, const void* data, unsigned dataSize){
    tNode* node;

    if((node = (tNode*)malloc(sizeof(tNode))) == NULL ||
       (node->data = malloc(dataSize)) == NULL){
        free(node);
        return 0;
    }

    while(*l)
        l = &((*l)->nextNode);

    memcpy(node->data, data, dataSize);
    node->dataSize = dataSize;
    node->nextNode = NULL;
    *l = node;

    return 1;
}

int removeLastFromList(tList* l, void* data, unsigned dataSize){
    if(!*l)
        return 0;

    while((*l)->nextNode)
        l = &((*l)->nextNode);

    memcpy(data, (*l)->data, MIN(dataSize, (*l)->dataSize));


    free((*l)->data);
    free(*l);

    *l = NULL;

    return 1;
}

int isEmptyList(const tList* l){
    return *l == NULL;
}

void clearList(tList* l){
    tNode* node;
    while(*l){
        node = *l;
        *l = node->nextNode;
        free(node->data);
        free(node);
    }
}
int isFullList(const tList* l, unsigned dataSize){
    tNode* node = (tNode*)malloc(sizeof(tNode));
    void* data = malloc(dataSize);

    free(node);
    free(data);

    return node == NULL || data == NULL;
}
int viewTopList(const tList* l, void* data, unsigned dataSize){
    if(!*l)
        return 0;

    while((*l)->nextNode)
        l = &(*l)->nextNode;

    memcpy(data, (*l)->data, MIN((*l)->dataSize, dataSize));

    return 1;
}
int viewFirstList(const tList* l, void* data, unsigned dataSize){
    if(!*l)
        return 0;

    memcpy(data, (*l)->data, MIN((*l)->dataSize, dataSize));

    return 1;
}
void showList(const tList* l, void(*show)(const void*)){
    while(*l){
        show((*l)->data);
        l = &(*l)->nextNode;
    }
}
void showAndClearList(tList* l, void(*show)(const void*)){// se puede modularizar usando otra primitiva en una misma primitiva?
    tNode* node;

    while(*l){
        node = *l;
        *l = node->nextNode;
        show(node->data);
        free(node->data);
        free(node);
    }
}
void showListReverse(const tList* l, void(*show)(const void*)){
    if(*l){
        showListReverse((&(*l)->nextNode), show);
        show((*l)->data);
    }
}
void showAndClearListReverse(tList* l, void(*show)(const void*)){
    if(*l){
        showAndClearListReverse((&(*l)->nextNode), show);
        show((*l)->data);
        free((*l)->data);
        free(*l);
    }
    *l = NULL;
}
void showListReverseFiltered(const tList* l, const void* key,
                             void(*show)(const void*),
                             int(*cmp)(const void*, const void*)){
    if(*l){
        showListReverseFiltered((&(*l)->nextNode), key, show, cmp);
        if(!cmp(key, (*l)->data))
            show((*l)->data);
    }
}
void removeCoincidencesFromList(tList* l, const void* key,
                                int(*cmp)(const void*, const void*)){
    tNode* node;
    while(*l){
        if(!cmp((*l)->data, key)){
            node = *l;
            *l = node->nextNode;
            free(node->data);
            free(node);
        }
        else{
            showInt((*l)->data);//solo para corroborar que muestra los que no son Key
            l = &(*l)->nextNode;
            /*showInt((*l)->data); Si pongo esto despues del nextNode se
                                   rompe por desreferenciar null (EXCEPTO QUE EL
                                   ULT ELEMENTO SEA = KEY*/
        }
    }
}
void removeElementByPosition(tList* l, int position){
    tNode* node;

    if(position <= 0)
        return;

    while(*l && position--){
        if(!position){
            node = *l;
            *l = node->nextNode;
            free(node->data);
            free(node);
            return;
        }
        l = &(*l)->nextNode;
    }
}
void sortList(tList* l, int(*cmp)(const void*, const void*)){
    tList* firstNode;
    tList* auxList;
    tNode* node;

    firstNode = l;

    if(!*l)
        return;

    while((*l)->nextNode){
        if(cmp((*l)->data, (*l)->nextNode->data) > 0){
            auxList = firstNode;
            node = (*l)->nextNode;
            (*l)->nextNode = node->nextNode;
            while(cmp((*auxList)->data, node->data) < 0)
                auxList = &(*auxList)->nextNode;
            node->nextNode = *auxList;
            *auxList = node;
        }
        else
            l = &(*l)->nextNode;
    }
}

void sortListBySelection(tList* l, int(*cmp)(const void*, const void*)){
    tList* minorNode;
    tNode* auxNode;

    if(!*l)
        return;

    while((*l)->nextNode){
        minorNode = findMinor(l, cmp);
        if(minorNode != l){
            auxNode = *minorNode;
            *minorNode = auxNode->nextNode;
            auxNode->nextNode = *l;
            *l = auxNode;
        }
        l = &((*l)->nextNode);
    }
}
tList* findMinor(tList* l, int(*cmp)(const void*, const void*))
{
    tList* minor;

    minor = l;
    l = &(*l)->nextNode;

    while(*l){
        if(cmp((*l)->data, (*minor)->data) < 0)
            minor = l;
        l = &(*l)->nextNode;
    }

    return minor;
}




void showInt(const void* data){
    fprintf(stdout, "%d ", *(int*)data);
}
void showString (const void* data){
    fprintf(stdout, "%s\n", (char*)data);
}
int cmpKey(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}

void createBatch(const char* fileName){
    int i;
    FILE* file;
    tProduct products[] =
    {
        {"P000001", "Product A", "Provider X", {10, 1, 2023}, {10, 1, 2024}, 100, 10.0, 151.0},
        {"P000002", "Product B", "Provider Y", {5, 4, 2023}, {5, 4, 2024}, 50, 20.0, 302.0},
        {"P000003", "Product C", "Provider Z", {20, 7, 2023}, {20, 7, 2024}, 200, 8.0, 127.0},
        {"P000004", "Product D", "Provider X", {15, 3, 2023}, {15, 3, 2024}, 80, 12.0, 188.0},
        {"P000005", "Product E", "Provider Y", {8, 6, 2023}, {8, 6, 2024}, 120, 15.0, 259.0},
        {"P000006", "Product F", "Provider Z", {25, 9, 2023}, {3, 10, 2024}, 150, 9.0, 145.0},
        {"P000007", "Product G", "Provider X", {12, 2, 2023}, {12, 2, 2024}, 90, 11.0, 179.0},
        {"P000008", "Product H", "Provider Y", {7, 5, 2023}, {7, 5, 2024}, 60, 18.0, 7772877.0},
        {"P000009", "Product I", "Provider Z", {22, 8, 2023}, {22, 8, 2024}, 180, 10.0, 8881645.0},
        {"P000010", "Product J", "Provider X", {18, 12, 2023}, {18, 12, 2024}, 70, 14.0, 882274.0},
        {"P000011", "Product K", "Provider Y", {3, 10, 2023}, {3, 10, 2024}, 100, 16.0, 994226.0},
        {"P000012", "Product L", "Provider Z", {9, 11, 2023}, {3, 10, 2024}, 110, 13.0, 8820.0},
        {"P000013", "Product M", "Provider X", {16, 2, 2023}, {3, 10, 2024}, 85, 11.5, 86318.5},
        {"P000014", "Product N", "Provider Y", {12, 5, 2023}, {3, 10, 2024}, 75, 19.0, 5529.0},
        {"P000015", "Product O", "Provider Z", {28, 8, 2023}, {3, 10, 2024}, 95, 9.5, 815.5},
        {"P000016", "Product P", "Provider X", {13, 7, 2023}, {3, 10, 2024}, 105, 12.5, 19.5},
        {"P000017", "Product Q", "Provider Y", {19, 4, 2023}, {19, 4, 2024}, 125, 14.5, 824.5},
        {"P000018", "Product R", "Provider Z", {23, 1, 2023}, {23, 1, 2024}, 145, 8.5, 13.5},
        {"P000019", "Product S", "Provider X", {6, 10, 2023}, {6, 10, 2024}, 155, 11.0, 917.0},
        {"P000020", "Product T", "Provider Y", {11, 11, 2023}, {11, 11, 2024}, 165, 17.0, 627.0},
        {"P000021", "Product U", "Provider Z", {4, 6, 2023}, {4, 6, 2024}, 175, 10.5, 616.5},
        {"P000022", "Product V", "Provider X", {21, 9, 2023}, {3, 10, 2024}, 185, 12.0, 218.0},
        {"P000023", "Product W", "Provider Y", {17, 12, 2023}, {17, 12, 2024}, 195, 15.0, 125.0},
        {"P000024", "Product X", "Provider Z", {14, 3, 2023}, {14, 3, 2024}, 205, 9.0, 614.0},
        {"P000025", "Product Y", "Provider X", {1, 1, 2023}, {1, 1, 2024}, 215, 10.0, 6616.0},
        {"P000026", "Product Z", "Provider Y", {30, 4, 2023}, {30, 4, 2024}, 225, 12.0, 920.0},
        {"P000027", "Product AA", "Provider Z", {24, 7, 2023}, {3, 10, 2024}, 235, 13.0, 8821.0},
        {"P000028", "Product BB", "Provider X", {27, 10, 2023}, {27, 10, 2024}, 245, 14.0, 8722.0},
        {"P000029", "Product CC", "Provider Y", {2, 5, 2023}, {2, 5, 2024}, 255, 16.0, 7826.0},
        {"P000030", "Product DD", "Provider Z", {29, 8, 2023}, {29, 8, 2024}, 265, 18.0, 278.0}
    };

    openFile(&file, fileName, "wb");

    for(i = 0; i < sizeof(products)/sizeof(tProduct); i ++){
        fwrite(&products[i], sizeof(tProduct), 1, file);
    }

    fclose(file);
}
int openFile(FILE** file, const char* fileName, const char* openMode){
    if((*file = fopen(fileName, openMode)) == NULL){
        perror("Oops! Something went wrong");
        return -1;
    }
    return 0;
}
//int traverseBinaryFile(const char* fileName, size_t dataSize,
//                       void(*action)(const void* data, void* context),
//                       void* context){
//    FILE* file;
//    void* data;
//
//    if(!(data = malloc(dataSize)))
//        return MEM_ERR;
//
//    if(openFile(&file, fileName, "rb"))
//        return FILE_ERR;
//
//    fread(data, dataSize, 1, file);
//
//    while(!feof(file)){
//        action(data);
//        fread(data, dataSize, 1, file);
//    }
//
//    free(data);
//    fclose(file);
//    return OK;
//}
int loadListWithMostExpensiveProducts(tList* listPointer,
                                      int nElements, const char* fileName,
                                      size_t dataSize,
                                      int(*cmp)(const void*, const void*)){
    FILE* file;
    void* data;

    if(!(data = malloc(dataSize)))
        return MEM_ERR;

    if(openFile(&file, fileName, "rb"))
        return FILE_ERR;

    fread(data, dataSize, 1, file);

    while(!feof(file) && nElements > 0){
        insertSorted(listPointer, data, dataSize, cmp);
        nElements--;
        fread(data, dataSize, 1, file);
    }
    while(!feof(file)){
        if(cmp(data, (*listPointer)->data) > 0){
            _removeFirstFromList(listPointer, dataSize);
            insertSorted(listPointer, data, dataSize, cmp);
        }
        fread(data, dataSize, 1, file);
    }

    free(data);
    fclose(file);
    return OK;
}
int _removeFirstFromList(tList* listPointer, size_t dataSize){
    tNode* node;

    if(!(*listPointer))
        return 0;

    node = *listPointer;
    *listPointer = node->nextNode;

    free(node->data);
    free(node);

    return 1;
}

int traverseAndRecordBinaryFileWithList(const char* fileName, size_t dataSize,
                                        int(*cmp)(const void*, const void*),
                                        int(*action)(tList*, const void*, size_t,
                                        int(*cmp)(const void*, const void*))){
    tList l;
    FILE* file;
    FILE* tempFile;
    void* data;

    createList(&l);

    if(!(data = malloc(dataSize)))
        return -1;

    if(openFile(&file, fileName, "rb") || openFile(&tempFile, "temp", "wb")){
        fclose(file);
        return -2;
    }

    fread(data, dataSize, 1, file);

    while(!feof(file)){
        action(&l, data, dataSize, cmp);
        fread(data, dataSize, 1, file);
    }

    while(removeFirstFromList(&l, data, dataSize))
        fwrite(data, dataSize, 1, tempFile);

    free(data);

    clearList(&l);

    fclose(file);
    fclose(tempFile);

    remove(fileName);
    rename("temp", fileName);

    return 0;
}
int traverseAndRecordBinaryFileSortingList(const char* fileName, unsigned dataSize,
                                        int(*cmp)(const void*, const void*),
                                        int(*action)(tList*, const void*, unsigned)){
    tList l;
    FILE* file;
    FILE* tempFile;
    void* data;

    createList(&l);

    if(!(data = malloc(dataSize)))
        return -1;

    if(openFile(&file, fileName, "rb") || openFile(&tempFile, "temp", "wb")){
        fclose(file);
        return -2;
    }

    fread(data, dataSize, 1, file);

    while(!feof(file)){
        action(&l, data, dataSize);
        fread(data, dataSize, 1, file);
    }

    sortListBySelection(&l, cmp);

    while(removeFirstFromList(&l, data, dataSize))
        fwrite(data, dataSize, 1, tempFile);

    free(data);

    clearList(&l);

    fclose(file);
    fclose(tempFile);

    remove(fileName);
    rename("temp", fileName);

    return 0;
}
int insertSorted(tList* l, const void* data, size_t dataSize,
                 int(*cmp)(const void*, const void*)){
    tNode* node;

    if(!(node = malloc(sizeof(tNode))) || !(node->data = malloc(dataSize))){
        free(node);
        return -1;
    }

    while(*l && cmp(data, (*l)->data) > 0)
        l = &((*l)->nextNode);

    memcpy(node->data, data, dataSize);
    node->dataSize = dataSize;
    node->nextNode = *l;
    *l = node;

    return 0;
}

int removeNLastElements(tList* l, unsigned n)
{
    int elements = n;

    if((*l)->nextNode){
        elements = removeNLastElements(&((*l)->nextNode), n);
        elements--;
    }

    if(elements > 0){
        free((*l)->data);
        free(*l);
        *l = NULL;
    }

    return elements;
}

int cmpDateProviderId (const void* a, const void* b){
    if(!cmpDate(a, b)){
        if(!cmpProvider(a, b))
            return cmpId(a, b);
        return cmpProvider(a, b);
    }
    return cmpDate(a, b);
}
int cmpId (const void* a, const void* b){
    return strcmp(((tProduct*)a)->id, ((tProduct*)b)->id);
}
int cmpProvider (const void* a, const void* b){
    return strcmp(((tProduct*)a)->provider, ((tProduct*)b)->provider);
}
int cmpPrice(const void* a, const void* b){
    return (((tProduct*)a)->sellingPrice - ((tProduct*)b)->sellingPrice);
}
int cmpDate (const void* a, const void* b){
    if(((tProduct*)a)->expirationDate.year -
       ((tProduct*)b)->expirationDate.year == 0){
        if(((tProduct*)a)->expirationDate.month -
           ((tProduct*)b)->expirationDate.month == 0)
            return ((tProduct*)a)->expirationDate.day - ((tProduct*)b)->expirationDate.day;
        return ((tProduct*)a)->expirationDate.month - ((tProduct*)b)->expirationDate.month;
       }
    return ((tProduct*)a)->expirationDate.year - ((tProduct*)b)->expirationDate.year;
}
/**
    typedef struct{
        char id[7];
        char description[15];
        char provider[15];
        tDate purchaseDate;
        tDate expirationDate;
        int quantity;
        float buyingPrice;
        float sellingPrice;
    }tProduct;
*/
void showProduct(const void* product){
    fprintf(stdout,
            "=======================================\n"
            "ID: %s\nDescription: %s\nProvider: %s\n"
            "Purchase Date: %02d-%02d-%04d\nExpiration Date: %02d-%02d-%04d\n"
            "Quantity: %0d\nBuying Price: %0.2f\nSelling Price: %0.2f\n",
            ((tProduct*)product)->id,
            ((tProduct*)product)->description,
            ((tProduct*)product)->provider,
            ((tProduct*)product)->purchaseDate.day,
            ((tProduct*)product)->purchaseDate.month,
            ((tProduct*)product)->purchaseDate.year,
            ((tProduct*)product)->expirationDate.day,
            ((tProduct*)product)->expirationDate.month,
            ((tProduct*)product)->expirationDate.year,
            ((tProduct*)product)->quantity,
            ((tProduct*)product)->buyingPrice,
            ((tProduct*)product)->sellingPrice);
}
void showIdExpDateProvider(const void* product){
    fprintf(stdout,
            "=======================================\n"
            "ID: %s\nProvider: %s\nExpiration Date: %02d-%02d-%04d\n",
            ((tProduct*)product)->id,
            ((tProduct*)product)->provider,
            ((tProduct*)product)->expirationDate.day,
            ((tProduct*)product)->expirationDate.month,
            ((tProduct*)product)->expirationDate.year);
}

/**Dynamic Stack primitives*/

void createStack(tStack* s){
    *s = NULL;
}
int pushStack(tStack* s, const void* data, unsigned dataSize){
    tNode* node;
    if((node = (tNode*)malloc(sizeof(tNode))) == NULL ||
       (node->data = malloc(dataSize)) == NULL){
        free(node);
        return 0;
    }
    return 1;
}
int popStack(tStack* s, void* data, unsigned dataSize);
