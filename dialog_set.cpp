#include "dialog_set.h"
#include "ui_dialog_set.h"

#include <QDebug>

Dialog_set::Dialog_set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_set)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    this->setWindowTitle(u8"Spaste 截图设置");
}

Dialog_set::~Dialog_set()
{
    delete ui;
}
