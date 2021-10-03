#include "registrationform.h"
#include "ui_registrationform.h"

#include <QMessageBox>
#include <Database/sqlrec.h>

RegistrationForm::RegistrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
    setWindowTitle("Регистрация");

    ui->dateEditBirthDay->setDate(QDate::currentDate());

    connectChanged();
}

void RegistrationForm::connectChanged()
{
    connect(ui->lineEditUserName, &QLineEdit::textChanged, this, &RegistrationForm::slotChanged);
    connect(ui->lineEditFirsName, &QLineEdit::textChanged, this, &RegistrationForm::slotChanged);
    connect(ui->lineEditLastName, &QLineEdit::textChanged, this, &RegistrationForm::slotChanged);
    connect(ui->lineEditSecondName, &QLineEdit::textChanged, this, &RegistrationForm::slotChanged);
    connect(ui->lineEditEmail, &QLineEdit::textChanged, this, &RegistrationForm::slotChanged);
    connect(ui->lineEditPassword, &QLineEdit::textChanged, this, &RegistrationForm::slotChanged);
    connect(ui->lineEditConfitmPassword, &QLineEdit::textChanged, this, &RegistrationForm::slotChanged);
    connect(ui->radioButtonMale, &QRadioButton::clicked, this, &RegistrationForm::slotChanged);
    connect(ui->radioButtonFemale, &QRadioButton::clicked, this, &RegistrationForm::slotChanged);
}

bool RegistrationForm::checkAllLine()
{
    return !ui->lineEditUserName->text().isEmpty() && !ui->lineEditFirsName->text().isEmpty() &&
           !ui->lineEditLastName->text().isEmpty() && !ui->lineEditEmail->text().isEmpty() &&
           !ui->lineEditPassword->text().isEmpty() && !ui->lineEditConfitmPassword->text().isEmpty() &&
           !ui->lineEditSecondName->text().isEmpty() &&
           (ui->radioButtonMale->isChecked() || ui->radioButtonFemale->isChecked());
}

bool RegistrationForm::insertUser()
{
    QString sex;
    if (ui->radioButtonMale->isChecked())
        sex = "Male";
    else if (ui->radioButtonFemale->isChecked())
        sex = "Female";

    if (!SqlRec::sqlExec({{":user_name", ui->lineEditUserName->text()},
                          {":password", ui->lineEditPassword->text()},
                          {":first_name", ui->lineEditFirsName->text()},
                          {":last_name", ui->lineEditLastName->text()},
                          {":second_name", ui->lineEditSecondName->text()},
                          {":sex", sex},
                          {":date_of_birth", ui->dateEditBirthDay->date()},
                          {":email", ui->lineEditEmail->text()},
                          {":registration_date", QDateTime::currentDateTime()}}, SQL_REC::insertUsers))
        return false;

    return true;
}

bool RegistrationForm::insertIntoBalance(const int id)
{
    QString strQuery = QString("INSERT INTO Баланс (id_клиента) "
                                    "VALUES (%1);").arg(id);
    QSqlQuery query;

    if (!query.exec(strQuery)) {
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool RegistrationForm::insertContract(const int id)
{
    QString strQuery = "INSERT INTO Договоры (ДатаДог, КодКлиент) "
                                    "VALUES (:date, :idUser);";
    QSqlQuery query;
    query.prepare(strQuery);

    query.bindValue(":date", QDate::currentDate());
    query.bindValue(":idUser", id);

    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

void RegistrationForm::selectUsers(const QString user_name)
{
    QString strQuery = "SELECT id FROM Users WHERE user_name = '" + user_name + "';";
    QSqlQuery query;

    if (!query.exec(strQuery)) {
        qDebug() << query.lastError().text();
        return;
    }

    int id = -1;
    while (query.next())
       id = query.value(query.record().indexOf("id")).toInt();

    if (!insertIntoBalance(id))
        qDebug() << "Ошибка добавлении записи о балансе";

    if (!insertContract(id))
        qDebug() << "Ошибка добавления договора";
}

void RegistrationForm::on_pbtnRegister_clicked()
{
    if (checkAllLine())
    {
        if (ui->lineEditPassword->text() == ui->lineEditConfitmPassword->text())
        {
            QString strQuery = "SELECT user_name FROM Users WHERE user_name = '" + ui->lineEditUserName->text() + "';";
            if (!isUser(strQuery))
            {
                strQuery = "SELECT email FROM Users WHERE email = '" + ui->lineEditEmail->text() + "';";
                if (!isUser(strQuery))
                {
                    if (insertUser())
                    {
                        selectUsers(ui->lineEditUserName->text());
                        QString message = "Вы успешно зарегистрировались!";
                        QMessageBox::information(this, "Information", message);
                        on_pbtnCenselRegiser_clicked();
                    }
                    else
                    {
                        QString message = "Зарегистрирование не прошло";
                        QMessageBox::information(this, "Information", message);
                    }
                }
                else
                {
                    QString message = "Пользователь с елктронной почтой: " + ui->lineEditEmail->text() + ", уже существует.";
                    message += "\nВведите другую почту";
                    QMessageBox::information(this, "Information", message);
                }
            }
            else
            {
                QString message = "Пользователь с ником: " + ui->lineEditUserName->text() + ", уже существует.";
                message += "\nВыберите другой ник";
                QMessageBox::information(this, "Information", message);
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
        QString message = "Не все поля заполнены";
        QMessageBox::information(this, "Information", message);
    }
}

void RegistrationForm::on_pbtnCenselRegiser_clicked()
{
    emit signalCancelRegistration();
    delete this;
}

void RegistrationForm::slotChanged()
{
    ui->pbtnRegister->setEnabled(checkAllLine());
}

bool RegistrationForm::isUser(const QString strQuery)
{
    QSqlQuery query;

    if (!query.exec(strQuery))
        qDebug() << query.lastError().text();

    if (!query.next())
        return false;

    return true;
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}
