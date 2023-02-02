#include "mainwindow.h"
#include "highlight/highlighter.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QCloseEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMimeType>
#include <QMimeDatabase>
#include <QDebug>
#include <QXmlStreamReader>

int ret = 0;

MAINWINDOW::MAINWINDOW(QMainWindow *parent) :
    QMainWindow(parent)
    , ui(new Ui::MAINWINDOW)
{
    ui->setupUi(this);

    setAcceptDrops(true);

    editor = new LINESHOW();
    editor->setAcceptDrops(false);
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
    QString xmlFilePath = QFileDialog::getOpenFileName(this, "打开", "C:", "XML文件(*.xml)");
    if (xmlFilePath.isEmpty())
    {
        return;
    }
    else
    {
        QFile xmlFile(xmlFilePath);
        if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return;
        }

        QTextStream read(&xmlFile);
        read.setCodec("UTF-8");// 设置字符编码格式为UTF-8，显示中文字符不乱码。
        editor->setPlainText(read.readAll());
        xmlFile.close();
    }
}

/************************************************
函数名：on_actionsave_triggered
功能：保存xml文件
************************************************/
void MAINWINDOW::on_actionsave_triggered()
{
    QString xmlFilePath = QFileDialog::getSaveFileName(this, "保存为", "C:", "XML文件(*.xml)");

    if (xmlFilePath.isEmpty())
    {
        return;
    }
    else
    {
        QFile xmlFile(xmlFilePath);
        if (!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        }

        QTextStream write(&xmlFile);
        write.setCodec("UTF-8");
        write << editor->toPlainText();
        QMessageBox *saveFinishedMessageBox = new QMessageBox(QMessageBox::Information,
                                                      "提示", "这个xml文件已经保存好了。",
                                                      QMessageBox::Yes);
        saveFinishedMessageBox->setButtonText(QMessageBox::Yes, "好的");
        ret = saveFinishedMessageBox->exec();
        xmlFile.close();
    }
}

/************************************************
函数名：closeEvent
功能：窗口关闭事件
参数：event
返回值：NULL
************************************************/
void MAINWINDOW::closeEvent(QCloseEvent *event)
{
    if (editor->document()->isModified() && ret != QMessageBox::Yes)
    {
        QMessageBox *closeWarningMessageBox = new QMessageBox(QMessageBox::Question,
                                                       "警告", "检测到当前xml文件被修改，确认退出吗？",
                                                       QMessageBox::Yes | QMessageBox::No);
        closeWarningMessageBox->setButtonText(QMessageBox::Yes, "好的");
        closeWarningMessageBox->setButtonText(QMessageBox::No, "取消");
        int ret = closeWarningMessageBox->exec();
        if (ret == QMessageBox::Yes)
        {
            event->accept();
        }
        else
        {
            event->ignore();
            on_actionsave_triggered();
        }
    }

    else if (editor->document()->isModified() && ret == QMessageBox::Yes)
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

/************************************************
函数名：on_actionhelp_triggered
功能：打开应用程序帮助对话框
************************************************/
void MAINWINDOW::on_actionhelp_triggered()
{
    aboutmyxml = new ABOUTMYXML();
    aboutmyxml->show();
}

/************************************************
函数名：dragEnterEvent
功能：xml文件拖拽进入事件
参数：event
返回值：NULL
************************************************/
void MAINWINDOW::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

/************************************************
函数名：dropEvent
功能：xml文件拖拽释放事件
参数：event
返回值：NULL
************************************************/
void MAINWINDOW::dropEvent(QDropEvent *event)
{
    const QMimeData *mimedata = event->mimeData();
    if (!mimedata->hasUrls())
    {
        return;
    }
    else
    {

        if (event->mimeData()->hasUrls() && event->mimeData()->urls()[0].fileName().right(3).compare("xml") == 0)
        {
            QList<QUrl> urls = mimedata->urls();
            QString xmlFilePath = urls.at(0).toLocalFile();
            QFile xmlFile(xmlFilePath);
            if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                return;
            }
            else
            {
                QTextStream loadFile(&xmlFile);
                loadFile.setCodec("UTF-8");
                editor->setPlainText(loadFile.readAll());
                xmlFile.close();
            }
        }
        else
        {
            QMessageBox *dragDropMessageBox = new QMessageBox(QMessageBox::Warning,
                                                              "警告", "不支持的文件类型！",
                                                              QMessageBox::Yes);
            dragDropMessageBox->setButtonText(QMessageBox::Yes, "好的");
            dragDropMessageBox->exec();
        }
    }
}

///************************************************
//函数名：on_actionparse_triggered
//功能：解析打开的xml文件
//************************************************/
//void MAINWINDOW::on_actionparse_triggered()
//{
//        QString XMLPath = QFileDialog::getOpenFileName(this, "选择文件", "C:", "XML文件(*.xml)");
//        QFile parseXMLFile(XMLPath);
//        if (!parseXMLFile.open(QIODevice::ReadOnly | QIODevice::Text))
//        {
//            return;
//        }

//        QXmlStreamReader reader;
//        reader.setDevice(&parseXMLFile);
//        while (!reader.atEnd())
//        {
//            QXmlStreamReader::TokenType type = reader.readNext();
//            if (type == QXmlStreamReader::StartDocument)///1
//            {
//                qDebug() << "xml版本：" << reader.documentVersion() << "编码：" << reader.documentEncoding();
//            }
//            else if (type ==  QXmlStreamReader::StartElement)///2
//            {
//                qDebug() << "开始节点：" << reader.name();
//            }
//            else if (reader.attributes().hasAttribute("id"))///3
//            {
//                qDebug() << "属性值：" << reader.attributes().value("id");
//            }
//            else if (type == QXmlStreamReader::EndElement)///4
//            {
//                qDebug() << "结束节点：" << reader.name();
//            }
//            else if (type == QXmlStreamReader::Characters && !reader.isWhitespace())///5
//            {
//                qDebug() << "文本内容："<< reader.text();
//            }
//            else if (reader.hasError())
//            {

//            }
//        }
//        parseXMLFile.close();
//}
