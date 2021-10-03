#ifndef WGTEDITTABLE_H
#define WGTEDITTABLE_H

#include <QWidget>
#include <QWidget>
#include <QtSqlDepends>
#include <QSqlTableModel>

namespace Ui {
class WgtEditTable;
}

class WgtEditTable : public QWidget
{
    Q_OBJECT
private:
    QSqlDatabase db;
    QSqlTableModel *model;
    int row;

public:
    explicit WgtEditTable(QWidget *parent = nullptr);
    ~WgtEditTable();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_pbtnSaveInDb_clicked();

    void on_pbtnCancelSaveInDb_clicked();

    void on_pbtnInsertRow_clicked();

    void on_pbtnDeleteRow_clicked();

    void on_pbtnBackToMenu_clicked();

    void on_comboBoxListTables_activated(int index);

private:
    Ui::WgtEditTable *ui;
    bool setTableModel(QSqlTableModel* model, int index = 0);
};

#endif // WGTEDITTABLE_H
