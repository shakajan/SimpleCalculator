#ifndef DATA_H
#define DATA_H
#include<stdbool.h>

typedef struct Data {
   bool is_op;
   long long value;
} Data;

void copyData(Data* dst, Data* src);
void dataInit(Data* data, bool is_op, long long value);
////////////////////////////////////

void copyData(Data* dst, Data* src)
{
    *dst = *src;
}

void dataInit(Data* data, bool is_op, long long value)
{
    data->is_op = is_op;
    data->value = value;
}

#endif
