#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QDate>

class Session : public QObject
{
    Q_OBJECT
private:
    QDateTime date;
    int idEmployee;

public:
    explicit Session(QObject *parent = nullptr) {}

    void setDate(QDateTime date) { this->date = date; }
    void setIdEmployee(int idEmployee) { this->idEmployee = idEmployee; }

    QDateTime getDate() { return date; }
    int getIdEmployee() { return idEmployee; }

signals:

};

#endif // SESSION_H
