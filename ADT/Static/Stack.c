#include "Stack.h"

void createStack(tStack* s){
    s->top = STACK_SIZE;
}
int isStackEmpty(const tStack* s){
    return s->top == STACK_SIZE;
}
int isStackFull(const tStack* s, unsigned dataSize){
    return s->top < dataSize + sizeof(unsigned);
}
int pushStack(tStack* s, const void* data, unsigned dataSize){
    if(s->top < dataSize + sizeof(unsigned))//preguntar si esto lo puedo reemplazar por pilaLLena()
        return 0;

    s->top -= dataSize;
    memcpy(s->sstack + s->top, data, dataSize);
    s->top -= sizeof(unsigned);
    memcpy(s->sstack + s->top, &dataSize, sizeof(unsigned));

    return 1;
}
int popStack(tStack* s, void* data, unsigned dataSize){
    unsigned infoSize;

    if(s->top == STACK_SIZE)
        return 0;

    memcpy(&infoSize, s->sstack + s->top, sizeof(unsigned));
    s->top += sizeof(unsigned);
    memcpy(data, s->sstack + s->top, MIN(dataSize, infoSize));
    s->top += infoSize;

    return 1;

}
void clearStack(tStack* s){
    s->top = STACK_SIZE;
}
int seeStackTop(const tStack* s, void* data, unsigned dataSize){
    unsigned infoSize;

    if(s->top == STACK_SIZE)
        return 0;

    memcpy(&infoSize, s->sstack + s->top, sizeof(unsigned));
    memcpy(data, s->sstack + s->top + sizeof(unsigned), MIN(dataSize, infoSize));

    return 1;
}
