#include "Stack.h"

void createStack(tStack* s){
 *s = NULL;
}
int isStackEmpty(const tStack* s){
    return *s == NULL;
}
int isStackFull(const tStack* s, unsigned dataSize){
    tNode* aux = (tNode*)malloc(sizeof(tNode));
    void* info = malloc(dataSize);

    free(aux);
    free(info);

    return info == NULL || aux == NULL;
}
int pushStack(tStack* s, const void* data, unsigned sizeOfData){
    tNode* aux;

    if(((aux = (tNode*)malloc(sizeof(tNode))) == NULL) ||
       (((aux->info = malloc(sizeOfData)) == NULL))){
        free(aux);
        return 0;
    }

    memcpy(aux->info, data, sizeOfData);
    aux->infoSize = sizeOfData;
    aux->nextNode = *s;
    *s = aux;

    return 1;

}
int popStack(tStack* s, void* data, unsigned sizeOfData){
    tNode* aux;

    if(!*s)
        return 0;

    memcpy(data, (*s)->info, MIN(sizeOfData, (*s)->infoSize));
    aux = *s;
    *s = aux->nextNode;
    free(aux->info);
    free(aux);

    return 1;

}
void clearStack(tStack* s){
    tNode* aux;

    while(*s){
        aux = *s;
        *s = aux->nextNode;
        free(aux->info);
        free(aux);
    }
}
int seeStackTop(const tStack* s, void* data, unsigned sizeOfData){
    if(!*s)
        return 0;

    memcpy(data, (*s)->info, MIN(sizeOfData, (*s)->infoSize));

    return 1;
}
