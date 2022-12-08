#include "options.h"
#include "ui_options.h"
#include <QDebug>

OPTIONS::OPTIONS(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OPTIONS)
{
    ui->setupUi(this);
}

OPTIONS::~OPTIONS()
{
    delete ui;
}

void OPTIONS::on_pushButton_apply_clicked()
{
    if (ui->radioButton_black->isChecked())
    {
        emit selectBlack();
    }
    else if (ui->radioButton_classcial->isChecked())
    {
        emit selectClasscial();
    }

    this->close();
}

