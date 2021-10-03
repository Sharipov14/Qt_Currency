#include "loginform.h"
#include "ui_loginform.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>
#include <QDir>

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    setWindowTitle("Добро пожаловать");

    creatConnection(db);

    connect(ui->lineEditLogin, &QLineEdit::textChanged, this, &LoginForm::slotTextChanged);
    connect(ui->lineEditPassword, &QLineEdit::textChanged, this, &LoginForm::slotTextChanged);

    connect(ui->pbtnRegistration, SIGNAL(clicked()), parent, SLOT(runRegistrationForm()));
    connect(ui->pbtnNewPassword, SIGNAL(clicked()), parent, SLOT(runRestoreAccount()));
}

bool LoginForm::creatConnection(QSqlDatabase& db)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName(QApplication::applicationDirPath() + "\\Database\\Currency.db");

    if (!db.open()) {
        qDebug() << "Ошибка подключения БД: " << db.lastError();
        return false;
    }

    return true;
}

void LoginForm::on_pbtnLogIntoAccount_clicked()
{
    const QString login = ui->lineEditLogin->text();
    const QString password = ui->lineEditPassword->text();

    QString strQuery = "SELECT user_name, password FROM Users "
                           "WHERE user_name = '" + login + "';";
    QSqlQuery query;

    if (query.exec(strQuery))
    {
        QSqlRecord recrod = query.record();

        QString userNameFromDb;
        QString passwordFromDb;

        while (query.next())
        {
            userNameFromDb = query.value(recrod.indexOf("user_name")).toString();
            passwordFromDb = query.value(recrod.indexOf("password")).toString();
        }

        if (login == userNameFromDb)
        {
            if (password == passwordFromDb)
            {
                emit signalLogIn(userNameFromDb, passwordFromDb);
            }
            else
            {
                QString message = "Неверный пароль!";
                QMessageBox::information(0, "Information", message);
            }
        }
        else
        {
            QString message = "Пользователь не найден!";
            QMessageBox::information(0, "Information", message);
        }
    }
    else qDebug() << query.lastError().text();
}

void LoginForm::on_checkBoxViewPassword_clicked()
{
    if (ui->checkBoxViewPassword->isChecked())
        ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
    else
        ui->lineEditPassword->setEchoMode(QLineEdit::Password);
}

void LoginForm::slotTextChanged()
{
    ui->pbtnLogIntoAccount->setEnabled(!ui->lineEditLogin->text().isEmpty() && !ui->lineEditPassword->text().isEmpty());
}

LoginForm::~LoginForm()
{

    delete ui;
}
