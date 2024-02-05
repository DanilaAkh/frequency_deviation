#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QVector>
#include <QDialog>

namespace Ui {
class graphics;
}

class graphics : public QDialog
{
    Q_OBJECT

public:
    explicit graphics(QWidget *parent = 0);
    ~graphics();


private:
    Ui::graphics *ui;
    QVector<double> x, y;
    double height;
    double max = -500;
    double min = 500;
    QVector<double> maxV;

public slots:
    void graphic_slot(QVector<double> a, QVector<double> b);
private slots:
    void on_pushButton_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
};

#endif // GRAPHICS_H
