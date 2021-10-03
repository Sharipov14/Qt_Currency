#include "mydelegate.h"

MyDelegate::MyDelegate(QString tableName)
{
    this->tableName = tableName;
}

QWidget *MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QModelIndex newIndex = index;


}

void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QVariantList data;



    for (int col = 1; col <= data.size(); ++col)
        model->setData(model->index(index.row(), col), data[col - 1]);
}

void MyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    int xTopLeft = option.rect.left() + 400;
//    int yTopLeft = option.rect.top() + 200;
//    int xBottomRight = 175;
//    int yBottomRight = 120;

//    editor->setGeometry(xTopLeft, yTopLeft, xBottomRight, yBottomRight);
}
