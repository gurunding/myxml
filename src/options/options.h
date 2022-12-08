#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class OPTIONS; }
QT_END_NAMESPACE

class OPTIONS : public QDialog
{
    Q_OBJECT

public:
    OPTIONS(QWidget *parent = nullptr);
    ~OPTIONS();

signals:
    void selectBlack();
    void selectClasscial();

private slots:
    void on_pushButton_apply_clicked();

private:
    Ui::OPTIONS *ui;
};
#endif // OPTIONS_H
