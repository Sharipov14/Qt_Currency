#include "wgtexchangecurrency.h"
#include "ui_wgtexchangecurrency.h"

#include <QTimer>
#include "Database/sqlrec.h"

wgtExchangeCurrency::wgtExchangeCurrency(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wgtExchangeCurrency)
{
    ui->setupUi(this);
    setWindowTitle("Обмен валют");

    session = new Session(this);
    contract = new Contract(this);
    exchangeRates = new ExchangeRates(this);
    operation = new Operation(this);

    if (!selectCurrency())
        qDebug() << "Ошибка получения валют";

    QTimer::singleShot(20, this, SLOT(slotUpdateInfo()));
    connect(ui->doubleSpinBoxInputMoney, SIGNAL(valueChanged(const double)), this, SLOT(slotConvert(const double)));
}

void wgtExchangeCurrency::slotUpdateInfo()
{
    ui->plblMoneyRub->setText(QString("%1 ₽").arg(QString::number(balance->getMoneyRub(), 'f', 2)));
    ui->plblMoneyDol->setText(QString("%1 $").arg(QString::number(balance->getMoneyDollars(), 'f', 2)));
    ui->plblMoneyEur->setText(QString("%1 €").arg(QString::number(balance->getMoneyEuro(), 'f', 2)));

    if (ui->comboBoxRates->currentText().isNull())
        for (int i = 0; i < listCurrency.size(); ++i)
            ui->comboBoxRates->addItem(listCurrency[i]->getCurrency());

    on_comboBoxByeOrSelling_activated(ui->comboBoxByeOrSelling->currentIndex());
}

wgtExchangeCurrency::~wgtExchangeCurrency()
{
    delete ui;
    delete session;
    delete contract;
    delete exchangeRates;
    delete operation;
    listCurrency.clear();
}

void wgtExchangeCurrency::setUser(Users *user)
{
    this->user = user;
}

void wgtExchangeCurrency::setBalance(Balance *balance)
{
    this->balance = balance;
}

void wgtExchangeCurrency::createSession(Session *session)
{
    session->setDate(QDateTime::currentDateTime());
    session->setIdEmployee(2);
}

void wgtExchangeCurrency::selectContract(Contract *contract)
{
    QString strQuery = QString("SELECT * FROM  Договоры WHERE КодКлиент = %1").arg(user->getIdUser());

    QSqlQuery query;

    if (!query.exec(strQuery))
        qDebug() << query.lastError();

    while(query.next())
    {
        contract->setContractNumber(query.value(query.record().indexOf("НомДог")).toUInt());
        contract->setDate(query.value(query.record().indexOf("ДатаДог")).toDate());
        contract->setIdUsers(query.value(query.record().indexOf("КодКлиент")).toUInt());
    }
}

bool wgtExchangeCurrency::selectCurrency()
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

bool wgtExchangeCurrency::selecetExRates(ExchangeRates *exchageRates, const int idRate,  const QDate dateRate)
{
    QString strQuery = QString("SELECT * FROM [Курсы валют] "
                                        "WHERE КодВалют = '%1' "
                                        "AND ДатаКурс = '%2';").arg(idRate).arg(dateRate.toString(Qt::ISODate));

    QSqlQuery query(strQuery);

    if (!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }

    while (query.next())
    {
        exchangeRates->setDate(query.value(query.record().indexOf("ДатаКурс")).toDate());
        exchageRates->setIdCurrency(query.value(query.record().indexOf("КодВалют")).toUInt());
        exchageRates->setRateCB(query.value(query.record().indexOf("КурсЦБ")).toDouble());
        exchageRates->setSellingRate(query.value(query.record().indexOf("КурсПрод")).toDouble());
        exchageRates->setPurchaseRate(query.value(query.record().indexOf("КурсПокуп")).toDouble());
    }
    return true;
}

bool wgtExchangeCurrency::insertOperation(Operation *operation)
{
    selectContract(contract);

    operation->setTypeOfOperation(ui->comboBoxByeOrSelling->currentText());
    operation->setDateOperation(session->getDate());
    operation->setContractNumber(contract->getContractNumber());
    operation->setMoney(ui->doubleSpinBoxInputMoney->value());

    if (!SqlRec::sqlExec({{":typeOfOperation", operation->getTypeOfOperation()},
                          {":dateOperation", operation->getDateOperation()},
                          {":contractNumber", operation->getContractNumber()},
                          {":idCurrency", operation->getIdCurrency()},
                          {":money", operation->getMoney()}}, SQL_REC::insertOperation))
        return false;

    return true;
}

bool wgtExchangeCurrency::insetSession(Session *session)
{
    if (!SqlRec::sqlExec({{":date", session->getDate()},
                          {":idEmployee", session->getIdEmployee()}}, SQL_REC::isertSession))
        return false;

    return true;
}

bool wgtExchangeCurrency::updateBalance(Balance *balance)
{
    if (!SqlRec::sqlExec({{":rub", balance->getMoneyRub()},
                          {":dollar", balance->getMoneyDollars()},
                          {":euro", balance->getMoneyEuro()},
                          {":idUser", user->getIdUser()}}, SQL_REC::updateBalance))
        return false;

    return true;
}

