#ifndef USERSEDITOR_H
#define USERSEDITOR_H

#include <QWidget>

namespace Ui {
class UsersEditor;
}

class UsersEditor : public QWidget
{
    Q_OBJECT

public:
    explicit UsersEditor(QWidget *parent = nullptr);
    ~UsersEditor();

private:
    Ui::UsersEditor *ui;
};

#endif // USERSEDITOR_H
