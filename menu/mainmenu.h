#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "wgtedittable.h"
#include "wgtexchangecurrency.h"
#include "wgtprofil.h"
#include "wgtgraphic.h"
#include "wgtmyoperations.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT
private:
    WgtEditTable *wgtEditTable;
    wgtExchangeCurrency *wgtExCurrency;
    WgtProfil *wgtProfil;
    WgtGraphic *wgtGraphic;
    WgtMyOperations *wgtMyOperations;
    Users *user;
    Balance *balance;


public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

    void setUser(const QString, const QString);

private slots:
    void slotUpdateInfo();

    void on_pbtnLogOut_clicked();

    void on_commandLinkButton_clicked();
    void slotExitWgtProfil();

    void on_pbtnRunWgtEditTable_clicked();

    void on_pbtnRunExchangeRate_clicked();
    void slotExitWgtExCerrncy();

    void on_pbtnRunWgtGraphic_clicked();
    void slotExitWgtGraphic();

    void on_pbtnRunWgtMyOperation_clicked();
    void slotExitWgtMyOpertion();

signals:
    void signalLoginOut();
    void signalUpdateTitle(const QString);

private:
    Ui::MainMenu *ui;
    bool getBalace(Balance *balance, Users* user);
};

#endif // MAINMENU_H
