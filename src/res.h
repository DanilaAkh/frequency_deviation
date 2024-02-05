#ifndef RES_H
#define RES_H

#include <QMainWindow>
#include <QComboBox>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include "graphics.h"
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSet>

namespace Ui {
class RES;
}

class RES : public QMainWindow
{
    Q_OBJECT

public:
    explicit RES(QWidget *parent = 0);
    ~RES();


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_groupBox_clicked();

    void on_groupBox_2_clicked();

    void on_pushButton_5_clicked();

    void on_groupBox_5_clicked();

    void on_checkBox_clicked();

    void on_pushButton_6_clicked();

    int razmernost(int index);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_12_clicked();

    void on_checkBox_2_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

    void on_comboBox_6_currentTextChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_8_clicked();

signals:
    void signal_form();
    void signal_form2();   
    void signal_graphics(QVector<double>, QVector<double>);

private:
    Ui::RES *ui;
    int curIndex = 0;
    float N = 0;
    QString fileName;
    graphics *graphic;
    QVector<double> x, y;
    QSqlDatabase db;
    QSqlQuery *query;
    QSet<QString> uniqueSet;
    double height = 100;
    bool use_new_formula = true;

public slots:
    void Slot_formula(bool);
};

#endif // RES_H
