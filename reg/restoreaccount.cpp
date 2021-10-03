#include "restoreaccount.h"
#include "ui_restoreaccount.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>

RestoreAccount::RestoreAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RestoreAccount)
{
    ui->setupUi(this);
    setWindowTitle("Востановление аккаунта");
    ui->stackedWidget->setCurrentWidget(ui->wgtStepOne);
}

RestoreAccount::~RestoreAccount()
{
    delete ui;
}

void RestoreAccount::on_pbtnNext_clicked()
{
    if (!ui->lineEditEmail->text().isEmpty())
    {
        QString strQuery = "SELECT email FROM Users WHERE email = '" + ui->lineEditEmail->text() +"';";
        QSqlQuery query;

        if(!query.exec(strQuery))
            qDebug() << query.lastError();

        while (query.next())
            email = query.value(query.record().indexOf("email")).toString();

        if (email == ui->lineEditEmail->text())
        {

            kod = "1234";

            QString messagee = "На вашу почту отправлен код подтверждения";
            QMessageBox::information(this, "Information", messagee);

            ui->stackedWidget->setCurrentWidget(ui->wgtStepTwo);
        }
        else
        {
            QString message = "Учетная запись не найдена";
            QMessageBox::information(this, "Information", message);
            ui->lineEditEmail->setText(NULL);
        }
    }
    else
    {
        QString message = "Введите электронную почту";
        QMessageBox::information(this, "Information", message);
    }

}

void RestoreAccount::on_pbtnNext_2_clicked()
{
    if (!ui->lineEditKod->text().isEmpty())
    {
        if (kod == ui->lineEditKod->text())
        {
            ui->stackedWidget->setCurrentWidget(ui->wgtStepThree);
            delete ui->wgtStepOne;
            delete ui->wgtStepTwo;
        }
        else
        {
            QString message = "Неверный код";
            QMessageBox::information(this, "Information", message);
            ui->lineEditEmail->setText(NULL);
        }
    }
    else
    {
        QString message = "Введите код";
        QMessageBox::information(this, "Information", message);
    }
}

void RestoreAccount::on_pbtnBack_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->wgtStepOne);
}

void RestoreAccount::on_pbtnRestore_clicked()
{
    if (!ui->lineEditPassword->text().isEmpty() && !ui->lineEditConfirmPassword->text().isEmpty())
    {
        if (ui->lineEditPassword->text() == ui->lineEditConfirmPassword->text())
        {
            QString strQuery = "UPDATE Users "
                                    "SET password = '" + ui->lineEditPassword->text() + "' "
                                "WHERE email = '" + email + "';";
            QSqlQuery query;

            if (!query.exec(strQuery))
                qDebug() << query.lastError().text();
            else
            {
                QString message = "Ваш пароль, успешно изменен";
                QMessageBox::information(this, "Information", message);
                on_pbtnCancel_clicked();
            }
        }
        else
        {
            QString message = "Пароли не совпадают";
            QMessageBox::information(this, "Information", message);
        }
    }
    else
    {
        QString message = "Заполните все поля";
        QMessageBox::information(this, "Information", message);
    }
}

void RestoreAccount::on_pbtnCancel_clicked()
{
    emit signalCancelRestorePassowrd();
    delete this;
}

void RestoreAccount::on_pbtnCancel_2_clicked()
{
    on_pbtnCancel_clicked();
}

void RestoreAccount::on_checkBoxViewPssword_clicked()
{
    if (ui->checkBoxViewPssword->isChecked())
    {
        ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
        ui->lineEditConfirmPassword->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->lineEditPassword->setEchoMode(QLineEdit::Password);
        ui->lineEditConfirmPassword->setEchoMode(QLineEdit::Password);
    }
}
