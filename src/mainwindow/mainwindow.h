#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "options/options.h"
#include <QLabel>
#include "linenumber/linenumber.h"
#include <QAbstractButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MAINWINDOW; }
QT_END_NAMESPACE

class MAINWINDOW : public QMainWindow
{
    Q_OBJECT

public:
    explicit MAINWINDOW(QMainWindow *parent = 0);
    ~MAINWINDOW();
    void closeEvent(QCloseEvent *e);
    void set_app_statusBar();

private slots:
    void on_actionopen_triggered();
    void on_actionsave_triggered();
    void on_actionoptions_triggered();
    void change_classcial_skin();
    void change_black_skin();
    void highlignt_current_line();

private:
    Ui::MAINWINDOW *ui;
    OPTIONS *options;
    QLabel *label;
    LINESHOW *editor;
};
#endif // MAINWINDOW_H
