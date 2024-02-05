#ifndef NORMS19_H
#define NORMS19_H

#include <QDialog>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
namespace Ui {
class Norms19;
}

class Norms19 : public QDialog
{
    Q_OBJECT

public:
    explicit Norms19(QWidget *parent = 0);
    ~Norms19();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);


    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Norms19 *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    int row = -1;
};

#endif // NORMS19_H
