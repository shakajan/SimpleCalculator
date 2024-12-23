#include "module/Stack.h"
#include "module/Queue.h"
#include "module/Data.h"
#include <memory.h>
#include <stdbool.h>

#define TOKEN_CAPACITY 255
#define OPERATOR_CAPACITY 4
typedef struct Calculator {
    char operator_priority[5];
    Data* tokens[TOKEN_CAPACITY];
    int token_len;
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
static bool isOperator(Calculator* calculator, const char character);
static void tokenizeOperator(Calculator* calculator, const char string[], int string_ptr);
static void tokenizeOperand (Calculator* calculator, const char string[], int* string_ptr);

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
    calculator->token_len = 0;
}


int calculate(Calculator* calculator, const char string[])
{
    tokenize(calculator, string);   // convert string to tokens.
    convert(calculator);            // convert tokens to postfix order.
    return evaluate(calculator);    // calculate postfix order.
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
    int string_len = strlen(string);
    int string_ptr = 0;
    while(string_ptr < string_len) {
        switch(string[string_ptr]) {
            case ' ':
                break;
            case '(':
                // push to stack.
                break;
            case ')':
                // pop stack, and push it to the queue until pop stack == '('
                break;
            default:
                if(isOperator(calculator, string[string_ptr]))
                    tokenizeOperator(calculator, string, string_ptr);

                else if('0' <= string[string_ptr] && string[string_ptr] <= '9') 
                    tokenizeOperand(calculator, string, &string_ptr);

                else {
                    // wrong formula
                }
        }
        string_ptr++;
    }
}


static int evaluate(Calculator* calculator);




static bool isOperator(Calculator* calculator, const char character)
{
    for(int i = 0; i < OPERATOR_CAPACITY; i++) {
        if(calculator->operatorPriority[i] == character) {
            return true;
        }
    }
    return false;
}

static void tokenizeOperator(Calculator* calculator, const char string[], int  string_ptr)
{
    Data* new_data = malloc(sizeof(Data));
    dataInit(new_data, false, string[string_ptr]);
    calculator->tokens[calculator->token_len++] = new_data;
}

static void tokenizeOperand (Calculator* calculator, const char string[], int* string_ptr)
{
    long long value = 0;
    for(int i = 0; i < 18; i++) {
        value = value * 10 + (long long) (string[*string_ptr] - '0');

        char end_checker = string[(*string_ptr) + 1];
        if(end_checker < '0' || end_checker > '9')
            break;
        else
            (*string_ptr)++;
    }

    Data* new_data = malloc(sizeof(Data));
    dataInit(new_data, true, value);
    calculator->tokens[calculator->token_len++] = new_data;
}
