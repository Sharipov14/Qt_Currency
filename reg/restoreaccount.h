#ifndef RESTOREACCOUNT_H
#define RESTOREACCOUNT_H

#include <QWidget>

namespace Ui {
class RestoreAccount;
}

class RestoreAccount : public QWidget
{
    Q_OBJECT

public:
    explicit RestoreAccount(QWidget *parent = nullptr);
    ~RestoreAccount();

private slots:
    void on_pbtnNext_clicked();

    void on_pbtnNext_2_clicked();

    void on_pbtnBack_clicked();

    void on_pbtnRestore_clicked();

    void on_pbtnCancel_clicked();

    void on_pbtnCancel_2_clicked();

    void on_checkBoxViewPssword_clicked();

signals:
    void signalCancelRestorePassowrd();

private:
    Ui::RestoreAccount *ui;

    QString email = NULL;
    QString kod;
};

#endif // RESTOREACCOUNT_H
