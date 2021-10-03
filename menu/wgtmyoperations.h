#ifndef WGTMYOPERATIONS_H
#define WGTMYOPERATIONS_H

#include <QWidget>
#include "tables/session.h"
#include "tables/operation.h"
#include "tables/users.h"
#include "tables/exchangerates.h"
#include "tables/balance.h"
#include "tables/currency.h"
#include "tables/contract.h"
#include "tables/myoperation.h"
#include "Database/sqlrec.h"

namespace Ui {
class WgtMyOperations;
}

class WgtMyOperations : public QWidget
{
    Q_OBJECT
private:
    Users *user;
    Balance *balance;
    QList<MyOperation*> listMyOperation;

public:
    explicit WgtMyOperations(QWidget *parent = nullptr);
    ~WgtMyOperations();

    void setUser(Users*);
    void setBalance(Balance*);

private slots:
    void slotUpdateInfo();

    void on_pbtnBackToMenu_clicked();

    void on_pbtnSavePdf_clicked();

signals:
    void signalExit();

private:
    Ui::WgtMyOperations *ui;
    bool selectMyOperation();
    void createTable();
    void createPdf(const QString html);
};

#endif // WGTMYOPERATIONS_H
