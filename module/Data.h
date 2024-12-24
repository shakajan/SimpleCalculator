#ifndef DATA_H
#define DATA_H
#include<stdbool.h>
#include<stdio.h>

typedef struct Data {
   bool is_op;
   long long value;
} Data;

void copyData(Data* dst, Data* src);
void dataInit(Data* data, bool is_op, long long value);
void describeData(Data* data);

////////////////////////////////////

void copyData(Data* dst, Data* src)
{
    *dst = *src;
}

void dataInit(Data* data, bool is_op, long long value)
{
    data->is_op = is_op;
    data->value = value;

    //printf("new data! is_op: %d, value: %lld\n", is_op, value);
}

void describeData(Data* data)
{
    printf("is_op : %s , value: %lld (%c) \n", data->is_op ? "true " : "false", data->value, (char) data->value);
}
#endif
