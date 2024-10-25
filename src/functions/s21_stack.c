#include "../s21_smart_calc.h"

char* strdup(const char* str) {
  size_t size = strlen(str) + 1;
  char* dst = malloc(size);
  if (dst != NULL) {
    memcpy(dst, str, size);
  }
  return dst;
}

StringStack* create_string_stack() {
  StringStack* stack = (StringStack*)malloc(sizeof(StringStack));
  stack->top = NULL;
  return stack;
}

int is_string_stack_empty(StringStack* stack) { return stack->top == NULL; }

void push_string(StringStack* stack, char* data) {
  StringNode* newNode = (StringNode*)malloc(sizeof(StringNode));
  newNode->data = strdup(data);
  newNode->next = stack->top;
  stack->top = newNode;
}

char* pop_string(StringStack* stack) {
  char* data;
  if (is_string_stack_empty(stack)) {
    printf("String stack is Empty\n");
    data = "Err";
  } else {
    data = stack->top->data;
    StringNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
  }
  return data;
}

char* peep_string(StringStack* stack) {
  char* data;

  if (is_string_stack_empty(stack)) {
    printf("String stack is Empty\n");
    data = "Err";
  } else {
    data = stack->top->data;
  }
  return data;
}

DoubleStack* create_double_stack() {
  DoubleStack* stack = (DoubleStack*)malloc(sizeof(DoubleStack));
  stack->top = NULL;
  return stack;
}

int is_double_stack_empty(DoubleStack* stack) { return stack->top == NULL; }

void push_double(DoubleStack* stack, double data) {
  DoubleNode* newNode = (DoubleNode*)malloc(sizeof(DoubleNode));
  newNode->data = data;
  newNode->next = stack->top;
  stack->top = newNode;
}

double pop_double(DoubleStack* stack) {
  double data;
  if (is_double_stack_empty(stack)) {
    printf("Double stack is Empty\n");
    data = NAN;
  } else {
    data = stack->top->data;
    DoubleNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
  }
  return data;
}