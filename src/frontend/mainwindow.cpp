#include "mainwindow.h"

#include "./ui_mainwindow.h"

extern "C" {
#include "../s21_smart_calc.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  resize(450, 495);
  ui->result_show->setMaxLength(255);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(symb_clicked()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(symb_clicked()));
  connect(ui->pushButton_asterisk, SIGNAL(clicked()), this,
          SLOT(symb_clicked()));
  connect(ui->pushButton_slash, SIGNAL(clicked()), this, SLOT(symb_clicked()));
  connect(ui->pushButton_open_parenthesis, SIGNAL(clicked()), this,
          SLOT(symb_clicked()));
  connect(ui->pushButton_close_parenthesis, SIGNAL(clicked()), this,
          SLOT(symb_clicked()));
  connect(ui->pushButton_exp, SIGNAL(clicked()), this, SLOT(symb_clicked()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(func_clicked()));

  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(func_clicked()));

  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(mod_clicked()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(symb_clicked()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(dot_clicked()));
  connect(ui->pushButton_del, SIGNAL(clicked()), this,
          SLOT(clear_one_clicked()));
  connect(ui->pushButton_ac, SIGNAL(clicked()), this,
          SLOT(clear_all_clicked()));

  connect(ui->pushButton_calc, SIGNAL(clicked()), this,
          SLOT(calculate_expression()));

  connect(ui->pushButton_Graph, SIGNAL(clicked()), this, SLOT(show_Graph()));

  connect(ui->pushButton_credit_mod, SIGNAL(clicked()), this,
          SLOT(credit_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::mod_clicked() {
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();

  ui->last_expr->setText("");
  if (expression.length() < 255) {
    // Если выражение заканчивается на точку, то не добавляем новый символ
    if (expression.back() != '.' || expression.length() == 0) {
      if (expression == "0") {
        expression = "%";
      } else {
        expression += "%";
      }
    }

    ui->result_show->setText(expression);
  }
}

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();

  if (expression.length() < 255) {
    // If the current expression is "0" or "-0", replace it with the new digit
    if (expression == "0" || expression == "-0") {
      expression = button_text;
    } else {
      expression += button_text;
    }

    ui->result_show->setText(expression);
  }
}

void MainWindow::symb_clicked() {
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();

  if (expression.length() < 255) {
    // Если выражение заканчивается на точку, то не добавляем новый символ
    if (expression.back() != '.' || expression.length() == 0) {
      if (expression == "0") {
        expression = button_text;
      } else {
        expression += button_text;
      }
    }
    ui->result_show->setText(expression);
  }
}

void MainWindow::func_clicked() {
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();

  // ui->last_expr->setText("");
  if (expression.length() < 252) {
    // Если выражение заканчивается на точку, то не добавляем новый символ
    if (expression.back() != '.' || expression.length() == 0) {
      if (expression == "0") {
        expression = button_text + "(";
      } else {
        expression += button_text + "(";
      }
    }

    ui->result_show->setText(expression);
  }
}

void MainWindow::dot_clicked() {
  QString current_text = ui->result_show->text();
  QPushButton *button = qobject_cast<QPushButton *>(sender());

  // ui->last_expr->setText("");

  // Проверяем, содержит ли текущее состояние поля ввода цифру перед точкой
  if (current_text.at(current_text.length() - 1).isDigit() &&
      current_text.back() != '.') {
    // Добавляем точку в конец текущего состояния поля ввода
    expression += button->text();
    ui->result_show->setText(expression);
  }
}

void MainWindow::clear_one_clicked() {
  QString current_text = ui->result_show->text();

  // Удаляем последний символ из текущего состояния поля ввода
  // Используем trimmed(), чтобы удалить лишние пробелы в начале и конце строки
  ui->result_show->setText(
      current_text.trimmed().left(current_text.length() - 1));

  // Обновляем выражение, удаляя последний символ
  expression = expression.left(expression.length() - 1);
}

void MainWindow::clear_all_clicked() {
  ui->result_show->setText("0");
  ui->last_expr->setText("");
  expression = "0";
}

bool MainWindow::check_parentheses(const QString &expression) {
  int open_parentheses = 0;
  int closed_parentheses = 0;

  for (int i = 0; i < expression.length(); i++) {
    if (expression.at(i) == '(') {
      open_parentheses++;
    } else if (expression.at(i) == ')') {
      closed_parentheses++;
    }

    if (closed_parentheses > open_parentheses) {
      return false;  // too many closed parentheses
    }
  }

  return open_parentheses == closed_parentheses;
}

void MainWindow::show_Graph() {
  if (expression.isEmpty()) {
    QMessageBox::warning(this, tr("Error"),
                         tr("Invalid input: empty expression."));
    return;
  }

  bool containsX = expression.contains("x");
  if (!containsX) {
    QMessageBox::warning(this, tr("Error"),
                         tr("Invalid input: missing variable x."));
    return;
  }

  QString x_value_str = ui->x_value->text();
  if (!x_value_str.isEmpty()) {
    QMessageBox::warning(this, tr("Error"),
                         tr("Invalid input: missing value for x."));
    return;
  }

  resize(955, 495);

  double xMin = ui->x_min->value();
  double xMax = ui->x_max->value();

  ui->customPlot->clearGraphs();
  ui->customPlot->addGraph();
  ui->customPlot->xAxis->setRange(xMin, xMax);

  double yMin = ui->y_min->value();
  double yMax = ui->y_max->value();
  double yRange = yMax - yMin;
  int numPoints = 2000;
  double yStep = yRange / numPoints;

  QVector<double> x(numPoints);
  QVector<double> y(numPoints);

  for (int i = 0; i < numPoints; i++) {
    x[i] = xMin + i * (xMax - xMin) / (numPoints - 1);
    y[i] = all_calculation(expression.toLocal8Bit().constData(),
                           QString::number(x[i]).toLocal8Bit().data());
  }

  for (int i = 0; i < numPoints; i++) {
    y[i] = std::atof(QString::number(y[i]).toLocal8Bit().data());
  }

  ui->customPlot->graph(0)->setData(x, y);
  ui->customPlot->yAxis->setRange(yMin, yMin + numPoints * yStep);
  ui->customPlot->replot();
}

void MainWindow::calculate_expression() {
  resize(450, 495);
  if (!check_parentheses(expression)) {
    QMessageBox::warning(this, tr("Error"),
                         tr("Invalid input: mismatched parentheses."));
    return;
  }

  // Проверка на недопустимые последовательности символов
  if (expression.contains("---") || expression.contains("+++") ||
      expression.contains("**") || expression.contains("/\\/") ||
      expression.contains("//") || expression.contains("xx")) {
    QMessageBox::warning(this, tr("Error"),
                         tr("Invalid input: invalid sequences."));
    return;
  }
  QString x_value_str = ui->x_value->text();

  bool is_valid_double = true;
  double x_value = x_value_str.toDouble(&is_valid_double);
  if (!x_value_str.isEmpty()) {
    if (!is_valid_double) {
      QMessageBox::warning(this, tr("Error"),
                           tr("Invalid input: x value is not a valid double."));
      return;
    }
  }

  double result = all_calculation(expression.toLocal8Bit().constData(),
                                  x_value_str.toLocal8Bit().data());

  if (std::isnan(result) || std::isinf(result)) {
    QMessageBox::warning(this, tr("Error"),
                         tr("Invalid input: result is not a number."));
    return;
  }

  ui->last_expr->setText(expression);
  ui->result_show->setText(QString::number(result, 'f', 6));
  expression =
      QString::number(result);  // update the expression with the result
}

void MainWindow::credit_clicked() { creditcalc.show(); }