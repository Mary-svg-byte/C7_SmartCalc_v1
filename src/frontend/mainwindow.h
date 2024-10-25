#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "creditcalc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString expression;
    CreditCalc creditcalc;

private slots:
    void digits_numbers();
    void dot_clicked();
    void clear_one_clicked();
    void clear_all_clicked();
    void symb_clicked();
    void func_clicked();
    void calculate_expression();
    bool check_parentheses(const QString& expression);
    void mod_clicked ();
    void show_Graph ();
    void credit_clicked ();
};

#endif // MAINWINDOW_H
