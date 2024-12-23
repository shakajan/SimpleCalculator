#include "module/Stack.h"
#include "module/Queue.h"
#include "module/Data.h"
#include <memory.h>

#define TOKEN_CAPACITY 255

typedef struct Calculator {
    char operator_priority[5];
    Data* tokens[TOKEN_CAPACITY];
    Stack* stack;
    Queue* queue;
} Calculator;

// public use
void calculatorInit(Calculator* calculator);
int calculate(Calculator* calculator, const char string[]);
void calculatorDestroy(Calculator* calculator);

// private use
static void tokenize(Calculator* calculator, const char string[]);
static int evaluate(Calculator* calculator);

///////////////////////////////////////////

void calculatorInit(Calculator* calculator)
{
    calculator->operator_priority[0] = '-';
    calculator->operator_priority[1] = '+';

    calculator->operator_priority[2] = '*';
    calculator->operator_priority[3] = '/';
    
    calculator->stack = malloc(sizeof(Stack));
    calculator->queue = malloc(sizeof(Queue));
    
    *(calculator->stack) = *(calculator->queue) = NULL;
    memset(calculator->tokens, 0, sizeof(calculator->tokens));
}


int calculate(Calculator* calculator, const char string[])
{
    tokenize(calculator, string);
    return evaluate(calculator);
}

void calculatorDestroy(Calculator* calculator)
{
    for(int i = 0; i < TOKEN_SIZE; i++)
        if(calculator->tokens[i] != NULL)
            free(calculator->tokens[i]);

    stackDestroy(calculator->stack);
    queueDestroy(calculator->queue);
}



//////////////

static void tokenize(Calculator* calculator, const char string[])
{

static int evaluate(Calculator* calculator);
