#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) ((X < Y)? (X) : (Y))

typedef struct sNode{
    void* info;
    unsigned infoSize;
    struct sNode* nextNode;
}tNode;

typedef tNode* tStack;

void createStack(tStack* s);
int isStackEmpty(const tStack* s);
int isStackFull(const tStack* s, unsigned dataSize);
int pushStack(tStack* s, const void* data, unsigned sizeOfData);
int popStack(tStack* s, void* data, unsigned sizeOfData);
void clearStack(tStack* s);
int seeStackTop(const tStack* s, void* data, unsigned sizeOfData);
#endif // STACK_H_INCLUDED
