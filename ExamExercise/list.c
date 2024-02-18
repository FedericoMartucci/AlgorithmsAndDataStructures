#include "file.h"

void createList(tList* l)
{
    *l = NULL;
}
void clearList(tList* l)
{
    tNode* aux;
    while(*l){
        aux = *l;
        *l = aux->nextNode;
        showProductWithoutProvider(aux->data);
        free(aux->data);
        free(aux);
    }
}
int insertToEnd(tList* l, const void* data, unsigned dataSize)
{
    tNode* node;
    if(!(node = (tNode*)malloc(sizeof(tNode))) ||
       !(node->data = malloc(dataSize))){
        free(node);
        return MEM_ERR;
    }

    while(*l)
        l = &(*l)->nextNode;

    memcpy(node->data, data, dataSize);
    node->dataSize = dataSize;
    node->nextNode = *l;
    *l = node;

    return OK;
}
int insertToEndWithoutProvider(tList* l, const void* data, unsigned dataSize)
{
    tProductWithoutProvider product;

    strcpy(product.id, ((tProduct*)data)->id);
    strcpy(product.description, ((tProduct*)data)->description);
    product.purchaseDate.day = ((tProduct*)data)->purchaseDate.day;
    product.purchaseDate.month = ((tProduct*)data)->purchaseDate.month;
    product.purchaseDate.year = ((tProduct*)data)->purchaseDate.year;
    product.expirationDate.day = ((tProduct*)data)->expirationDate.day;
    product.expirationDate.month = ((tProduct*)data)->expirationDate.month;
    product.expirationDate.year = ((tProduct*)data)->expirationDate.year;
    product.quantity = ((tProduct*)data)->quantity;
    product.buyingPrice = ((tProduct*)data)->buyingPrice;
    product.sellingPrice = ((tProduct*)data)->sellingPrice;

    insertToEnd(l, &product, sizeof(tProductWithoutProvider));

    return OK;
}

/**File functions*/

int createBatch(const char* fileName)
{
    tProduct products[] =
    {
      {"P000001", "Provider X", "Description 1", {1, 2, 2000}, {1, 2, 2000}, 111, 222.11, 222.22},
      {"P000002", "Provider X", "Description 2", {2, 12, 2003}, {2, 12, 2001}, 111, 333.11, 333.22},
      {"P000003", "Provider Z", "Description 3", {3, 11, 2003}, {2, 5, 2001}, 111, 444.11, 444.22},
      {"P000004", "Provider X", "Description 4", {4, 3, 2003}, {3, 4, 2002}, 111, 555.11, 555.22},
      {"P000005", "Provider X", "Description 1", {5, 5, 2003}, {4, 2, 2002}, 111, 111.11, 222.22},
      {"P000006", "Provider X", "Description 2", {1, 7, 2002}, {5, 2, 2002}, 111, 222.11, 444.22},
      {"P000001", "Provider Y", "Description 3", {1, 7, 2001}, {5, 5, 2003}, 111, 333.11, 444.22},
      {"P000001", "Provider Y", "Description 1", {1, 7, 2003}, {5, 5, 2003}, 111, 333.11, 444.22},
      {"P000002", "Provider Y", "Description 2", {2, 7, 2003}, {5, 5, 2003}, 111, 333.11, 333.22},
      {"P000002", "Provider Z", "Description 2", {2, 7, 2001}, {5, 5, 2004}, 111, 111.11, 333.22},
      {"P000003", "Provider Z", "Description 1", {5, 7, 2001}, {6, 4, 2003}, 111, 111.11, 222.22},
      {"P000001", "Provider Z", "Description 3", {5, 7, 2002}, {6, 10, 2004}, 111, 222.11, 222.22},
      {"P000001", "Provider Z", "Description 5", {8, 7, 2002}, {6, 11, 2003}, 111, 111.11, 222.22},
      {"P000005", "Provider X", "Description 6", {8, 4, 2002}, {6, 12, 2004}, 111, 111.11, 555.22},
      {"P000007", "Provider Y", "Description 7", {12, 4, 2003}, {1, 4, 2005}, 111, 111.11, 555.22},
      {"P000008", "Provider X", "Description 8", {13, 4, 2003}, {1, 4, 2005}, 111, 111.11, 555.22},
      {"P000009", "Provider X", "Description 4", {13, 4, 2003}, {1, 4, 2003}, 111, 111.11, 222.22}
    };

    FILE* file;

    if(openFile(&file, fileName, "wb") != OK)
        return FILE_ERR;

    fwrite(products, sizeof(products), 1, file);

    fclose(file);
    return OK;
}
int openFile(FILE** file, const char* fileName, const char* openMode)
{
    if((*file = fopen(fileName, openMode)) == NULL){
        perror("Oops! Something went wrong");
        return FILE_ERR;
    }

    return OK;
}
int traverseFileWithList(const char* fileName, unsigned dataSize, int(*action)(tList*, const void*, unsigned))
{
    FILE* file;
    void* product;
    tList l;

    createList(&l);

    if(!(product = malloc(dataSize)))
        return MEM_ERR;

    if(openFile(&file, fileName, "rb") != OK){
        free(product);
        return FILE_ERR;
    }

    fread(product, dataSize, 1, file);
    while(!feof(file)){
        action(&l, product, dataSize);
        fread(product, dataSize, 1, file);
    }

    clearList(&l);

    free(product);
    fclose(file);
    return OK;
}
/**Show functions*/
/*
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
*/
void showProduct(const void* product)
{
    fprintf(stdout, "\n=====================\n"
            "ID: %s\nProvider: %s\nDescription: %s\n"
            "Purchase date: %02d-%02d-%04d\nExpiration date: %02d-%02d-%04d\n"
            "Quantity: %d\nBuying price: %0.2f\nSelling price: %0.2f",
            ((tProduct*)product)->id,
            ((tProduct*)product)->provider,
            ((tProduct*)product)->description,
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
void showProductWithoutProvider(const void* product)
{
    fprintf(stdout, "\n=====================\n"
            "ID: %s\nDescription: %s\n"
            "Purchase date: %02d-%02d-%04d\nExpiration date: %02d-%02d-%04d\n"
            "Quantity: %d\nBuying price: %0.2f\nSelling price: %0.2f",
            ((tProductWithoutProvider*)product)->id,
            ((tProductWithoutProvider*)product)->description,
            ((tProductWithoutProvider*)product)->purchaseDate.day,
            ((tProductWithoutProvider*)product)->purchaseDate.month,
            ((tProductWithoutProvider*)product)->purchaseDate.year,
            ((tProductWithoutProvider*)product)->expirationDate.day,
            ((tProductWithoutProvider*)product)->expirationDate.month,
            ((tProductWithoutProvider*)product)->expirationDate.year,
            ((tProductWithoutProvider*)product)->quantity,
            ((tProductWithoutProvider*)product)->buyingPrice,
            ((tProductWithoutProvider*)product)->sellingPrice);
}
