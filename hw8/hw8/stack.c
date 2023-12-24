#include <stdio.h>
#include "mice.h"

#define SIZE 10

void stackInit(Stack *p){
    p->top = 0;
}

int stackFull(Stack *p) {
    return (p->top >= SIZE*SIZE+1);
}

int stackEmpty(Stack *p) {
    return (p->top <= 0);
}

void push(Stack *p, Pos pos) {
    if(stackFull(p)){
        printf("stack is full\n");
        return;
    }
    p->cell[p->top++] = pos;
}

Pos pop(Stack *p) {
    if(!stackEmpty(p))
        return (p->cell[--p->top]);
    printf("stack is empty\n");
}
