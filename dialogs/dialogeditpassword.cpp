#include "dialogeditpassword.h"
#include "ui_dialogeditpassword.h"

#include <QMessageBox>

DialogEditPassword::DialogEditPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditPassword)
{
    ui->setupUi(this);
    setWindowTitle("Изменить пароль");

    connect(ui->lineEditOldPassword, &QLineEdit::textChanged, this, &DialogEditPassword::slotTextChangedPasswords);
    connect(ui->lineEditNewPassword, &QLineEdit::textChanged, this, &DialogEditPassword::slotTextChangedPasswords);
    connect(ui->lineEditConfirmPassword, &QLineEdit::textChanged, this, &DialogEditPassword::slotTextChangedPasswords);
}

DialogEditPassword::~DialogEditPassword()
{
    delete ui;
}

void DialogEditPassword::setPassword(QString oldPassword)
{
    this->oldPassword = oldPassword;
}

QString DialogEditPassword::getNewPassword() const
{
    return ui->lineEditNewPassword->text();
}

void DialogEditPassword::on_checkBoxShowPassword_clicked()
{
    if (ui->checkBoxShowPassword->isChecked())
    {
        ui->lineEditNewPassword->setEchoMode(QLineEdit::Normal);
        ui->lineEditOldPassword->setEchoMode(QLineEdit::Normal);
        ui->lineEditConfirmPassword->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->lineEditNewPassword->setEchoMode(QLineEdit::Password);
        ui->lineEditOldPassword->setEchoMode(QLineEdit::Password);
        ui->lineEditConfirmPassword->setEchoMode(QLineEdit::Password);
    }
}

void DialogEditPassword::slotTextChangedPasswords()
{
    const bool checkOldPassword = !ui->lineEditOldPassword->text().isEmpty();
    const bool checkNewPassword = !ui->lineEditNewPassword->text().isEmpty();
    const bool checkConfirmPassword = !ui->lineEditConfirmPassword->text().isEmpty();

    ui->pbtnOk->setEnabled(checkOldPassword && checkNewPassword && checkConfirmPassword);
}

void DialogEditPassword::on_pbtnOk_clicked()
{
    if (ui->lineEditOldPassword->text() == oldPassword)
    {
        if (ui->lineEditNewPassword->text() == ui->lineEditConfirmPassword->text())
        {
            this->accept();
        }
        else
        {
            QString message = "Пароли не совпадают";
            QMessageBox::information(this, "Information", message);
        }
    }
    else
    {
        QString message = "Вы ввели неверный паролль";
        QMessageBox::information(this, "Information", message);
    }
}
