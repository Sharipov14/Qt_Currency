#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QItemDelegate>


class MyDelegate : public QItemDelegate
{
    Q_OBJECT
private:
    QString tableName;

public:
    MyDelegate(QString tablName);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // MYDELEGATE_H
