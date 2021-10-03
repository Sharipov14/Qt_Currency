#include "wgtgraphic.h"
#include "ui_wgtgraphic.h"

#include <QTimer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDate>
#include <QChart>
#include <QDateTimeAxis>
#include <QValueAxis>

WgtGraphic::WgtGraphic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WgtGraphic)
{
    ui->setupUi(this);
    setWindowTitle("График изменение курса валют");

    QTimer::singleShot(20, this, SLOT(slotUpdateInfo()));

    chartView = new QChartView;

    selectCurrancy();

    if (ui->comboBoxRates->currentText().isNull())
        for (int i = 0; i < listCurrency.size(); ++i)
            ui->comboBoxRates->addItem(listCurrency[i]->getCurrency());

    on_comboBoxRates_activated(ui->comboBoxRates->currentIndex());
}

WgtGraphic::~WgtGraphic()
{
    delete ui;
    delete seriesCbRate;
    delete seriesSellingRate;
    delete seriesPurchaseRate;
    delete chartView;
    listCurrency.clear();
}

void WgtGraphic::setBalance(Balance *balance)
{
    this->balance = balance;
}

void WgtGraphic::slotUpdateInfo()
{
    ui->plblMoneyRub->setText(QString("%1 ₽").arg(QString::number(balance->getMoneyRub(), 'f', 2)));
    ui->plblMoneyDol->setText(QString("%1 $").arg(QString::number(balance->getMoneyDollars(), 'f', 2)));
    ui->plblMoneyEur->setText(QString("%1 €").arg(QString::number(balance->getMoneyEuro(), 'f', 2)));
}

void WgtGraphic::on_pbtnBackToMenu_clicked()
{
    emit signalExit();
}

bool WgtGraphic::selectExchangeRates(int idCurrency)
{
    QString sqlQuery = QString("SELECT * FROM [Курсы валют] WHERE КодВалют = '%1' ORDER BY ДатаКурс;").arg(idCurrency);

    QSqlQuery query;

    if (!query.exec(sqlQuery)) {
        qDebug() << query.lastError().text();
        return false;
    }

    while (query.next())
    {
        QDateTime date = query.value(query.record().indexOf("ДатаКурс")).toDateTime();

        double cbRate = query.value(query.record().indexOf("КурсЦБ")).toDouble();
        double sellingRate = query.value(query.record().indexOf("КурсПрод")).toDouble();
        double purchaseRate = query.value(query.record().indexOf("КурсПокуп")).toDouble();

        seriesCbRate->append(date.toMSecsSinceEpoch(), cbRate);
        seriesSellingRate->append(date.toMSecsSinceEpoch(), sellingRate);
        seriesPurchaseRate->append(date.toMSecsSinceEpoch(), purchaseRate);
    }

    return true;
}

bool WgtGraphic::selectCurrancy()
{
    QString strQuery = QString("SELECT * FROM Валюты");

    QSqlQuery query(strQuery);

    if (!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }

    while (query.next())
    {
        Currency *currency = new Currency(this);
        currency->setIdCurrency(query.value(query.record().indexOf("КодВалют")).toUInt());
        currency->setCurrency(query.value(query.record().indexOf("Валюта")).toString());
        QPixmap pix;
        pix.loadFromData(query.value(query.record().indexOf("Флаг")).toByteArray());
        currency->setFlag(pix);

        listCurrency.append(currency);
    }

    return true;
}

void WgtGraphic::clearGraphic()
{
    seriesCbRate->clear();
    seriesSellingRate->clear();
    seriesPurchaseRate->clear();
    delete chartView;
}

void WgtGraphic::on_comboBoxRates_activated(int index)
{
    seriesCbRate = new QLineSeries;
    seriesSellingRate = new QLineSeries;
    seriesPurchaseRate = new QLineSeries;
    clearGraphic();
    seriesCbRate->setName("КурсЦБ");
    seriesSellingRate->setName("КурсПрод");
    seriesPurchaseRate->setName("КурсПокуп");


    selectExchangeRates(listCurrency[index]->getIdCurrency());

    QChart *chart = new QChart;
    chart->addSeries(seriesCbRate);
    chart->addSeries(seriesSellingRate);
    chart->addSeries(seriesPurchaseRate);
    //chart->legend()->hide();
    chart->setTitle("Курс валют");

    QDateTimeAxis *axisX = new QDateTimeAxis(this);
    axisX->setTickCount(20);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Дата");
    chart->addAxis(axisX, Qt::AlignBottom);
    seriesCbRate->attachAxis(axisX);
    seriesSellingRate->attachAxis(axisX);
    seriesPurchaseRate->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis(this);
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Курс");
    chart->addAxis(axisY, Qt::AlignLeft);
    seriesCbRate->attachAxis(axisY);
    seriesSellingRate->attachAxis(axisY);
    seriesPurchaseRate->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView);
}

