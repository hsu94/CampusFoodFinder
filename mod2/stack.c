#include<stdio.h>
#include "stack.h"

void init(Stack *S)
{
    S->top = 0;
}

void push(Stack *S, int val)
{
    S->x[ S->top ] = val;
   (S->top)++;
}

int pop(Stack *S)
{
    (S->top)--;
    return (S->x[S->top]);
}



