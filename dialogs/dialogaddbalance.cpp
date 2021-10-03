#include "dialogaddbalance.h"
#include "ui_dialogaddbalance.h"

DialogAddBalance::DialogAddBalance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddBalance)
{
    ui->setupUi(this);
    setWindowTitle("Пополнение баланса");
}

double DialogAddBalance::getMoneyRub() const
{
    return ui->doubleSpinBoxAddMonay->value();
}

DialogAddBalance::~DialogAddBalance()
{
    delete ui;
}
