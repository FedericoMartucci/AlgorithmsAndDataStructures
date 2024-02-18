#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (X < Y ? (X) : (Y))

/**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~o~~~x~~~o~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
 *                          Dynamic implementation                             *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~o~~~x~~~o~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**/

/*

typedef struct sNodo
{
    void            *info;
    unsigned         infoSize;
    struct sNodo    *nextNode;
} tNode;

typedef tNode *tStack;

void createStack(tStack* s);
int isStackEmpty(const tStack* s);
int pushStack(tStack* s, const void* info, unsigned infoSize);
void clearStack(tStack* s);
int popStack(tStack* s, void* data, unsigned sizeOfData);
int seeTop(tStack* s, void* data, unsigned sizeOfData);
int isStackFull(const tStack *s, unsigned sizeOfData);

*/

/**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~o~~~x~~~o~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
 *                          Static implementation                              *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~o~~~x~~~o~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**/

#define STACK_SIZE 400

typedef struct
{
    char sstack[STACK_SIZE];
    unsigned top;
} tStack;

void createStack(tStack* s);
int isStackEmpty(const tStack* s);
int pushStack(tStack* s, const void* info, unsigned infoSize);
void clearStack(tStack* s);
int popStack(tStack* s, void* data, unsigned sizeOfData);
int seeTop(tStack* s, void* data, unsigned sizeOfData);
int isStackFull(const tStack *s, unsigned sizeOfData);

#endif // STACK_H_INCLUDED
