#ifndef S21_SMART_CALC_H
#define S21_SMART_CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include <ctype.h>

//Stack
typedef struct Node {
    char* data;
    struct Node* next;
} StringNode;

typedef struct Stack {
    StringNode* top;
} StringStack;

StringStack* create_string_stack();
int is_string_stack_empty(StringStack* stack);
void push_string(StringStack* stack, char* data);
char* pop_string(StringStack* stack);
char* peep_string(StringStack* stack);
void print_string_stack(StringStack* stack);
void free_string_stack(StringStack* stack);

typedef struct NodeDouble {
    double data;
    struct NodeDouble* next;
} DoubleNode;

typedef struct StackDouble {
    DoubleNode* top;
} DoubleStack;

DoubleStack* create_double_stack();
int is_double_stack_empty(DoubleStack* stack);
void push_double(DoubleStack* stack, double data);
double pop_double(DoubleStack* stack);
double peep_double(DoubleStack* stack);
void printdouble_stack(DoubleStack* stack);
void free_double_stack(DoubleStack* stack);


//Calc

typedef struct {
    char *operator_pr;
    int priority;
} Operator;

int is_digit_int(char str[]);
int is_digit_double(char str[]);
int is_function(char str[]);
int is_operator(char str[]);
int get_priority(char* input_operator);
int is_open_parenthesis(char str[]);
int is_close_parenthesis(char str[]);
int getPriority(char *input_operator);

double all_calculation(const char* math_expression, char* x);
void infixToPrefix(const char* math_expression, char* postfix_math_expression, char* x);
void process_expression(const char* math_expression, StringStack* stack, char* postfix_math_expression, char* x);
void parse(const char*str, StringStack* stack, char* postfix_math_expression, char* x); 
void process_token(char* token, StringStack* stack, char* postfix_math_expression);
double eval_postfix(char* postfix_expression);

// Структура для хранения параметров кредита
typedef struct {
   double amount;        // Сумма кредита
   double term;         // Срок кредита в годах
   double rate;          // Процентная ставка в год
   int month;           // Номер месяца, для которого необходимо рассчитать платеж
   int k;               // Количество раз в год, которое осуществляется платеж (например, для ежемесячного платежа k=12)
   int type;            // 0 для аннуитетного платежа, 1 для дифференцированного платежа
} LoanParams;

void s21_calculate_loan(LoanParams params, double *pay, double *perc, double *total);

#endif
