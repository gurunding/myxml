#ifndef ABOUTMYXML_H
#define ABOUTMYXML_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ABOUTMYXML; }
QT_END_NAMESPACE

class ABOUTMYXML : public QDialog
{
    Q_OBJECT

public:
    ABOUTMYXML(QWidget *parent = nullptr);
    ~ABOUTMYXML();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ABOUTMYXML *ui;
};
#endif // ABOUTMYXML_H
