#ifndef ADD_EQUIP_H
#define ADD_EQUIP_H

#include <QDialog>

namespace Ui {
class add_equip;
}

class add_equip : public QDialog
{
    Q_OBJECT

public:
    explicit add_equip(QWidget *parent = 0);
    ~add_equip();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

signals:
    void signal_form(QString strs[12]);

private:
    Ui::add_equip *ui;
};

#endif // ADD_EQUIP_H
