#include "wgtprofil.h"
#include "ui_wgtprofil.h"

#include <QTimer>
#include <QSqlQuery>
#include <QSqlError>
#include <QByteArray>
#include <QBuffer>
#include <Database/sqlrec.h>
#include "dialogs/dialogaddbalance.h"
#include "dialogs/dialogeditpassword.h"
#include "dialogs/dialogeditprofil.h"

WgtProfil::WgtProfil(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WgtProfil)
{
    ui->setupUi(this);
    setWindowTitle("Профиль");

    QTimer::singleShot(20, this, SLOT(slotUpdateInfo()));
}

void WgtProfil::slotUpdateInfo()
{
    ui->plblShowUserName->setText(user->getUserName());
    QString fullName = user->getLastName() + " " + user->getFirstName() + " " + user->getSecondName();
    ui->plblShowFullName->setText(fullName);
    ui->plblShowEmail->setText(user->getEmail());
    ui->plblShowSex->setText(user->getSex());
    ui->plblShowDayOfBirth->setText(user->getDateOfBirth().toString(Qt::ISODateWithMs));

    if(!user->getPhoto().isNull())
        ui->plblShowPhoto->setPixmap(user->getPhoto().scaled(260, 260));
    else {
        QPixmap pix;
        if (user->getSex() == "Female") {
            pix.load(":/icons2/icons8-woman100.png");
            ui->plblShowPhoto->setPixmap(pix.scaled(260, 260));
        }
        else if (user->getSex() == "Male") {
            pix.load(":/icons2/icons8-man-100.png");
            ui->plblShowPhoto->setPixmap(pix.scaled(260, 260));
        }
    }

    ui->plblMoneyRub->setText(QString("%1 ₽").arg(QString::number(balance->getMoneyRub(), 'f', 2)));
    ui->plblMoneyDol->setText(QString("%1 $").arg(QString::number(balance->getMoneyDollars(), 'f', 2)));
    ui->plblMoneyEur->setText(QString("%1 €").arg(QString::number(balance->getMoneyEuro(), 'f', 2)));
}

WgtProfil::~WgtProfil()
{
    delete ui;
}

void WgtProfil::setBalance(Balance *balance)
{
    this->balance = balance;
}

void WgtProfil::setUser(Users *user)
{
    this->user = user;
}

bool WgtProfil::updateTableBalance(Balance *balance)
{
    if (!SqlRec::sqlExec({{":rub", balance->getMoneyRub()},
                          {":dollar", balance->getMoneyDollars()},
                          {":euro", balance->getMoneyEuro()},
                          {":idUser", user->getIdUser()}}, SQL_REC::updateBalance))
        return false;

    return true;

}

bool WgtProfil::updateTableUser(Users *user)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    user->getPhoto().save(&buffer, "PNG");

    if (!SqlRec::sqlExec({{":user_name", user->getUserName()},
                          {":password", user->getPassword()},
                          {":first_name", user->getFirstName()},
                          {":last_name", user->getLastName()},
                          {":second_name", user->getSecondName()},
                          {":date_of_birth", user->getDateOfBirth()},
                          {":email", user->getEmail()},
                          {":photo", byteArray},
                          {":id", user->getIdUser()}}, SQL_REC::updateUsers))
        return false;

    return true;
}

void WgtProfil::on_pbtTopUpBalance_clicked()
{
    DialogAddBalance *dialog = new DialogAddBalance(this);

    if (dialog->exec() == QDialog::Accepted)
    {
        balance->setMoneyRub(balance->getMoneyRub() + dialog->getMoneyRub());

        if (!updateTableBalance(balance))
            qDebug() << "Ошибка. Баланс не пополнен";

        slotUpdateInfo();
    }

    delete dialog;
}

void WgtProfil::on_pbtnChangePassword_clicked()
{
    DialogEditPassword *dialog = new DialogEditPassword(this);
    dialog->setPassword(user->getPassword());

    if (dialog->exec() == QDialog::Accepted)
    {
        user->setPassword(dialog->getNewPassword());

        if (!updateTableUser(user))
            qDebug() << "Ошибка. Пароль не обнавлен";
    }

    delete dialog;
}

void WgtProfil::on_pbtnBackToMenu_clicked()
{
    emit signalExit();
}

void WgtProfil::on_pbtnChangeUser_clicked()
{
    DialogEditProfil *dialog = new DialogEditProfil(this);
    dialog->setUser(user);

    if (dialog->exec() == QDialog::Accepted)
    {
        slotUpdateInfo();
        if (!updateTableUser(user))
            qDebug() << "Ошибка обновления данных пользователя";
    }

    delete dialog;
}
