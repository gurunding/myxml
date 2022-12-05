#ifndef THEME_H
#define THEME_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class THEME; }
QT_END_NAMESPACE

class THEME : public QDialog
{
    Q_OBJECT

public:
    THEME(QWidget *parent = nullptr);
    ~THEME();

    static bool select_classcial;
    static bool select_deepBlack;

signals:
    void selectClasscialSignal();//
    void selectDeepBlackSignal();//

private slots:

    void on_radioButton_classcial_clicked(bool checked);

    void on_radioButton_deep_black_clicked(bool checked);

    void on_pushButton_apply_clicked();

private:
    Ui::THEME *ui;
};
#endif // THEME_H
