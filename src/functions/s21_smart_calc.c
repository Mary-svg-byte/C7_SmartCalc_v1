#include "../s21_smart_calc.h"

double all_calculation(const char* math_expression, char* x) {
  size_t math_expression_length = strlen(math_expression);

  // Выделение памяти под строку с математическим выражением в виде обратной
  // польской нотации
  char* postfix_math_expression = (char*)malloc(math_expression_length * 3 + 1);

  // Add null character at the end of the allocated string
  postfix_math_expression[0] = '\0';

  infixToPrefix(math_expression, postfix_math_expression, x);

  double result = eval_postfix(postfix_math_expression);

  free(postfix_math_expression);
  return result;
}

void infixToPrefix(const char* math_expression, char* postfix_math_expression,
                   char* x) {
  // Создание стека
  StringStack* stack = create_string_stack();

  process_expression(math_expression, stack, postfix_math_expression, x);
  // printf("Rev_pol: \n%s\n", postfix_math_expression);
  free(stack);
}

void process_expression(const char* math_expression, StringStack* stack,
                        char* postfix_math_expression, char* x) {
  // Разбиение выражения на лексемы
  parse(math_expression, stack, postfix_math_expression, x);

  while (!is_string_stack_empty(stack)) {
    if (strcmp(peep_string(stack), "(") != 0 &&
        strcmp(peep_string(stack), ")") != 0) {
      char* popped_data = pop_string(stack);
      strcat(postfix_math_expression, popped_data);
      free(popped_data);
      strcat(postfix_math_expression, " ");
    }
  }
}

void parse(const char* str, StringStack* stack, char* postfix_math_expression,
           char* x) {
  int i = 0, len = strlen(str);  // инициализируем счетчик и длину строки
  char lexeme[100];             // буфер для лексемы
  char prev_lexeme[100] = {0};  // буфер для предыдущей лексемы
  char unar_lexeme[100] = {0};  // буфер для унарной лексемы

  while (i < len) {  // пока не достигнут конец строки
    if (isspace(str[i])) {  // если текущий символ - пробел
      i++;  // переходим к следующему символу
    } else if (isalnum(str[i])) {  // если текущий символ - буква или цифра
      int j = 0;  // сброс счетчика
      while (
          i < len &&
          ((isalnum(str[i])) ||
           (str[i] == '.'))) {  // пока встречаются буквы или цифры, или точка
        lexeme[j++] = str[i++];  // сохраняем их в буфер лексемы
      }
      lexeme[j] = '\0';  // добавляем завершающий нуль
      if (strlen(unar_lexeme) != 0) {  // если буфер унарной лексемы не пуст
        strcat(unar_lexeme, lexeme);  // добавляем текущую лексему к унарной
        process_token(
            unar_lexeme, stack,
            postfix_math_expression);  // вызываем функцию обработки токена
        memset(unar_lexeme, 0,
               sizeof(unar_lexeme));  // очищаем буфер унарной лексемы
      } else {
        if (strcmp(lexeme, "x") == 0) {
          strcpy(lexeme, x);
        }
        process_token(
            lexeme, stack,
            postfix_math_expression);  // вызываем функцию обработки токена
      }
      strcpy(prev_lexeme,
             lexeme);  // сохраняем текущую лексему в буфер предыдущей лексемы
    } else {  // если текущий символ - не пробел, буква или цифра
      lexeme[0] = str[i++];  // сохраняем текущий символ в буфер лексемы
      lexeme[1] = '\0';  // усекаем буфер лексемы до одного символа
      if (((strcmp(lexeme, "-") == 0) || (strcmp(lexeme, "+") == 0)) &&
          ((strcmp(prev_lexeme, "(") == 0) ||
           (strcmp(prev_lexeme, "\0") == 0) ||
           (is_operator(prev_lexeme)))) {  //
        strcat(unar_lexeme, lexeme);  // добавляем текущую лексему к унарной
      } else {
        process_token(
            lexeme, stack,
            postfix_math_expression);  // вызываем функцию обработки токена
      }
      strcpy(prev_lexeme,
             lexeme);  // сохраняем текущую лексему в буфер предыдущей лексемы
    }
  }
}

