
// description: implements Stack with linked-list.
// depends on "Node.h" file.

#ifndef STACK_H
#define STACK_H


#include "Node.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct Stack {
    struct Node* top;
    int size;
} Stack;

void stackInit(Stack* s);
void stackDestroy(Stack* s);

Data stackTop(Stack* s);
void stackPush(Stack* s, Data data);
Data stackPop(Stack* s);
bool stackIsEmpty(Stack* s);
int stackSize(Stack* s);

///////////////////////////////////////

void stackInit(Stack* s)
{
    s->top = NULL;
    s->size = 0;
}

void stackDestroy(Stack* s)
{
    while(stackIsEmpty(s) == false)
        stackPop(s);
}


void stackPush(Stack* s, Data data) {
    Node* new_node = malloc(sizeof(Node));
    copyData(&new_node->data, &data);
    new_node -> next = s->top;
    s->top = new_node;
    s->size++;
}

// warning : should be used after asserting stackIsEmpty == false
Data stackPop(Stack* s) {
    Node* old_node = s->top;
    Data old_data;
    copyData(&old_data, &old_node->data);
    s->top = old_node->next;
    free(old_node);
    s->size--;
    return old_data;
}

// warning : should be used after asserting stackIsEmpty == false
Data stackTop(Stack* s)
{
    return s->top->data;
}

bool stackIsEmpty(Stack* s)
{
    return s->size == 0;
}


int stackSize(Stack* s)
{
    return s->size;
}


void stackDescribe(Stack* s)
{
    Node* iterator = s->top;
    while( iterator != NULL) {
        describeData(&(iterator->data));
        iterator = iterator -> next;
    }
    printf("stack descrive done.\n");
}
#endif
