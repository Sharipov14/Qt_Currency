#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QWidget>

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = nullptr);
    ~RegistrationForm();

private slots:
    void on_pbtnRegister_clicked();
    void on_pbtnCenselRegiser_clicked();

    void slotChanged();

signals:
    void signalCancelRegistration();

private:
    void connectChanged();
    bool isUser(const QString strQuery);
    bool checkAllLine();
    bool insertUser();
    bool insertIntoBalance(const int id);
    bool insertContract(const int id);
    void selectUsers(const QString);
    Ui::RegistrationForm *ui;
};

#endif // REGISTRATIONFORM_H
