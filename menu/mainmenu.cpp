#include "mainmenu.h"
#include "ui_mainmenu.h"

#include <QTimer>

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->wgtMenu);
    ui->wgtMenu->setWindowTitle("Меню");
    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());

    user = new Users(this);
    balance = new Balance(this);

    QTimer::singleShot(20, this, SLOT(slotUpdateInfo()));
}

void MainMenu::setUser(const QString userName, const QString password)
{
    QString strQuery = QString("SELECT * FROM Users "
                               "WHERE user_name = '%1' and password = '%2';").arg(userName).arg(password);

    QSqlQuery query(strQuery);

    if (!query.exec())
        qDebug() << query.lastError().text();

    while (query.next())
    {
        QPixmap pix;
        user->setUserName(userName);
        user->setPassword(password);
        user->setIdUser(query.value(query.record().indexOf("id")).toUInt());
        user->setFirstName(query.value(query.record().indexOf("first_name")).toString());
        user->setLastName(query.value(query.record().indexOf("last_name")).toString());
        user->setSecondName(query.value(query.record().indexOf("second_name")).toString());
        user->setEmail(query.value(query.record().indexOf("email")).toString());
        user->setSex(query.value(query.record().indexOf("sex")).toString());
        user->setDateOfBirth(query.value(query.record().indexOf("date_of_birth")).toDate());
        user->setRegistrationDate(query.value(query.record().indexOf("registration_date")).toDateTime());
        user->setAdmin(query.value(query.record().indexOf("administrator")).toBool());
        pix.loadFromData(query.value(query.record().indexOf("photo")).toByteArray());
        user->setPhoto(pix);
    }

    if (!getBalace(balance, user))
        qDebug() << "Ошибка добавления баланса";
}

bool MainMenu::getBalace(Balance *balance, Users* user)
{
    QString strQuery = QString("SELECT * FROM Баланс WHERE id_клиента = '%1';").arg(user->getIdUser());
    QSqlQuery query(strQuery);

    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return false;
    }

    while (query.next())
    {
        balance->setIdUser(user->getIdUser());
        balance->setMoneyRub(query.value(query.record().indexOf("сумма_рубль")).toDouble());
        balance->setMoneyDollars(query.value(query.record().indexOf("сумма_доллар")).toDouble());
        balance->setMoneyEuro(query.value(query.record().indexOf("сумма_евро")).toDouble());
    }
    return true;
}

void MainMenu::slotUpdateInfo()
{
    ui->plblMoneyRub->setText(QString("%1 ₽").arg(QString::number(balance->getMoneyRub(), 'f', 2)));
    ui->plblMoneyDol->setText(QString("%1 $").arg(QString::number(balance->getMoneyDollars(), 'f', 2)));
    ui->plblMoneyEur->setText(QString("%1 €").arg(QString::number(balance->getMoneyEuro(), 'f', 2)));

    bool checkButoonExRate =  balance->getMoneyRub() > 0 || balance->getMoneyDollars() > 0 || balance->getMoneyEuro() > 0;
    ui->pbtnRunExchangeRate->setEnabled(checkButoonExRate);

    if (!user->getAdmin())
        ui->pbtnRunWgtEditTable->hide();

    if(!user->getPhoto().isNull())
        ui->commandLinkButton->setIcon(user->getPhoto());
    else
        if (user->getSex() == "Female") {
            QIcon icon;
            icon.addFile(":/icons2/icons8-woman100.png");
            ui->commandLinkButton->setIcon(icon);
        }
}

MainMenu::~MainMenu()
{
    delete ui;
    delete user;
    delete balance;
}

void MainMenu::on_pbtnLogOut_clicked()
{
    emit signalLoginOut();
    delete this;
}

void MainMenu::on_commandLinkButton_clicked()
{
    wgtProfil = new WgtProfil(this);
    wgtProfil->setUser(user);
    wgtProfil->setBalance(balance);

    connect(wgtProfil, &WgtProfil::signalExit, this, &MainMenu::slotExitWgtProfil);

    ui->stackedWidget->addWidget(wgtProfil);
    ui->stackedWidget->setCurrentWidget(wgtProfil);

    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());
    emit signalUpdateTitle(windowTitle());
}

void MainMenu::slotExitWgtProfil()
{
    disconnect(wgtProfil, &WgtProfil::signalExit, this, &MainMenu::slotExitWgtProfil);
    slotUpdateInfo();
    delete wgtProfil;
    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());
    emit signalUpdateTitle(windowTitle());
}

void MainMenu::on_pbtnRunWgtEditTable_clicked()
{
    wgtEditTable = new WgtEditTable(this);

    ui->stackedWidget->addWidget(wgtEditTable);
    ui->stackedWidget->setCurrentWidget(wgtEditTable);

    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());
    emit signalUpdateTitle(windowTitle());
}


void MainMenu::on_pbtnRunExchangeRate_clicked()
{
    wgtExCurrency = new wgtExchangeCurrency(this);
    wgtExCurrency->setUser(user);
    wgtExCurrency->setBalance(balance);

    connect(wgtExCurrency, &wgtExchangeCurrency::signalExit, this, &MainMenu::slotExitWgtExCerrncy);

    ui->stackedWidget->addWidget(wgtExCurrency);
    ui->stackedWidget->setCurrentWidget(wgtExCurrency);

    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());
    emit signalUpdateTitle(windowTitle());
}

void MainMenu::slotExitWgtExCerrncy()
{
    disconnect(wgtExCurrency, &wgtExchangeCurrency::signalExit, this, &MainMenu::slotExitWgtExCerrncy);
    slotUpdateInfo();
    delete wgtExCurrency;
    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());
    emit signalUpdateTitle(windowTitle());
}

void MainMenu::on_pbtnRunWgtGraphic_clicked()
{
    wgtGraphic = new WgtGraphic(this);
    wgtGraphic->setBalance(balance);

    connect(wgtGraphic, &WgtGraphic::signalExit, this, &MainMenu::slotExitWgtGraphic);

    ui->stackedWidget->addWidget(wgtGraphic);
    ui->stackedWidget->setCurrentWidget(wgtGraphic);

    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());
    emit signalUpdateTitle(windowTitle());
}

void MainMenu::slotExitWgtGraphic()
{
    disconnect(wgtGraphic, &WgtGraphic::signalExit, this, &MainMenu::slotExitWgtGraphic);
    delete  wgtGraphic;
    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());
    emit signalUpdateTitle(windowTitle());
}

void MainMenu::on_pbtnRunWgtMyOperation_clicked()
{
    wgtMyOperations = new WgtMyOperations(this);
    wgtMyOperations->setUser(user);
    wgtMyOperations->setBalance(balance);

    connect(wgtMyOperations, &WgtMyOperations::signalExit, this, &MainMenu::slotExitWgtMyOpertion);

    ui->stackedWidget->addWidget(wgtMyOperations);
    ui->stackedWidget->setCurrentWidget(wgtMyOperations);

    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());
    emit signalUpdateTitle(windowTitle());
}

void MainMenu::slotExitWgtMyOpertion()
{
    disconnect(wgtMyOperations, &WgtMyOperations::signalExit, this, &MainMenu::slotExitWgtMyOpertion);
    delete wgtMyOperations;
    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());
    emit signalUpdateTitle(windowTitle());
}

