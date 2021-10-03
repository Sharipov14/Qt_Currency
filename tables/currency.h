#ifndef CURRENCY_H
#define CURRENCY_H

#include <QObject>
#include <QPixmap>

class Currency : public QObject
{
    Q_OBJECT
private:
    int idCurrency;
    QString currency;
    QPixmap flag;

public:
    explicit Currency(QObject *parent = nullptr){}

    void setIdCurrency(int idCurrency) { this->idCurrency = idCurrency; }
    void setCurrency(QString currency) { this->currency = currency; }
    void setFlag(QPixmap flag) { this->flag = flag; }

    int getIdCurrency() { return idCurrency; }
    QString getCurrency() { return currency; }
    QPixmap getFlag() { return flag; }

signals:

};

#endif // CURRENCY_H
