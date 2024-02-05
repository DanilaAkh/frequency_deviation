#ifndef ADD_NORMS_H
#define ADD_NORMS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class add_norms;
}

class add_norms : public QDialog
{
    Q_OBJECT

public:
    explicit add_norms(QWidget *parent = 0);
    ~add_norms();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::add_norms *ui;
    QSqlDatabase db;
    QSqlQuery *query;
};

#endif // ADD_NORMS_H
