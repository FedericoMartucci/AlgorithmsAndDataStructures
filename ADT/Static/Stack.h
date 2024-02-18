#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) ((X < Y)? (X) : (Y))

#define STACK_SIZE 160

typedef struct
{
    char sstack[STACK_SIZE];
    unsigned top;
}tStack;

void createStack(tStack* s);
int isStackEmpty(const tStack* s);
int isStackFull(const tStack* s, unsigned dataSize);
int pushStack(tStack* s, const void* data, unsigned dataSize);
int popStack(tStack* s, void* data, unsigned dataSize);
void clearStack(tStack* s);
int seeStackTop(const tStack* s, void* data, unsigned dataSize);

#endif // STACK_H_INCLUDED
