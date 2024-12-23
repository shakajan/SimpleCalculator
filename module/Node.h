#ifndef NODE_H
#define NODE_H

#include "Data.h"

typedef struct Node {
    Data data;
    struct Node* next;
} Node;

#endif
