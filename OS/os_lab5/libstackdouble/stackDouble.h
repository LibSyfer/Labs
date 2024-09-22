#ifndef STACK_DOUBLE_H
#define STACK_DOUBLE_H

#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *Next;
    double Data;
} Node;

typedef struct DStack {
    Node *Head, *Tail;
    int numof;
} DStack;

void DStackCreate(DStack*);
void DStackPush(DStack*, double);
Node* DStackPop1(DStack*);
double DStackPop2(DStack*);
size_t DStackSize(DStack*);
void DStackDelete(DStack*);

#endif
