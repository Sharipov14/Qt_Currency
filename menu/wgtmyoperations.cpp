#include "wgtmyoperations.h"
#include "ui_wgtmyoperations.h"

#include <QTimer>
#include <QPrinter>
#include <QTextDocument>
#include <QMessageBox>
#include "Database/sqlrec.h"

WgtMyOperations::WgtMyOperations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WgtMyOperations)
{
    ui->setupUi(this);
    setWindowTitle("Мои операции");

    QTimer::singleShot(20, this, SLOT(slotUpdateInfo()));

}

void WgtMyOperations::setUser(Users *user)
{
    this->user = user;
}

void WgtMyOperations::setBalance(Balance *balance)
{
    this->balance = balance;
}

WgtMyOperations::~WgtMyOperations()
{
    delete ui;
    listMyOperation.clear();
}

void WgtMyOperations::slotUpdateInfo()
{
    ui->plblMoneyRub->setText(QString("%1 ₽").arg(QString::number(balance->getMoneyRub(), 'f', 2)));
    ui->plblMoneyDol->setText(QString("%1 $").arg(QString::number(balance->getMoneyDollars(), 'f', 2)));
    ui->plblMoneyEur->setText(QString("%1 €").arg(QString::number(balance->getMoneyEuro(), 'f', 2)));

    selectMyOperation();
    createTable();
}

bool WgtMyOperations::selectMyOperation()
{
    QSqlQuery query;
    query.prepare(SQL_REC::selectMyOperaton);

    query.bindValue(":id", user->getIdUser());

    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return false;
    }

    while (query.next())
    {
        MyOperation *myOperation = new MyOperation(this);

        myOperation->setDate(query.value(query.record().indexOf("ДатаОпер")).toDateTime());
        myOperation->setTypeOperation(query.value(query.record().indexOf("ВидОпер")).toString());
        myOperation->setCurrency(query.value(query.record().indexOf("Валюта")).toString());
        QPixmap flagCurrency;
        flagCurrency.loadFromData(query.value(query.record().indexOf("Флаг")).toByteArray());
        myOperation->setFlagCurrency(flagCurrency);
        myOperation->setIdCurrency(query.value(query.record().indexOf("КодВалют")).toUInt());
        myOperation->setMoneyIn(query.value(query.record().indexOf("СуммаВалют")).toDouble());
        myOperation->setFioSot(query.value(query.record().indexOf("Сотрудник")).toString());

        listMyOperation.append(myOperation);
    }

    return true;
}

void WgtMyOperations::createTable()
{
    QString html = ui->label->text();

    for (int i = 0; i < listMyOperation.size(); ++i)
    {

        html += QString("<tr>"
                    "<td>%1</td>"
                    "<td>%2</td>"
                    "<td>%3</td>"
                    "<td>%4</td>"
                    "<td>%5</td>"
                    "<td>%6</td>"
                    "<td>%7</td>"
                    "<td>%8</td>"
                    "<td>%10</td>"
                "</tr>").arg(listMyOperation[i]->getDate().date().toString(Qt::ISODateWithMs))
                        .arg(listMyOperation[i]->getDate().time().toString(Qt::ISODate))
                        .arg(listMyOperation[i]->getTypeOperation())
                        .arg(listMyOperation[i]->getCurrency())
                        .arg("Флаг")
                        .arg(listMyOperation[i]->getMoneyIn())
                        .arg("курс")
                        .arg(listMyOperation[i]->getICurrency())
                        .arg(listMyOperation[i]->getFioSot());
    }

    html += "</table></body</html>";
    ui->label->setText(html);
}

void WgtMyOperations::createPdf(const QString html)
{
    QTextDocument *document = new QTextDocument();
    document->setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    //printer.setPaperSize(QPrinter::A4);
    printer.setPageMargins(QMarginsF(5, 5, 5, 5));
    printer.setOutputFileName(QApplication::applicationDirPath() + "\\PDF\\My operations.pdf");

    //document->setPageSize(printer.pageRect().size());
    document->print(&printer);
}

void WgtMyOperations::on_pbtnBackToMenu_clicked()
{
    emit signalExit();
}

void WgtMyOperations::on_pbtnSavePdf_clicked()
{
    createPdf(ui->label->text());
    QString message = "Таблица сохоранена в формате pdf";
    QMessageBox::information(this, "Information", message);
}
