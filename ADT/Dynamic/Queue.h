#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) ((X < Y)? (X) : (Y))

typedef struct sNode
{
    void* info;
    unsigned infoSize;
    struct sNode*  nextNode;
}tNode;

typedef struct
{
    tNode* firstNode;
    tNode* lastNode;
}tQueue;

void createQueue(tQueue* q);
int enqueue(tQueue* q, const void* data, unsigned dataSize);
int dequeue(tQueue* q, void* data, unsigned dataSize);
int isEmptyQueue(const tQueue* q);
int isFullQueue(const tQueue* q, unsigned dataSize);
int seeFirstNodeInQueue(const tQueue* q, void* data, unsigned dataSize);
void clearQueue(tQueue* q);

#endif // QUEUE_H_INCLUDED
