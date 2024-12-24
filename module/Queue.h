#ifndef QUEUE_H
#define QUEUE_H

#include "Data.h"
#include "Node.h"
#include <stdbool.h>

typedef struct Queue {
    Node *front, *back;
    int size;
} Queue;

void queueInit(Queue* queue);
void queueDestroy(Queue* queue);

void enqueue(Queue* queue, Data data);
Data dequeue(Queue* queue);
bool queueIsEmpty(Queue* queue);
int queueSize(Queue* queue);

//////////////////////////////////////

void queueInit(Queue* queue)
{
    queue->front = queue->back = NULL;
    queue->size = 0;
}

void queueDestroy(Queue* queue)
{
    while(queueIsEmpty(queue) == false)
        dequeue(queue);
}

void enqueue(Queue* queue, Data data) {
    Node* new_node = malloc(sizeof(Node));
    copyData(&new_node->data, &data);
    new_node->next = NULL;

    if(queueIsEmpty(queue))
        queue->front = new_node;
    else
        queue->back->next = new_node;

    queue->back = new_node;
    queue->size++;
}

// warning : should be used after asserting QueueIsEmpty == false
Data dequeue(Queue* queue) {
    Node* old_node = queue->front;
    Data old_data;
    copyData(&old_data, &old_node->data);
    queue->front = old_node->next;
    queue->size--;
    if(queueIsEmpty(queue))
        queue->back = NULL;
    return old_data;
}

bool queueIsEmpty(Queue* queue)
{
    return queue->size == 0;
}

int queueSize(Queue* queue)
{
    return queue->size;
}

void queueDescribe(Queue* queue)
{
    Node* itr = queue->front;
    printf("front :: ");
    while(itr != NULL) {
        describeData(&itr->data);
        itr = itr->next;
    }
    printf(":: back\n");
}

#endif
