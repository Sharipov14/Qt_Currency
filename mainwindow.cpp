#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    runLoginForm();
}

void MainWindow::runLoginForm()
{
    loginForm = new LoginForm(this);

    connect(loginForm, SIGNAL(signalLogIn(const QString, const QString)), this, SLOT(runMenuForm(QString, QString)));

    ui->stackedWidget->addWidget(loginForm);
    ui->stackedWidget->setCurrentWidget(loginForm);

    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());
}

void MainWindow::runMenuForm(QString userName, QString password)
{
    mainMenu = new MainMenu(this);
    mainMenu->setUser(userName, password);

    connect(mainMenu, &MainMenu::signalLoginOut, this, &MainWindow::runLoginForm);
    connect(mainMenu, &MainMenu::signalUpdateTitle, this, &MainWindow::slotUpdateTitle);

    ui->stackedWidget->addWidget(mainMenu);
    ui->stackedWidget->setCurrentWidget(mainMenu);

    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());

    delete loginForm;
}

void MainWindow::runRegistrationForm()
{
    registrationForm = new RegistrationForm(this);

    ui->stackedWidget->addWidget(registrationForm);
    ui->stackedWidget->setCurrentWidget(registrationForm);

    connect(registrationForm, &RegistrationForm::signalCancelRegistration, this, &MainWindow::runLoginForm);

    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());

    delete loginForm;
}

void MainWindow::runRestoreAccount()
{
    restoreAccount = new RestoreAccount(this);

    ui->stackedWidget->addWidget(restoreAccount);
    ui->stackedWidget->setCurrentWidget(restoreAccount);

    connect(restoreAccount, &RestoreAccount::signalCancelRestorePassowrd, this, &MainWindow::runLoginForm);

    setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());

    delete loginForm;
}

void MainWindow::slotUpdateTitle(const QString title)
{
    setWindowTitle(title);
}

MainWindow::~MainWindow()
{
    delete ui->stackedWidget->currentWidget();
    delete ui;
}

