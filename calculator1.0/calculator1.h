#ifndef CALCULATOR1_H
#define CALCULATOR1_H

#include <QWidget>
#include <QStack>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class calculator1; }
QT_END_NAMESPACE

class calculator1 : public QWidget
{
    Q_OBJECT

public:
    calculator1(QWidget *parent = nullptr);
    ~calculator1();
    QStack <double> q1;
    QStack <char> q2;
    void work();
private slots:
    void on_pushButton_clicked();
    void count();
    void on_ans1_inputRejected();
    void on_confirm_clicked();

    void on_less_clicked();

    void on_confirm_3_clicked();

    void on_confirm_4_clicked();

    void on_confirm_5_clicked();

    void on_confirm_6_clicked();

    void on_confirm_7_clicked();

    void on_confirm_8_clicked();

    void on_confirm_9_clicked();

    void on_confirm_10_clicked();

    void on_NUMBER_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_confirm_13_clicked();

    void on_confirm_14_clicked();

    void on_confirm_11_clicked();

    void on_confirm_12_clicked();

private:
    Ui::calculator1 *ui;
};
#endif // CALCULATOR1_H
