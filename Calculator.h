#include "module/Stack.h"
#include "module/Queue.h"
#include "module/Data.h"
#include <memory.h>
#include <stdbool.h>

#define TOKEN_CAPACITY 255
#define OPERATOR_CAPACITY 6
typedef struct Calculator {
    char operator_priority[OPERATOR_CAPACITY];
    Data* tokens[TOKEN_CAPACITY];
    int token_len;
    Stack* stack;
    Queue* queue;
} Calculator;

// public use
void calculatorInit(Calculator* calculator);
long long calculate(Calculator* calculator, const char string[]);
void calculatorDestroy(Calculator* calculator);

// private use
static void tokenize(Calculator* calculator, const char string[]);
static void convert(Calculator* calculator);
static long long evaluate(Calculator* calculator);
static bool isOperator(Calculator* calculator, const char character);
static int getPriority(Calculator* calculator, const char character);
static void tokenizeOperator(Calculator* calculator, const char string[], int string_ptr);
static void tokenizeOperand (Calculator* calculator, const char string[], int* string_ptr);
static void describeTokens(Calculator* calculator);
static void describeToken(Data* data);
static void describePostfix(Calculator* calculator);

///////////////////////////////////////////

void calculatorInit(Calculator* calculator)
{
    calculator->operator_priority[0] = '-';
    calculator->operator_priority[1] = '+';

    calculator->operator_priority[2] = '*';
    calculator->operator_priority[3] = '/';

    calculator->operator_priority[4] = '(';
    calculator->operator_priority[5] = ')';

    
    calculator->stack = malloc(sizeof(Stack));
    calculator->queue = malloc(sizeof(Queue));

    stackInit(calculator->stack);
    queueInit(calculator->queue);

    memset(calculator->tokens, 0, sizeof(calculator->tokens));
    calculator->token_len = 0;
}


long long calculate(Calculator* calculator, const char string[])
{
    tokenize(calculator, string);   // convert string to tokens.
    convert(calculator);            // convert tokens to postfix order.
    return evaluate(calculator);    // calculate postfix order.
}

void calculatorDestroy(Calculator* calculator)
{
    for(int i = 0; i < TOKEN_CAPACITY; i++)
        if(calculator->tokens[i] != NULL)
            free(calculator->tokens[i]);

    stackDestroy(calculator->stack);
    queueDestroy(calculator->queue);
    free(calculator->stack);
    free(calculator->queue);
}

//////////////

static void tokenize(Calculator* calculator, const char string[])
{
    int string_len = strlen(string);
    int string_ptr = -1;
    while(++string_ptr < string_len) {
        if(isOperator(calculator, string[string_ptr])) {
            tokenizeOperator(calculator, string, string_ptr);
        }

        else if('0' <= string[string_ptr] && string[string_ptr] <= '9') {
            tokenizeOperand(calculator, string, &string_ptr);
        }

        else if (string[string_ptr] == ' ') {
            continue;
        
        } else {}
    }
}

static void convert(Calculator* calculator)
{
    for(int i = 0; i < calculator->token_len; i++) {
        Data token = *(calculator->tokens[i]);

        if(token.is_op == true) {

            if(token.value == '(') {
                stackPush(calculator->stack, token);
                continue;
            }

            if(token.value == ')') {
                while(1) {
                    Data data = stackPop(calculator->stack);
                    if(data.is_op == true && data.value == '(')
                        break;
                    else
                        enqueue(calculator->queue, data);
                }
                continue;
            }
            int token_priority = getPriority(calculator, (char) token.value);
            if(stackIsEmpty(calculator->stack)) {
                stackPush(calculator->stack, token);
            } else {
                Data data = stackTop(calculator->stack);
                int data_priority = getPriority(calculator, (char) data.value);
                
                if(data_priority == 2) { // ( or )
                    stackPush(calculator->stack, token);
                    continue;
                }

                if(token_priority > data_priority) {
                    stackPush(calculator->stack, token);
                } else if(token_priority == data_priority) {
                    enqueue(calculator->queue, stackPop(calculator->stack));
                    stackPush(calculator->stack, token);
                } else {
                    enqueue(calculator->queue, stackPop(calculator->stack));
                    if(! stackIsEmpty(calculator->stack) && \
                        (getPriority(calculator, (char) stackTop(calculator->stack).value) == token_priority)) {
                        enqueue(calculator->queue, stackPop(calculator->stack));
                    }
                    stackPush(calculator->stack, token);
                }
            }
        } else {
            enqueue(calculator->queue, token);
        }
    }

    while( ! stackIsEmpty(calculator->stack)) {
        enqueue(calculator->queue, stackPop(calculator->stack));
    }
}




static long long evaluate(Calculator* calculator)
{
//  describePostfix(calculator);

    while(queueIsEmpty(calculator->queue) == false) {
        Data data = dequeue(calculator->queue);
        if(data.is_op == false) {
            stackPush(calculator->stack, data);
        } else {
            Data left, right, tmp;
            tmp.is_op = false;

            right = stackPop(calculator->stack);
            left  = stackPop(calculator->stack);
            
            if(data.value == '*')
                tmp.value = left.value * right.value;
            if(data.value == '/')
                tmp.value = left.value / right.value;
            if(data.value == '+')
                tmp.value = left.value + right.value;
            if(data.value == '-')
                tmp.value = left.value - right.value;
            stackPush(calculator->stack, tmp);
        }
    }
    Data last = stackPop(calculator->stack);
    return last.value;
}




static bool isOperator(Calculator* calculator, const char character)
{
    for(int i = 0; i < OPERATOR_CAPACITY; i++) {
        if(calculator->operator_priority[i] == character) {
            return true;
        }
    }
    return false;
}




static int getPriority(Calculator* calculator, const char character)
{
    for(int i = 0; i < OPERATOR_CAPACITY; i++) {
        if(calculator->operator_priority[i] == character) {
            return i / 2;
        }
    }
    printf("error: getProirity : param : %c (%3d) \n", character, character);
    return -1;
}

static void describeTokens(Calculator* calculator)
{
    for(int i = 0; i < calculator->token_len; i++) {
        printf("[%d]: is_op: %d, value: %lld\n", i, calculator->tokens[i]->is_op, calculator->tokens[i]->value);
    }
    printf("describeTokens done.\n");
}

static void describeToken(Data* data)
{
    printf("is_op: %s, value: %lld\n", data->is_op ? "true " : "false", data->value);
}

static void tokenizeOperator(Calculator* calculator, const char string[], int  string_ptr)
{
    Data* new_data = malloc(sizeof(Data));
    dataInit(new_data, true, string[string_ptr]);
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
    dataInit(new_data, false, value);
    calculator->tokens[calculator->token_len++] = new_data;
}

static void describePostfix(Calculator* calculator)
{
    if(queueIsEmpty(calculator->queue)) {
        printf("describePostfix: queue is empty.\n");
        return;
    }

    Node* itr = calculator->queue->front;
    while(itr != NULL) {
        Data data = itr->data;
        if(data.is_op) {
            printf("%c ", (char) data.value);
        } else {
            printf("%lld ", data.value);
        }
        itr = itr->next;
    }
    printf("\n");
}
