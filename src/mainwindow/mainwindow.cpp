#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shared/xmlsyntaxhighlighter.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QCloseEvent>

MAINWINDOW::MAINWINDOW(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MAINWINDOW)
{
    ui->setupUi(this);
    options = new OPTIONS();
//    第一种连接信号槽方式为什么不行？？？
//    connect(options, SIGNAL(selectBlack()), this, SLOT(changeClasscialSkin()));
//    connect(options, SIGNAL(selectClasscial()), this, SLOT(changeClasscialSkin()));
    connect(options, &OPTIONS::selectBlack, this, &MAINWINDOW::changeBlackSkin);
    connect(options, &OPTIONS::selectClasscial, this, &MAINWINDOW::changeClasscialSkin);
    new XmlSyntaxHighlighter(ui->textEdit->document());
}

MAINWINDOW::~MAINWINDOW()
{
    delete ui;
}

void MAINWINDOW::on_pushButton_options_clicked()
{
    options->exec();
}

void MAINWINDOW::changeBlackSkin()
{
    ui->textEdit->setStyleSheet("background-color: rgb(30, 30, 30);");
    ui->textEdit->selectAll();
    ui->textEdit->setTextColor(QColor(Qt::white));
}

void MAINWINDOW::changeClasscialSkin()
{
    ui->textEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void MAINWINDOW::on_pushButton_open_clicked()
{
    QString xmlFileName = QFileDialog::getOpenFileName(this, "打开", "C:", "xml文件(*.xml)");
    if (!xmlFileName.isNull())
    {
        QFile file(xmlFileName);
        if (!file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
        QMessageBox::warning(this, "警告", "这个xml文件打开失败了。", QMessageBox::Yes);
        return;
        }
        else
        {
            QTextStream in(&file);
            in.setCodec("UTF-8");
            ui->textEdit->setText(in.readAll());
            file.close();
        }
    }
}

void MAINWINDOW::on_pushButton_save_clicked()
{
    QString xmlFileName = QFileDialog::getSaveFileName(this, "另存为", "C:", "xml文件(*.xml)");
    if (!xmlFileName.isNull())
    {
        QFile file(xmlFileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, "警告", "这个xml文件没有正确保存。", QMessageBox::Yes);
            return;
        }
        else
        {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            QMessageBox::information(this, "提示", "这个xml文件已经保存好了。", QMessageBox::Yes);
            file.close();
        }
    }
}

void MAINWINDOW::closeEvent(QCloseEvent *e)
{
    if (ui->textEdit->document()->isModified())
    {
        int ret = QMessageBox::warning(this, "提示", "应用已经检测到当前xml文件被修改，确认退出吗？",
                                       QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes)
        {
            e->accept();
        }
        else
        {
            e->ignore();
            on_pushButton_save_clicked();
        }

    }
    else
    {
        this->close();
    }
}
