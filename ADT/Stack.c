#include "Stack.h"
/*
void createStack(tStack* s){
    *s = NULL;
}

int isStackEmpty(const tStack* s){
    return *s == NULL;
}

int pushStack(tStack* s, const void* info, unsigned infoSize){
    tNode* newElement;

    if((newElement = (tNode*)malloc(sizeof(tNode))) == NULL ||
       (newElement->info = malloc(infoSize)) == NULL){
        free(newElement);
        return 0;
    }

    memcpy(newElement->info, info, infoSize);
    newElement->infoSize = infoSize;
    newElement->nextNode = *s;
    *s = newElement;

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

int popStack(tStack* s, void* data, unsigned sizeOfData){
    tNode* aux;

    if(!*s)
        return 0;

    aux = *s;
    memcpy(data, aux->info, MIN(sizeOfData, aux->infoSize));//I can require less info than is stored.
    *s = aux->nextNode;
    free(aux->info);
    free(aux);

    return 1;
}

int seeTop(tStack* s, void* data, unsigned sizeOfData){
    if(!*s)
        return 0;

    memcpy(data, (*s)->info, MIN(sizeOfData, (*s)->infoSize));//I can require less info than is stored.

    return 1;
}

int isStackFull(const tStack *s, unsigned sizeOfData){
    tNode* aux = (tNode*)malloc(sizeof(tNode));
    void* info = malloc(sizeOfData);

    free(aux);
    free(info);

    return aux == NULL || info == NULL;
}
*/
void createStack(tStack* s){
    s->top = STACK_SIZE;
}
int isStackEmpty(const tStack* s){
    return s->top == STACK_SIZE;
}

int isStackFull(const tStack *s, unsigned sizeOfData){
    return s->top < sizeOfData + sizeof(unsigned);
}

int pushStack(tStack* s, const void* info, unsigned infoSize){
    if(s->top < infoSize + sizeof(unsigned))
        return 0;

    s->top -= infoSize;
    memcpy(s->sstack + s->top, info, infoSize);
    s->top -= sizeof(unsigned);
    memcpy(s->sstack + s->top, &infoSize, sizeof(unsigned));

    return 1;
}

void clearStack(tStack* s){
    s->top = STACK_SIZE;
}

int popStack(tStack* s, void* data, unsigned sizeOfData){
    unsigned dataSize;

    if(s->top == STACK_SIZE)
        return 0;

    memcpy(&dataSize, s->sstack + s->top, sizeof(unsigned));
    s->top +=  sizeof(unsigned);
    memcpy(data, s->sstack + s->top + sizeof(unsigned),
           MIN(dataSize, sizeOfData));
    s->top +=  dataSize;

    return 1;
}

int seeTop(tStack* s, void* data, unsigned sizeOfData){
    unsigned dataSize;

    if(s->top == STACK_SIZE)
        return 0;

    memcpy(&dataSize, s->sstack + s->top, sizeof(unsigned));
    memcpy(data, s->sstack + s->top + s->top + sizeof(unsigned),
           MIN(dataSize, sizeOfData));

    return 1;
}
