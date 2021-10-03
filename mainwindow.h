#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "reg/loginform.h"
#include "reg/registrationform.h"
#include "reg/restoreaccount.h"
#include "menu/mainmenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    LoginForm *loginForm;
    RegistrationForm *registrationForm;
    RestoreAccount *restoreAccount;
    MainMenu *mainMenu;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void runMenuForm(QString, QString);
    void runLoginForm();
    void runRegistrationForm();
    void runRestoreAccount();
    void slotUpdateTitle(const QString);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
