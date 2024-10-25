#include "../s21_smart_calc.h"

typedef struct {
  double sum;  // сумма вклада
  int term;    // срок размещения (в месяцах)
  double rate;  // процентная ставка (в десятичном виде)
  double tax_rate;  // налоговая ставка (в десятичном виде)
  int pay_freq;  // периодичность выплат (количество платежей за срок
                 // размещения)
  int cap_freq;  // капитализация процентов (количество капитализаций за срок
                 // размещения)
  double *additions;  // список пополнений (массив сумм пополнений)
  int num_additions;  // количество пополнений
  double *withdrawals;  // список частичных снятий (массив сумм снятий)
  int num_withdrawals;  // количество снятий
} Deposit;

void calculate_deposit(Deposit *deposit, double *interest, double *tax,
                       double *result) {
  double total_additions = 0;    // общая сумма пополнений
  double total_withdrawals = 0;  // общая сумма снятий
  *interest = 0;  // общая сумма начисленных процентов
  *tax = 0;       // сумма налога
  double balance = deposit->sum;  // текущая сумма на вкладе

  // осуществляем пополнения и снятия
  for (int i = 0; i < deposit->num_additions; i++) {
    total_additions += deposit->additions[i];
    balance += deposit->additions[i];
    for (int j = 0; j < deposit->cap_freq && j < deposit->pay_freq; j++) {
      double current_interest = balance * deposit->rate / 1200;
      *interest += current_interest;
      balance += current_interest;
    }
    if (i < deposit->num_withdrawals) {
      total_withdrawals += deposit->withdrawals[i];
      balance -= deposit->withdrawals[i];
    }
  }

  // вычисляем сумму налога
  if (*interest > 0) {
    *tax = *interest * deposit->tax_rate;
  }

  // возвращаем общую сумму на вкладе к концу срока
  *result = balance + *interest - *tax;
}

// int main() {
//     Deposit deposit = {
//         100000, // сумма вклада
//         12, // срок размещения (в месяцах)
//         5, // процентная ставка (в десятичном виде)
//         0.13, // налоговая ставка (в десятичном виде)
//         12, // периодичность выплат (количество платежей за срок размещения)
//         12, // капитализация процентов (количество капитализаций за срок
//         размещения) (double[]) {10000, 5000}, // список пополнений (массив
//         сумм пополнений) 2, // количество пополнений (double[]) {5000, 3000},
//         // список частичных снятий (массив сумм снятий) 2 // количество
//         снятий
//     };

//     double interest, tax, result;
//     calculate_deposit(&deposit, &interest, &tax, &result);
//     printf("Начисленные проценты: %.2f\n", interest);
//     printf("Сумма налога: %.2f\n", tax);
//     printf("Сумма на вкладе к концу срока: %.2f\n", result);

//     return 0;
// }