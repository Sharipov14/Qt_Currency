#ifndef EXCHANGERATES_H
#define EXCHANGERATES_H

#include <QObject>
#include <QDate>

class ExchangeRates : public QObject
{
    Q_OBJECT
private:
    QDate date;
    int idCurrency;
    double rateCB;
    double sellingRate;
    double purchaseRate;

public:
    explicit ExchangeRates(QObject *parent = nullptr){}

    void setDate(QDate date) { this->date = date; }
    void setIdCurrency(int idCurrency) { this->idCurrency = idCurrency; }
    void setRateCB(double rateCB) { this->rateCB = rateCB; }
    void setSellingRate(double sellingRate) { this->sellingRate = sellingRate; }
    void setPurchaseRate(double purchaseRate) { this->purchaseRate = purchaseRate; }

    QDate getDate() { return date; }
    int getIdCurrency() { return idCurrency; }
    double getRateCB() { return rateCB; }
    double getSellingRate() { return sellingRate; }
    double getPurchaseRate() { return purchaseRate; }

signals:

};

#endif // EXCHANGERATES_H
