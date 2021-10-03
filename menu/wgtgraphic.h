#ifndef WGTGRAPHIC_H
#define WGTGRAPHIC_H

#include <QWidget>
#include <QLineSeries>
#include <QChartView>
#include <tables/currency.h>
#include <tables/balance.h>

namespace Ui {
class WgtGraphic;
}

class WgtGraphic : public QWidget
{
    Q_OBJECT
private:
    QList<Currency*> listCurrency;
    Balance *balance;
    QLineSeries *seriesCbRate;
    QLineSeries *seriesSellingRate;
    QLineSeries *seriesPurchaseRate;
    QChartView *chartView;

public:
    explicit WgtGraphic(QWidget *parent = nullptr);
    ~WgtGraphic();

    void setBalance(Balance*);

private slots:
    void slotUpdateInfo();

    void on_pbtnBackToMenu_clicked();

    void on_comboBoxRates_activated(int index);

signals:
    void signalExit();

private:
    Ui::WgtGraphic *ui;
    bool selectExchangeRates(int idCurrency);
    bool selectCurrancy();
    void clearGraphic();
};

#endif // WGTGRAPHIC_H
