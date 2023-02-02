#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "options/options.h"
#include <QLabel>
#include "linenumber/linenumber.h"
#include <QAbstractButton>
#include "help/aboutmyxml.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MAINWINDOW; }
QT_END_NAMESPACE

class MAINWINDOW : public QMainWindow
{
    Q_OBJECT

public:
    explicit MAINWINDOW(QMainWindow *parent = 0);
    ~MAINWINDOW();
    void closeEvent(QCloseEvent *event) override;
    void set_app_statusBar();
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private slots:
    void on_actionopen_triggered();
    void on_actionsave_triggered();
    void on_actionoptions_triggered();
    void change_classcial_skin();
    void change_black_skin();
    void highlignt_current_line();
    void on_actionhelp_triggered();
//    void on_actionparse_triggered();

private:
    Ui::MAINWINDOW *ui;
    OPTIONS *options;
    QLabel *label;
    LINESHOW *editor;
    ABOUTMYXML *aboutmyxml;
};
extern int ret;// 声明获得保存完成消息对话框按钮点击返回值全局整型变量

#endif // MAINWINDOW_H
