#include "../s21_smart_calc.h"

// Функция рассчета платежа в зависимости от типа кредита
void s21_calculate_loan(LoanParams params, double *pay, double *perc,
                        double *total) {
  double m_rate = params.rate / 12.0 / 100.0;
  int time = params.term * params.k;

  if (params.type == 0) {
    // Аннуитетный платеж
    *pay = params.amount * (m_rate * pow(1 + m_rate, time)) /
           (pow(1 + m_rate, time) - 1);
    *perc = (*pay * time) - params.amount;
    *total = params.amount + *perc;
  } else {
    // Дифференцированный платеж
    double tmp = params.amount / (params.term * params.k);
    for (int i = 0; i < params.term * params.k; i++) {
      double interest_payment = params.amount * m_rate;
      if (i + 1 == params.month) *pay = interest_payment + tmp;
      *total += tmp + interest_payment;
      *perc += interest_payment;
      params.amount -= tmp;
    }
  }
}
