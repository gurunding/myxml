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
    setEnv = new THEME();
    connect(setEnv, &THEME::selectClasscialSignal, this, &XMLTOOL::change_classcial_theme);
    connect(setEnv, &THEME::selectDeepBlackSignal, this, &XMLTOOL::change_deep_black_theme);
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
            xmlIN.setCodec("UTF-8");//读文件编码方式，解决textedit显示中文乱码问题。
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

/************************************************
函数名：on_pushButton_environment_clicked()
功能：调用选择主题对话框窗口
************************************************/
void XMLTOOL::on_pushButton_environment_clicked()
{
    setEnv->exec();
}

/************************************************
函数名：change_classcial_theme()
功能：实现经典主题功能
************************************************/
void XMLTOOL::change_classcial_theme()
{
    QFile loadQSSFile("../theme/res/classcial-style.qss");
    loadQSSFile.open(QIODevice::ReadOnly);
    ui->textEdit_show->setStyleSheet(loadQSSFile.readAll());
    loadQSSFile.close();
    ui->textEdit_show->selectAll();
    ui->textEdit_show->setTextColor(QColor(0, 0, 0));
}

/************************************************
函数名：change_deep_black_theme()
功能：实现暗黑主题功能
************************************************/
void XMLTOOL::change_deep_black_theme()
{   
    QFile loadQSSFile("../theme/res/deep-black-style.qss");
    loadQSSFile.open(QIODevice::ReadOnly);
    ui->textEdit_show->setStyleSheet(loadQSSFile.readAll());
    loadQSSFile.close();
    ui->textEdit_show->selectAll();
    ui->textEdit_show->setTextColor(QColor(255, 255, 255));
}
