#include "sqlrec.h"
#include <QHash>

SqlRec::SqlRec(QObject *parent) : QObject(parent)
{

}

void SqlRec::sqlErr(const QString& s) {
    QFile f(QString(SQL::path).arg(SQL::count));
    f.open(QIODevice::WriteOnly);
    f.write(s.toUtf8());
    f.close();
}

bool SqlRec::sqlErr(const QSqlQuery& q) {
    QSqlError e = q.lastError();
    QString s = q.lastQuery();
    sqlErr(QString("%1\r\n%2\r\n%3").arg(s).arg(e.text()).arg(e.driverText()));
    return false;
}

bool SqlRec::sqlExec(const QHash <QString,QVariant>& param, const QString& sql) {
    SQL::count++;
    QSqlQuery q;

    if(!q.prepare(sql))return sqlErr(q);

    for(const QString& s : param.keys())
        q.bindValue(s, param.value(s));

    if(!q.exec())return sqlErr(q);

    return true;
}
