#include "creditcalc.h"

#include "ui_creditcalc.h"

extern "C" {
#include "../s21_smart_calc.h"
}

CreditCalc::CreditCalc(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);

  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
  connect(ui->Ann_button, SIGNAL(clicked()), this, SLOT(ann_clicked()));
  connect(ui->Diff_button, SIGNAL(clicked()), this, SLOT(diff_clicked()));
  connect(ui->Eq_button, SIGNAL(clicked()), this, SLOT(eq_clicked()));
  ui->Month_label->setVisible(false);
  ui->Month_spinBox->setVisible(false);
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::ann_clicked() {
  ui->Month_label->setVisible(false);
  ui->Month_spinBox->setVisible(false);
}

void CreditCalc::diff_clicked() {
  ui->Month_label->setVisible(true);
  ui->Month_spinBox->setVisible(true);
}

void CreditCalc::eq_clicked() {
  double payment = 0, perc = 0, total = 0;
  int k = ui->Months_button->isChecked() ? 1 : 12;
  LoanParams params;
  params.amount = ui->Amount_spinBox->value();
  params.term = ui->Term_spinBox->value();
  params.rate = ui->Rate_doubleSpinBox->value();
  params.k = k;
  params.type = ui->Ann_button->isChecked() ? 0 : 1;
  params.month = ui->Month_spinBox->value();
  s21_calculate_loan(params, &payment, &perc, &total);
  ui->Payment->setText(QString::number(payment, 'f', 2));
  ui->Percentage->setText(QString::number(perc, 'f', 2));
  ui->All->setText(QString::number(total, 'f', 2));
}