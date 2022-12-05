#ifndef XMLTOOL_H
#define XMLTOOL_H

#include <QWidget>
#include "theme/theme.h"

QT_BEGIN_NAMESPACE
namespace Ui { class XMLTOOL; }
QT_END_NAMESPACE

class XMLTOOL : public QWidget
{
    Q_OBJECT

public:
    XMLTOOL(QWidget *parent = nullptr);
    ~XMLTOOL();

    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_environment_clicked();

    void change_classcial_theme();

    void change_deep_black_theme();

private:
    Ui::XMLTOOL *ui;
    THEME *setEnv;//子窗体对象
};
#endif // XMLTOOL_H
