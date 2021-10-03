#ifndef WGTPROFIL_H
#define WGTPROFIL_H

#include <QWidget>
#include "tables/balance.h"
#include "tables/users.h"

namespace Ui {
class WgtProfil;
}

class WgtProfil : public QWidget
{
    Q_OBJECT
private:
    Balance *balance;
    Users *user;

public:
    explicit WgtProfil(QWidget *parent = nullptr);
    ~WgtProfil();

    void setBalance(Balance*);
    void setUser(Users*);

private slots:
    void on_pbtTopUpBalance_clicked();

    void on_pbtnChangePassword_clicked();

    void slotUpdateInfo();

    void on_pbtnBackToMenu_clicked();

    void on_pbtnChangeUser_clicked();

signals:
    void signalExit();

private:
    Ui::WgtProfil *ui;
    bool updateTableBalance(Balance*);
    bool updateTableUser(Users*);
};

#endif // WGTPROFIL_H
