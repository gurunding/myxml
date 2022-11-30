#include "xmltool.h"
#include "ui_xmltool.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include "xmlsyntaxhighlighter.h"

XMLTOOL::XMLTOOL(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::XMLTOOL)
{
    ui->setupUi(this);
    new XmlSyntaxHighlighter(ui->textEdit_show->document());
}

XMLTOOL::~XMLTOOL()
{
    delete ui;
}

/************************************************
函数名：closeEvent(QCloseEvent *event)
功能：窗口关闭事件
参数：event
返回值：NULL
************************************************/
void XMLTOOL::closeEvent(QCloseEvent *event)
{
    if (ui->textEdit_show->document()->isModified())
    {
        int ret = QMessageBox::information(this, "提示", "检测到当前xml文件已经修改，确认退出吗？",
                                           QMessageBox::Yes | QMessageBox::No);

        if (ret == QMessageBox::No)
        {
            event->ignore();
            on_pushButton_save_clicked();
        }
        else
        {
            event->accept();
        }
    }

    else
    {
        this->close();
    }
}

/************************************************
函数名：on_pushButton_open_clicked()
功能：打开xml文件
************************************************/
void XMLTOOL::on_pushButton_open_clicked()
{
    QString openXMLFileName = QFileDialog::getOpenFileName(this, "打开", "C:", "*xml");
    if (!openXMLFileName.isNull())
    {
        QFile xmlFile(openXMLFileName);
        if (!xmlFile.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            QMessageBox::warning(this, "警告", "打开xml文件失败！", QMessageBox::Yes);
            return;
        }
        else
        {
            QTextStream xmlIN(&xmlFile);
            ui->textEdit_show->setText(xmlIN.readAll());
            xmlFile.close();
        }
    }
}

/************************************************
函数名：on_pushButton_save_clicked()
功能：保存xml文件
************************************************/
void XMLTOOL::on_pushButton_save_clicked()
{
    QString saveXMLFile = QFileDialog::getSaveFileName(this, "另存为", "C:", "*xml");
    if (!saveXMLFile.isNull())
    {
        QFile xmlFile(saveXMLFile);
        if (!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, "警告", "发生未知错误！", QMessageBox::Yes);
            return;
        }
        else
        {
            QTextStream xmlOUT(&xmlFile);
            xmlOUT << ui->textEdit_show->toPlainText();
            QMessageBox::information(this, "提示", "xml文件已被保存！", QMessageBox::Yes);
            xmlFile.close();
        }
    }
}

