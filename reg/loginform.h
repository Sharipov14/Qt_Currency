#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT
private:
    QSqlDatabase db;
    bool creatConnection(QSqlDatabase& db);

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private slots:
    void on_pbtnLogIntoAccount_clicked();
    void on_checkBoxViewPassword_clicked();
    void slotTextChanged();

signals:
    void signalLogIn(const QString, const QString);

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
