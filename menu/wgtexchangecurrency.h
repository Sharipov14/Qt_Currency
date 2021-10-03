#ifndef WGTEXCHANGECURRENCY_H
#define WGTEXCHANGECURRENCY_H

#include <QWidget>
#include "tables/session.h"
#include "tables/operation.h"
#include "tables/contract.h"
#include "tables/users.h"
#include "tables/exchangerates.h"
#include "tables/balance.h"
#include "tables/currency.h"

namespace Ui {
class wgtExchangeCurrency;
}

class wgtExchangeCurrency : public QWidget
{
    Q_OBJECT
private:
    Users *user;
    Balance *balance;
    Session *session;
    Contract *contract;
    QList<Currency*> listCurrency;
    ExchangeRates *exchangeRates;
    Operation *operation;
    double ratio{1};

public:
    explicit wgtExchangeCurrency(QWidget *parent = nullptr);
    ~wgtExchangeCurrency();

    void setUser(Users*);
    void setBalance(Balance*);

private slots:
    void slotUpdateInfo();

    void slotConvert(const double);

    void on_pbtnBackToMenu_clicked();

    void on_comboBoxByeOrSelling_activated(int index);

    void on_comboBoxRates_activated(int index);

    void on_pbtnBye_clicked();

signals:
    void signalExit();

private:
    Ui::wgtExchangeCurrency *ui;
    void createSession(Session*);
    void selectContract(Contract*);
    bool selectCurrency();
    bool selecetExRates(ExchangeRates *exchageRates, const int idRate,  const QDate dateRate);
    bool insertOperation(Operation*);
    bool insetSession(Session*);
    bool updateBalance(Balance*);
};

#endif // WGTEXCHANGECURRENCY_H
