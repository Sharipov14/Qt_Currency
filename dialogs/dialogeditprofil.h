#ifndef DIALOGEDITPROFIL_H
#define DIALOGEDITPROFIL_H

#include <QDialog>
#include "tables/users.h"

namespace Ui {
class DialogEditProfil;
}

class DialogEditProfil : public QDialog
{
    Q_OBJECT
private:
    Users *user;
    bool checkUserName;
    bool checkFirstName;
    bool checkLastName;
    bool checkSecondName;
    bool checkEmail;

public:
    explicit DialogEditProfil(QWidget *parent = nullptr);
    ~DialogEditProfil();

    void setUser(Users*);

private slots:
    void slotUpdateInfo();

    bool slotTextChanged();

    void on_checkBoxChangeUserName_clicked();

    void on_checkBoxChangeFirstName_clicked();

    void on_checkBoxChangeLastName_clicked();

    void on_checkBoxSecondName_clicked();

    void on_checkBoxChangeEmail_clicked();

    void on_checkBoxChangeDayOfBirth_clicked();

    void on_checkBoxChangePhoto_clicked();

    void on_pbtnLoadPhoto_clicked();

    void on_pbtnDeletePhoto_clicked();

    void on_pbtnOk_clicked();

private:
    Ui::DialogEditProfil *ui;
    void connectChanged();
};

#endif // DIALOGEDITPROFIL_H
