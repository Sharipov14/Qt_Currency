#ifndef DIALOGADDBALANCE_H
#define DIALOGADDBALANCE_H

#include <QDialog>

namespace Ui {
class DialogAddBalance;
}

class DialogAddBalance : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddBalance(QWidget *parent = nullptr);
    ~DialogAddBalance();

    double getMoneyRub() const;

private:
    Ui::DialogAddBalance *ui;
};

#endif // DIALOGADDBALANCE_H
