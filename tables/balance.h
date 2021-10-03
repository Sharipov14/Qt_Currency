#ifndef BALANCE_H
#define BALANCE_H

#include <QObject>

class Balance : public QObject
{
    Q_OBJECT
private:
    int idUser;
    double moneyRub;
    double moneyDollars;
    double moneyEuro;

public:
    explicit Balance(QObject *parent = nullptr){}

    void setIdUser(int idUser) { this->idUser = idUser; }
    void setMoneyRub(double moneyRub) { this->moneyRub = moneyRub; }
    void setMoneyDollars(double moneyDollars) { this->moneyDollars = moneyDollars; }
    void setMoneyEuro(double moneyEuro) { this->moneyEuro = moneyEuro; }

    int getIdUser() { return idUser; }
    double getMoneyRub() { return moneyRub; }
    double getMoneyDollars() { return moneyDollars; }
    double getMoneyEuro() { return moneyEuro; }

signals:

};

#endif // BALANCE_H
