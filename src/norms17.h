#ifndef NORMS17_H
#define NORMS17_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlDatabase>

namespace Ui {
class Norms17;
}

class Norms17 : public QDialog
{
    Q_OBJECT

public:
    explicit Norms17(QWidget *parent = 0);
    ~Norms17();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Norms17 *ui;    
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    int row = -1;
};

#endif // NORMS17_H
