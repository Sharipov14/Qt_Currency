#ifndef OPERATION_H
#define OPERATION_H

#include <QObject>
#include <QDate>

class Operation : public QObject
{
    Q_OBJECT
private:
    int idOperation;
    QString typeOfOperation;
    QDateTime dateOperation;
    int contractNumber;
    int idCurrency;
    double money;

public:
    explicit Operation(QObject *parent = nullptr){}

    void setIdOperation(int idOperation) { this->idOperation = idOperation; }
    void setTypeOfOperation(QString typeOfOperation) { this->typeOfOperation = typeOfOperation; }
    void setDateOperation(QDateTime dateOperation) { this->dateOperation = dateOperation; }
    void setContractNumber(int contractNumber) { this->contractNumber = contractNumber; }
    void setIdCurrency(int idCurrency) { this->idCurrency = idCurrency; }
    void setMoney(double money) { this->money = money; }

    int getIdOperation() { return idOperation; }
    QString getTypeOfOperation() { return typeOfOperation; }
    QDateTime getDateOperation() { return dateOperation; }
    int getContractNumber() { return contractNumber; }
    int getIdCurrency() { return idCurrency; }
    double getMoney() { return money; }


signals:

};

#endif // OPERATION_H
