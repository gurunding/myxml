#include "mainwindow.h"
#include "highlight/highlighter.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QCloseEvent>
#include <QDebug>

MAINWINDOW::MAINWINDOW(QMainWindow *parent) :
    QMainWindow(parent)
    , ui(new Ui::MAINWINDOW)
{
    ui->setupUi(this);

    editor = new LINESHOW();
    ui->gridLayout->addWidget(editor);

    options = new OPTIONS();
    connect(options, &OPTIONS::selectBlack, this, &MAINWINDOW::change_black_skin);// 连接更改背景色为深色信号槽
    connect(options, &OPTIONS::selectClasscial, this, &MAINWINDOW::change_classcial_skin);// 连接更改背景色为经典色信号槽

    new HIGHLIGHTER(editor->document());

    label = new QLabel();
    set_app_statusBar();
    connect(editor, &QPlainTextEdit::cursorPositionChanged, this, &MAINWINDOW::set_app_statusBar);// 连接改变光标位置信号槽

    connect(editor, &QPlainTextEdit::cursorPositionChanged, this, &MAINWINDOW::highlignt_current_line);// 连接高亮显示当前行信号槽
}

MAINWINDOW::~MAINWINDOW()
{
}

/************************************************
函数名：on_actionoptions_triggered
功能：打开选项对话框
************************************************/
void MAINWINDOW::on_actionoptions_triggered()
{
    options->exec();// 设置选项对话框为模态对话框
}

/************************************************
函数名：changeBlackSkin
功能：改变工作区背景为深色槽函数
************************************************/
void MAINWINDOW::change_black_skin()
{
    editor->setStyleSheet("background-color: rgb(40, 40, 40);");
    editor->selectAll();
    QTextCharFormat textFmt;
    textFmt.setForeground(QColor(Qt::white));
    editor->mergeCurrentCharFormat(textFmt);
}

/************************************************
函数名：changeClasscialSkin
功能：改变工作区背景为经典色槽函数
************************************************/
void MAINWINDOW::change_classcial_skin()
{
    editor->setStyleSheet("background-color: rgb(255, 255, 255);");
    editor->selectAll();
    QTextCharFormat textFmt;
    textFmt.setForeground(QColor(Qt::black));
    editor->mergeCurrentCharFormat(textFmt);
}

/************************************************
函数名：on_actionopen_triggered
功能：打开xml文件
************************************************/
void MAINWINDOW::on_actionopen_triggered()
{
    QString xmlFileName = QFileDialog::getOpenFileName(this, "打开", "C:", "XML(*.xml)");
    if (!xmlFileName.isNull())
    {
        QFile file(xmlFileName);
        if (!file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            QMessageBox *openMessageBox = new QMessageBox(QMessageBox::Information, "提示", "这个xml文件打开失败了。",
                                          QMessageBox::Yes);
            openMessageBox->setButtonText(QMessageBox::Yes, "好的");
            return;
        }
        else
        {
            QTextStream in(&file);
            in.setCodec("UTF-8");// 设置字符编码，显示中文不乱码。
            editor->setPlainText(in.readAll());
            file.close();
        }
    }
}

/************************************************
函数名：on_actionsave_triggered
功能：保存xml文件
************************************************/
void MAINWINDOW::on_actionsave_triggered()
{
    QString xmlFileName = QFileDialog::getSaveFileName(this, "另存为", "C:", "XML(*.xml)");
    if (!xmlFileName.isNull())
    {
        QFile file(xmlFileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {   
            QMessageBox *saveMessageBox = new QMessageBox(QMessageBox::Information, "提示", "这个xm文件没有正确保存。",
                                          QMessageBox::Yes);
            saveMessageBox->setButtonText(QMessageBox::Yes, "好的");
            return;
        }
        else
        {
            QTextStream out(&file);
            out << editor->toPlainText();
            QMessageBox *saveMessageBox = new QMessageBox(QMessageBox::Information, "提示", "这个xml文件已经保存好了。",
                                          QMessageBox::Yes);
            saveMessageBox->setButtonText(QMessageBox::Yes, "好的");
            file.close();
        }
    }
}

/************************************************
函数名：closeEvent
功能：窗口关闭事件
参数：e
返回值：NULL
************************************************/
void MAINWINDOW::closeEvent(QCloseEvent *e)
{
    if (editor->document()->isModified())
    {
        QMessageBox *closeMessageBox = new QMessageBox(QMessageBox::Question, "警告", "应用已经检测到当前xml文件被修改，确认退出吗？",
                                       QMessageBox::Yes | QMessageBox::No);
        closeMessageBox->setButtonText(QMessageBox::Yes, "好的");
        closeMessageBox->setButtonText(QMessageBox::No, "取消");
        int ret = closeMessageBox->exec();
        if (ret == QMessageBox::Yes)
        {
            e->accept();
        }
        else
        {
            e->ignore();
            on_actionsave_triggered();
        }
    }
    else
    {
        this->close();
    }
}

/************************************************
函数名：set_app_statusBar
功能：设置应用光标位置状态栏
************************************************/
void MAINWINDOW::set_app_statusBar()
{
    QTextCursor textcursor = editor->textCursor();
    int i_row = textcursor.blockNumber() + 1;
    int i_col = textcursor.columnNumber() + 1;
    QString row = QString::number(i_row);
    QString col = QString::number(i_col);
    label->setText(row + "行" + col + "列");
    statusBar()->addPermanentWidget(label);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    statusBar()->setSizeGripEnabled(false);
}

/************************************************
函数名：highlignt_current_line
功能：高亮显示当前行槽函数
************************************************/
void MAINWINDOW::highlignt_current_line()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!editor->isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::lightGray).lighter(38);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = editor->textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    editor->setExtraSelections(extraSelections);
}
