#include "wgtedittable.h"
#include "ui_wgtedittable.h"

#include <QSqlError>

WgtEditTable::WgtEditTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WgtEditTable)
{
    ui->setupUi(this);
    setWindowTitle("Администратор");

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName(QApplication::applicationDirPath() + "\\Database\\Currency.db");

    if (!db.open())
        qDebug() << "Ошибка подключения БД: " << db.lastError();

    ui->comboBoxListTables->addItems(db.tables());

    connect(ui->comboBoxListTables, QOverload<int>::of(&QComboBox::activated),
            [=](int index) { on_comboBoxListTables_activated(index); });

    model = new QSqlTableModel(this);

    if (!setTableModel(model))
        qDebug() << model->lastError().text();

    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

WgtEditTable::~WgtEditTable()
{
    delete model;
    delete ui;
}

bool WgtEditTable::setTableModel(QSqlTableModel* model, int index)
{
    bool check = true;

    model->setTable(ui->comboBoxListTables->itemText(index));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    if (!model->select())
        check = false;

    ui->tableView->setModel(model);
    //ui->tableView->setColumnHidden(model->fieldIndex("id"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("photo"), true);

    return check;
}

void WgtEditTable::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

void WgtEditTable::on_pbtnSaveInDb_clicked()
{
    if (!model->submitAll())
        qDebug() << model->lastError();
}

void WgtEditTable::on_pbtnCancelSaveInDb_clicked()
{
    model->revertAll();
}

void WgtEditTable::on_pbtnInsertRow_clicked()
{
    if (!model->insertRow(model->rowCount()))
        qDebug() << model->lastError().text();
}

void WgtEditTable::on_pbtnDeleteRow_clicked()
{
    if (!model->removeRow(row))
        qDebug() << model->lastError().text();
}

void WgtEditTable::on_pbtnBackToMenu_clicked()
{
    delete this;
}

void WgtEditTable::on_comboBoxListTables_activated(int index)
{
    if (!setTableModel(model, index))
        qDebug() << model->lastError().text();
}
