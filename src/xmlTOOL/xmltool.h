#ifndef XMLTOOL_H
#define XMLTOOL_H

#include <QWidget>

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

private:
    Ui::XMLTOOL *ui;
};
#endif // XMLTOOL_H
