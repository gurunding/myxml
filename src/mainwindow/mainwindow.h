#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "options/options.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MAINWINDOW; }
QT_END_NAMESPACE

class MAINWINDOW : public QWidget
{
    Q_OBJECT

public:
    MAINWINDOW(QWidget *parent = nullptr);
    ~MAINWINDOW();

    void closeEvent(QCloseEvent *e);

private slots:
    void on_pushButton_options_clicked();
    void changeClasscialSkin();
    void changeBlackSkin();
    void on_pushButton_open_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::MAINWINDOW *ui;
    OPTIONS *options;
};
#endif // MAINWINDOW_H
