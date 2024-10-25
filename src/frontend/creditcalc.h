#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QMainWindow>


namespace Ui {
class CreditCalc;
}

class CreditCalc : public QMainWindow {
  Q_OBJECT

  public:
    explicit CreditCalc(QWidget *parent = nullptr);
    ~CreditCalc();

  protected:
  private slots:
    void eq_clicked();
    void ann_clicked();
    void diff_clicked();

  private:
    Ui::CreditCalc *ui;
};

#endif  // CREDITCALC_H
