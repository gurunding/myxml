#include "aboutmyxml.h"
#include "ui_aboutmyxml.h"

ABOUTMYXML::ABOUTMYXML(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ABOUTMYXML)
{
    ui->setupUi(this);
    setFixedSize(500, 300);
}

ABOUTMYXML::~ABOUTMYXML()
{
    delete ui;
}


void ABOUTMYXML::on_pushButton_clicked()
{
    this->close();
}

