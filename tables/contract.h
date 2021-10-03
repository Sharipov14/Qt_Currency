#ifndef CONTRACT_H
#define CONTRACT_H

#include <QObject>
#include <QDate>

class Contract : public QObject
{
    Q_OBJECT
private:
    int contractNumber;
    QDate date;
    int idUsers;

public:
    explicit Contract(QObject *parent = nullptr){}

    void setContractNumber(int contractNumber) { this->contractNumber = contractNumber; }
    void setDate(QDate date) { this->date = date; }
    void setIdUsers(int idUsers) { this->idUsers = idUsers; }

    int getContractNumber() { return contractNumber; }
    QDate getDate() { return date; }
    int getIdUsers() { return idUsers; }

signals:

};

#endif // CONTRACT_H
