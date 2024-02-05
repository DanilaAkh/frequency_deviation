#ifndef ADD_NORMS_19_H
#define ADD_NORMS_19_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
namespace Ui {
class add_norms_19;
}

class add_norms_19 : public QDialog
{
    Q_OBJECT

public:
    explicit add_norms_19(QWidget *parent = 0);
    ~add_norms_19();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::add_norms_19 *ui;
    QSqlDatabase db;
    QSqlQuery *query;
};

#endif // ADD_NORMS_19_H
