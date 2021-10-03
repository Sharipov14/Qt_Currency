#ifndef SQLREC_H
#define SQLREC_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QFile>
#include <Database/SQL.h>

class SqlRec : public QObject
{
    Q_OBJECT
public:
    explicit SqlRec(QObject *parent = nullptr);

    static void sqlErr(const QString& s);
    static bool sqlErr(const QSqlQuery& q);
    static bool sqlExec(const QHash <QString,QVariant>& param, const QString& sql);

signals:

};

#endif // SQLREC_H
