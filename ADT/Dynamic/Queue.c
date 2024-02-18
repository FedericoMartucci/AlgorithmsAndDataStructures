#include "Queue.h"

void createQueue(tQueue* q){
    q->firstNode = NULL;
    q->lastNode = NULL;
}

int enqueue(tQueue* q, const void* data, unsigned dataSize){
    tNode* aux;

    if((aux = (tNode*)malloc(sizeof(tNode))) == NULL ||
       (aux->info = malloc(dataSize)) == NULL){
        free(aux);
        return 0;
    }

    if(!q->firstNode)//preguntar si esta bien
        q->firstNode = aux;
    else
        q->lastNode->nextNode = aux;

    q->lastNode = aux;
    memcpy(aux->info, data, dataSize);
    aux->infoSize = dataSize;
    aux->nextNode = NULL;

    return 1;
}

int dequeue(tQueue* q, void* data, unsigned dataSize){
    tNode* aux;

    if(q->firstNode == NULL)
        return 0;

    aux = q->firstNode;
    q->firstNode = aux->nextNode;
    memcpy(data, (q->firstNode->info), MIN(q->firstNode->infoSize, dataSize));

    free(aux->info);
    free(aux);

    if(q->firstNode == NULL)
        q->lastNode = NULL;

    return 1;
}
int isEmptyQueue(const tQueue* q){
    return q->firstNode == NULL;
}

int isFullQueue(const tQueue* q, unsigned dataSize){//no se usa tQueue, para que lo necesito
    tNode* aux = (tNode*)malloc(sizeof(tNode));
    void* info = malloc(dataSize);

    free(aux);
    free(info);

    return aux == NULL || info == NULL;
}

int seeFirstNodeInQueue(const tQueue* q, void* data, unsigned dataSize){
    if(q->firstNode == NULL)
        return 0;

    memcpy(data, (q->firstNode->info), MIN(q->firstNode->infoSize, dataSize));

    return 1;
}

void clearQueue(tQueue* q){
    while(q->firstNode){
        tNode* aux = q->firstNode;
        q->firstNode = aux->nextNode;
        free(aux->info);
        free(aux);
    }
    q->lastNode = NULL;
}
