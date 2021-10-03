#ifndef DIALOGEDITPASSWORD_H
#define DIALOGEDITPASSWORD_H

#include <QDialog>

namespace Ui {
class DialogEditPassword;
}

class DialogEditPassword : public QDialog
{
    Q_OBJECT
    QString oldPassword;

public:
    explicit DialogEditPassword(QWidget *parent = nullptr);
    ~DialogEditPassword();

    void setPassword(QString oldPassword);
    QString getNewPassword() const;

private slots:
    void on_checkBoxShowPassword_clicked();

    void slotTextChangedPasswords();

    void on_pbtnOk_clicked();


private:
    Ui::DialogEditPassword *ui;
    bool checkLineEdit();
};

#endif // DIALOGEDITPASSWORD_H
