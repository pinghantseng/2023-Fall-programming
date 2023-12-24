#ifndef __MICE__
#define __MICE__

#define SIZE 10

typedef struct _Pos {
    int x;
    int y;
} Pos;

typedef struct _Stack {
    Pos cell[SIZE*SIZE];
    int top;
} Stack;

void stackInit(Stack *p);
int stackFull(Stack *p);
int stackEmpty(Stack *p);
void push(Stack *p, Pos pos);
Pos pop(Stack *p);

#endif