void wgtExchangeCurrency::slotConvert(const double in)
{
    ui->pbtnBye->setEnabled(ui->doubleSpinBoxInputMoney->value() > 0);

    double out;

    if (ui->comboBoxByeOrSelling->currentText() == "Покупка")
        out = QString::number(in / ratio, 'f', 2).toDouble();
    else if (ui->comboBoxByeOrSelling->currentText() == "Продажа")
        out = QString::number(in * ratio, 'f', 2).toDouble();
    else return;

    ui->lcdMoney->display(out);

}

void wgtExchangeCurrency::on_pbtnBackToMenu_clicked()
{
    emit signalExit();
}

void wgtExchangeCurrency::on_comboBoxByeOrSelling_activated(int index)
{
    if (ui->comboBoxByeOrSelling->itemText(index) == "Покупка")
    {
        ui->gridLayout->addWidget(ui->plblFlagRub, 0, 0);
        ui->gridLayout->addWidget(ui->plblRub, 0, 1);
        ui->gridLayout->addWidget(ui->plblFlagRates, 1, 0);
        ui->gridLayout->addWidget(ui->comboBoxRates, 1, 1);

        ui->doubleSpinBoxInputMoney->setMaximum(balance->getMoneyRub());
    }
    else if (ui->comboBoxByeOrSelling->itemText(index) == "Продажа")
    {
        ui->gridLayout->addWidget(ui->plblFlagRates, 0, 0);
        ui->gridLayout->addWidget(ui->comboBoxRates, 0, 1);
        ui->gridLayout->addWidget(ui->plblFlagRub, 1, 0);
        ui->gridLayout->addWidget(ui->plblRub, 1, 1);
    }

    ui->doubleSpinBoxInputMoney->setValue(0);
    on_comboBoxRates_activated(ui->comboBoxRates->currentIndex());
}

void wgtExchangeCurrency::on_comboBoxRates_activated(int index)
{
    ui->plblFlagRates->setPixmap(listCurrency[index]->getFlag());

    if (!selecetExRates(exchangeRates, listCurrency[index]->getIdCurrency(), QDate::currentDate()))
        qDebug() << "Ошибка курса валют";

    ui->plblShowRateCB->setText(QString("%1").arg(QString::number(exchangeRates->getRateCB(), 'f', 4)));
    ui->plblShowRateSelling->setText(QString("%1").arg(QString::number(exchangeRates->getSellingRate(), 'f', 4)));
    ui->plblShowRatePurchase->setText(QString("%1").arg(QString::number(exchangeRates->getPurchaseRate(), 'f', 4)));

    operation->setIdCurrency(listCurrency[index]->getIdCurrency());

    if (ui->comboBoxByeOrSelling->currentText() == "Продажа")
    {
        ratio = exchangeRates->getSellingRate();

        if (ui->comboBoxRates->itemText(0) == ui->comboBoxRates->currentText())
            ui->doubleSpinBoxInputMoney->setMaximum(balance->getMoneyDollars());

        else if (ui->comboBoxRates->itemText(1) == ui->comboBoxRates->currentText())
            ui->doubleSpinBoxInputMoney->setMaximum(balance->getMoneyEuro());
    }
    else
        ratio = exchangeRates->getPurchaseRate();

    ui->doubleSpinBoxInputMoney->setValue(0);

}

void wgtExchangeCurrency::on_pbtnBye_clicked()
{
    createSession(session);
    if (insetSession(session) && insertOperation(operation)) {
        if (ui->comboBoxByeOrSelling->currentText() == "Продажа")
        {
            if (ui->comboBoxRates->currentText() == ui->comboBoxRates->itemText(0))
                balance->setMoneyDollars(QString::number(balance->getMoneyDollars() - ui->doubleSpinBoxInputMoney->value(), 'f', 2).toDouble());

            else if (ui->comboBoxRates->currentText() == ui->comboBoxRates->itemText(1))
                balance->setMoneyEuro(QString::number(balance->getMoneyEuro() - ui->doubleSpinBoxInputMoney->value(), 'f', 2).toDouble());

            balance->setMoneyRub(QString::number(balance->getMoneyRub() + ui->lcdMoney->value(), 'f', 2).toDouble());
        }
        else
        {
            if (ui->comboBoxRates->currentText() == ui->comboBoxRates->itemText(0))
                balance->setMoneyDollars(QString::number(balance->getMoneyDollars() + ui->lcdMoney->value(), 'f', 2).toDouble());

            else if (ui->comboBoxRates->currentText() == ui->comboBoxRates->itemText(1))
                balance->setMoneyEuro(QString::number(balance->getMoneyEuro() + ui->lcdMoney->value(), 'f', 2).toDouble());

            balance->setMoneyRub(QString::number(balance->getMoneyRub() - ui->doubleSpinBoxInputMoney->value(), 'f', 2).toDouble());
        }

        if (!updateBalance(balance))
            qDebug() << "Ошибка обновления баланса";

        slotUpdateInfo();
    }
    else
    {
        qDebug() << "Ошибка добалении сессии или операции";
        return;
    }
}

