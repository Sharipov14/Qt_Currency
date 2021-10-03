#ifndef USERS_H
#define USERS_H

#include <QObject>
#include <QDate>
#include <QPixmap>

class Users : public QObject
{
    Q_OBJECT
private:
    int idUser;
    QString userName;
    QString password;
    QString firstName;
    QString lastName;
    QString secondName;
    QString sex;
    QDate dateOfBirth;
    QString email;
    QDateTime registrationDate;
    bool admin;
    QPixmap photo;

public:
    explicit Users(QObject *parent = nullptr){}
    ~Users(){}

    void setIdUser(int idUser) { this->idUser = idUser; }
    void setUserName(QString userName) { this->userName = userName; }
    void setPassword(QString password) { this->password = password; }
    void setFirstName(QString firstName) { this->firstName = firstName; }
    void setLastName(QString lastName) { this->lastName = lastName; }
    void setSecondName(QString secondName) { this->secondName = secondName; }
    void setSex(QString sex) { this->sex = sex; }
    void setDateOfBirth(QDate dateOfBirth) { this->dateOfBirth = dateOfBirth; }
    void setEmail(QString email) { this->email = email; }
    void setRegistrationDate(QDateTime registrationDate) { this->registrationDate = registrationDate; }
    void setAdmin(bool admin) {this->admin = admin; }
    void setPhoto(QPixmap photo) { this->photo = photo; }

    int getIdUser() { return idUser;; }
    QString getUserName() { return userName; }
    QString getPassword() { return password; }
    QString getFirstName() { return firstName; }
    QString getLastName() { return lastName; }
    QString getSecondName() { return secondName; }
    QString getSex() { return sex; }
    QDate getDateOfBirth() { return dateOfBirth; }
    QString getEmail() { return email; }
    QDateTime getRegistrationDate() { return registrationDate; }
    bool getAdmin() { return admin; }
    QPixmap getPhoto() { return photo; }

signals:

};

#endif // USERS_H
