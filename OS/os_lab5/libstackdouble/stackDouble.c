#include "stackDouble.h"

void DStackCreate(DStack *stack) {
    stack->Head = stack->Tail = NULL;
}
void DStackPush(DStack *stack, double data) {
    Node *tmp = (Node*)malloc(sizeof(Node));
    if(tmp == NULL) {
        exit(OUT_OF_MEMORY);
    }
    tmp->Next = stack->Head;
    tmp->Data = data;
    stack->Head = tmp;
}
Node* DStackPop1(DStack *stack) {
    Node *out;
    if(stack->Head == NULL) {
        exit(STACK_UNDERFLOW);
    }
    out = stack->Head;
    stack->Head = stack->Head->Next;
    return out;
}
double DStackPop2(DStack *stack) {
    Node *out;
    double value;
    if(stack->Head == NULL) {
        exit(STACK_UNDERFLOW);
    }
    out = stack->Head;
    stack->Head = stack->Head->Next;
    value = out->Data;
    free(out);
    return value;
}
size_t DStackSize(DStack* stack) {
    return stack->numof;
}
void DStackDelete(DStack *stack) {
    Node *tmp;
    while(stack->Head != NULL) {
        tmp = stack->Head;
        stack->Head = stack->Head->Next;
        free(tmp);
    }
}
