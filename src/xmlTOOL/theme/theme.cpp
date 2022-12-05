#include "theme.h"
#include "ui_theme.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>

bool THEME::select_classcial = false;
bool THEME::select_deepBlack = false;

THEME::THEME(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::THEME)
{
    ui->setupUi(this);
    setFixedSize(500, 500);
}

THEME::~THEME()
{
    delete ui;
}

void THEME::on_radioButton_classcial_clicked(bool checked)
{
    if (checked)
    {
        ui->radioButton_deep_black->setEnabled(false);
        ui->pushButton_apply->setEnabled(true);
        THEME::select_classcial = true;
    }
    else
    {
        ui->radioButton_deep_black->setEnabled(true);
        ui->pushButton_apply->setEnabled(false);
        THEME::select_classcial = false;
    }
}

void THEME::on_radioButton_deep_black_clicked(bool checked)
{
    if (checked)
    {
        ui->radioButton_classcial->setEnabled(false);
        ui->pushButton_apply->setEnabled(true);
        THEME::select_deepBlack = true;
    }
    else
    {
        ui->radioButton_classcial->setEnabled(true);
        ui->pushButton_apply->setEnabled(false);
        THEME::select_deepBlack = false;
    }
}

void THEME::on_pushButton_apply_clicked()
{
    if (THEME::select_classcial == true)
    {
        emit selectClasscialSignal();
    }
    else if (THEME::select_deepBlack == true)
    {
        emit selectDeepBlackSignal();
    }
}

