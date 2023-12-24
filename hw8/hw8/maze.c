#include <stdio.h>
#include "mice.h"

#define SIZE 10

int maze[SIZE][SIZE] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 0, 0, 0, 1, 1, 0, 1, 1, 0, 1 },
    { 1, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
    { 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
    { 1, 0, 1, 1, 1, 0, 0, 1, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
    { 1, 0, 1, 1, 1, 1, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

int dirx[4] = {0, 1, 0, -1};
int diry[4] = {1, 0, -1, 0};

int ans[SIZE][SIZE] = {0};

Pos find(Stack *p, Pos pos){
    printf("move to %d, %d\n", pos.x, pos.y);
    maze[pos.x][pos.y] = 1;
    int num = 0;
    Pos next;
    for(int k = 0; k < 4; k++){
        if(maze[pos.x + dirx[k]][pos.y + diry[k]] == 0){
            num++;
            if(num == 1){
                next.x = pos.x + dirx[k];
                next.y = pos.y + diry[k];
            }else{
                Pos wait = {pos.x + dirx[k], pos.y + diry[k]};
                push(p, wait);
            }
        }
    }
    if(num != 0){
        return next;
    }else{
        if(!stackEmpty(p))
            return pop(p);
        else{
            Pos empty = {-1, -1};
            return empty;
        }
    }
}

int main(){
    Stack stack;
    Pos extrance = {1, 0};
    Pos exit = {6, 9};
    stackInit(&stack);
    Pos pos = find(&stack, extrance);
    while(pos.x != exit.x || pos.y != exit.y){
        if(pos.x == -1 && pos.y == -1){
            printf("No Exit!\n");
            break;
        }
        pos = find(&stack, pos);
    }
    return 0;
}
