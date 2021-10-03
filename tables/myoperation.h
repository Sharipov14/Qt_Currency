#ifndef MYOPERATION_H
#define MYOPERATION_H

#include <QObject>
#include <QDateTime>
#include <QPixmap>

class MyOperation : public QObject
{
    Q_OBJECT
private:
    QDateTime date;
    QString typeOperation;
    QString currency;
    QPixmap flagCurrency;
    int idCurrency;
    double moneyIn;
    double moneyOut;
    QString fioSot;

public:
    explicit MyOperation(QObject *parent = nullptr) {}

    void setDate(QDateTime date) { this->date = date; }
    void setTypeOperation(QString typeOperation) { this->typeOperation = typeOperation; }
    void setCurrency (QString currency) { this->currency = currency; }
    void setFlagCurrency (QPixmap flagCurrency) { this->flagCurrency = flagCurrency; }
    void setIdCurrency (int idCurrency) { this->idCurrency = idCurrency; }
    void setMoneyIn (double moneyIn) { this->moneyIn = moneyIn; }
    void setMoneyOut (double moneyOut) { this->moneyOut = moneyOut; }
    void setFioSot (QString fioSot) { this->fioSot = fioSot; }

    QDateTime getDate() { return date; }
    QString getTypeOperation() { return typeOperation; }
    QString getCurrency () { return currency; }
    QPixmap getFlagCurrency () { return flagCurrency; }
    int getICurrency () { return idCurrency; }
    double getMoneyIn () { return moneyIn; }
    double getMoneyOut () { return moneyOut; }
    QString getFioSot () { return fioSot; }

signals:

};

#endif // MYOPERATION_H
