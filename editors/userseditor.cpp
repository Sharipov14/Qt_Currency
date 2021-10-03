#include "userseditor.h"
#include "ui_userseditor.h"

UsersEditor::UsersEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsersEditor)
{
    ui->setupUi(this);
}

UsersEditor::~UsersEditor()
{
    delete ui;
}