void process_token(char* token, StringStack* stack,
                   char* postfix_math_expression) {
  if (is_digit_double(token) || (is_digit_int(token))) {
    strcat(postfix_math_expression, token);
    strcat(postfix_math_expression, " ");
  } else if (is_function(token)) {
    push_string(stack, token);
  } else if (is_open_parenthesis(token)) {
    push_string(stack, token);
  } else if (is_operator(token)) {
    while (!is_string_stack_empty(stack) &&
           (get_priority(peep_string(stack)) >= get_priority(token))) {
      char* popped_data = pop_string(stack);
      strcat(postfix_math_expression, popped_data);
      free(popped_data);
      strcat(postfix_math_expression, " ");
    }
    push_string(stack, token);
  } else if (is_close_parenthesis(token)) {
    while (!is_string_stack_empty(stack) &&
           (strcmp(peep_string(stack), "(") != 0)) {
      char* popped_data = pop_string(stack);
      strcat(postfix_math_expression, popped_data);
      free(popped_data);
      strcat(postfix_math_expression, " ");
    }
    if (!is_string_stack_empty(stack) &&
        (strcmp(peep_string(stack), "(") == 0)) {
      char* popped_data = pop_string(stack);
      free(popped_data);
    }
  }
}

int is_digit_int(char str[]) {
  regex_t regex;
  int ret;

  ret = regcomp(&regex, "^[-+]?[0-9]+$", REG_EXTENDED);

  ret = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);

  if (ret) {
    return 0;
  }

  return 1;
}

int is_digit_double(char str[]) {
  regex_t regex;
  int ret;

  ret =
      regcomp(&regex, "[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?", REG_EXTENDED);

  ret = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);

  if (ret) {
    return 0;
  }

  return 1;
}

int is_function(char str[]) {
  regex_t regex;
  int ret;

  ret = regcomp(&regex, "cos|sin|tan|acos|asin|atan|sqrt|ln|log", REG_EXTENDED);

  ret = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);

  if (ret) {
    return 0;
  }

  return 1;
}

int is_open_parenthesis(char str[]) { return strcmp(str, "(") == 0; }

int is_close_parenthesis(char str[]) { return strcmp(str, ")") == 0; }

int get_priority(char* input_operator) {
  Operator operators[] = {
      {"(", 1},   {")", 1},    {"+", 2},   {"-", 2},    {"*", 3},
      {"/", 3},   {"%", 3},    {"^", 4},   {"cos", 5},  {"acos", 5},
      {"sin", 5}, {"asin", 5}, {"tan", 5}, {"atan", 5}, {"sqrt", 5},
      {"ln", 5},  {"log", 5},
  };
  int operators_count = sizeof(operators) / sizeof(operators[0]);
  int data = -1;
  for (int i = 0; i < operators_count; i++) {
    if (strcmp(input_operator, operators[i].operator_pr) == 0) {
      data = operators[i].priority;
    }
  }

  return data;
}

int is_operator(char str[]) {
  int ret;
  regex_t regex;

  // Регулярное выражение для поиска одного из символов: -+/*%
  const char* pattern = "[-+/*^%]";

  // Компиляция регулярного выражения
  ret = regcomp(&regex, pattern, REG_EXTENDED);

  // Поиск первого совпадения с регулярным выражением
  ret = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);
  if (ret == REG_NOMATCH) {
    return 0;
  }
  return 1;
}

double eval_postfix(char* postfix_expression) {
  DoubleStack* stack = create_double_stack();
  char* token = strtok(postfix_expression, " ");
  double result;
  // printf("token = %s\n", token);
  while (token != NULL) {
    if (is_digit_int(token) || is_digit_double(token)) {
      double num = atof(token);
      // printf("num = %f\n", num);
      push_double(stack, num);
    } else {
      double second_operand = pop_double(stack);
      double first_operand = is_operator(token) ? pop_double(stack) : 0;

      if (strcmp(token, "+") == 0) {
        result = first_operand + second_operand;
      } else if (strcmp(token, "-") == 0) {
        result = first_operand - second_operand;
      } else if (strcmp(token, "*") == 0) {
        result = first_operand * second_operand;
      } else if (strcmp(token, "/") == 0) {
        result = first_operand / second_operand;
      } else if (strcmp(token, "%") == 0) {
        result = fmod(first_operand, second_operand);
      } else if (strcmp(token, "^") == 0) {
        result = pow(first_operand, second_operand);
      } else {
        // function call
        if (strcmp(token, "sin") == 0) {
          result = sin(second_operand);
        } else if (strcmp(token, "cos") == 0) {
          result = cos(second_operand);
        } else if (strcmp(token, "tan") == 0) {
          result = tan(second_operand);
        } else if (strcmp(token, "acos") == 0) {
          result = acos(second_operand);
        } else if (strcmp(token, "asin") == 0) {
          result = asin(second_operand);
        } else if (strcmp(token, "atan") == 0) {
          result = atan(second_operand);
        } else if (strcmp(token, "sqrt") == 0) {
          result = sqrt(second_operand);
        } else if (strcmp(token, "ln") == 0) {
          result = log(second_operand);
        } else if (strcmp(token, "log") == 0) {
          result = log10(second_operand);
        }
      }
      push_double(stack, result);
    }

    token = strtok(NULL, " ");
  }

  double final_result = pop_double(stack);
  free(stack);
  return final_result;
}
