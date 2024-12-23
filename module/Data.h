#ifndef DATA_H
#define DATA_H
#include<stdbool.h>

typedef struct Data {
   bool is_op;
   int value;
} Data;

void copyData(Data* dst, Data* src);

////////////////////////////////////

void copyData(Data* dst, Data* src)
{
    *dst = *src;
}

#endif
