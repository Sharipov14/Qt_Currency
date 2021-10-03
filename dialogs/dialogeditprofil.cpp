#include "dialogeditprofil.h"
#include "ui_dialogeditprofil.h"

#include <QTimer>
#include <QFileDialog>

DialogEditProfil::DialogEditProfil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditProfil)
{
    ui->setupUi(this);
    setWindowTitle("Изменить профиль");

    ui->dateEditDayOfBirth->setDate(QDate::currentDate());

    connectChanged();

    QTimer::singleShot(20, this, SLOT(slotUpdateInfo()));
}

DialogEditProfil::~DialogEditProfil()
{
    delete ui;
}

void DialogEditProfil::setUser(Users *user)
{
    this->user = user;
}

void DialogEditProfil::connectChanged()
{
    connect(ui->lineEditUserName, &QLineEdit::textChanged, this, &DialogEditProfil::slotTextChanged);
    connect(ui->lineEditFirstName, &QLineEdit::textChanged, this, &DialogEditProfil::slotTextChanged);
    connect(ui->lineEditLastName, &QLineEdit::textChanged, this, &DialogEditProfil::slotTextChanged);
    connect(ui->lineEditSecondName, &QLineEdit::textChanged, this, &DialogEditProfil::slotTextChanged);
    connect(ui->lineEditEmail, &QLineEdit::textChanged, this, &DialogEditProfil::slotTextChanged);
}

void DialogEditProfil::slotUpdateInfo()
{
    ui->lineEditUserName->setText(user->getUserName());
    ui->lineEditFirstName->setText(user->getFirstName());
    ui->lineEditLastName->setText(user->getLastName());
    ui->lineEditSecondName->setText(user->getSecondName());
    ui->lineEditEmail->setText(user->getEmail());
    ui->dateEditDayOfBirth->setDate(user->getDateOfBirth());

    if(!user->getPhoto().isNull())
        ui->plblPhoto->setPixmap(user->getPhoto().scaled(260, 260));
    else {
        QPixmap pix;
        if (user->getSex() == "Female") {
            pix.load(":/icons2/icons8-woman100.png");
            ui->plblPhoto->setPixmap(pix.scaled(260, 260));
        }
        else if (user->getSex() == "Male") {
            pix.load(":/icons2/icons8-man-100.png");
            ui->plblPhoto->setPixmap(pix.scaled(260, 260));
        }
    }
}

bool DialogEditProfil::slotTextChanged()
{
    checkUserName = !ui->lineEditUserName->text().isEmpty() && ui->checkBoxChangeUserName->isChecked();
    checkFirstName = !ui->lineEditFirstName->text().isEmpty() && ui->checkBoxChangeFirstName->isChecked();
    checkLastName = !ui->lineEditLastName->text().isEmpty() && ui->checkBoxChangeLastName->isChecked();
    checkSecondName = !ui->lineEditSecondName->text().isEmpty() && ui->checkBoxSecondName->isChecked();
    checkEmail = !ui->lineEditEmail->text().isEmpty() && ui->checkBoxChangeEmail->isChecked();

    return checkUserName || checkFirstName || checkLastName || checkSecondName || checkEmail;
}

void DialogEditProfil::on_checkBoxChangeUserName_clicked()
{
    ui->lineEditUserName->setEnabled(ui->checkBoxChangeUserName->isChecked());
}

void DialogEditProfil::on_checkBoxChangeFirstName_clicked()
{
    ui->lineEditFirstName->setEnabled(ui->checkBoxChangeFirstName->isChecked());
}

void DialogEditProfil::on_checkBoxChangeLastName_clicked()
{
    ui->lineEditLastName->setEnabled(ui->checkBoxChangeLastName->isChecked());
}

void DialogEditProfil::on_checkBoxSecondName_clicked()
{
    ui->lineEditSecondName->setEnabled(ui->checkBoxSecondName->isChecked());
}

void DialogEditProfil::on_checkBoxChangeEmail_clicked()
{
    ui->lineEditEmail->setEnabled(ui->checkBoxChangeEmail->isChecked());
}

void DialogEditProfil::on_checkBoxChangeDayOfBirth_clicked()
{
    ui->dateEditDayOfBirth->setEnabled(ui->checkBoxChangeDayOfBirth->isChecked());
}

void DialogEditProfil::on_checkBoxChangePhoto_clicked()
{
    ui->pbtnLoadPhoto->setEnabled(ui->checkBoxChangePhoto->isChecked());
    ui->pbtnDeletePhoto->setEnabled(ui->checkBoxChangePhoto->isChecked() && !user->getPhoto().isNull());
}

void DialogEditProfil::on_pbtnLoadPhoto_clicked()
{
    QString url = QFileDialog::getOpenFileName(this, "Выберите файл", "", "*.png *.jpg *.ico *.jpeg");
    if(!url.isNull())
    {
        QPixmap pix(url);
        ui->plblPhoto->setPixmap(pix.scaled(260, 260));
        ui->pbtnDeletePhoto->setEnabled(true);
    }
}

void DialogEditProfil::on_pbtnDeletePhoto_clicked()
{
    QPixmap pix;

    if (user->getSex() == "Female") {
        pix.load(":/icons2/icons8-woman100.png");
        ui->plblPhoto->setPixmap(pix.scaled(260, 260));
    }
    else if (user->getSex() == "Male") {
        pix.load(":/icons2/icons8-man-100.png");
        ui->plblPhoto->setPixmap(pix.scaled(260, 260));
    }
    ui->pbtnDeletePhoto->setEnabled(false);
}

void DialogEditProfil::on_pbtnOk_clicked()
{
    if (slotTextChanged() || ui->checkBoxChangePhoto->isChecked() || ui->checkBoxChangeDayOfBirth->isChecked())
    {
        if (checkUserName)
            user->setUserName(ui->lineEditUserName->text());
        if (checkFirstName)
            user->setFirstName(ui->lineEditFirstName->text());
        if (checkLastName)
            user->setLastName(ui->lineEditLastName->text());
        if (checkSecondName)
            user->setSecondName(ui->lineEditSecondName->text());
        if (checkEmail)
            user->setEmail(ui->lineEditEmail->text());
        if (ui->checkBoxChangeDayOfBirth->isChecked())
            user->setDateOfBirth(ui->dateEditDayOfBirth->date());
        if (ui->checkBoxChangePhoto->isChecked())
            user->setPhoto(ui->plblPhoto->pixmap());
        this->accept();
    }
    else {
        qDebug() << "Привет!!!";
    }
}
