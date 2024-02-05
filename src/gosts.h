#ifndef GOSTS_H
#define GOSTS_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>

namespace Ui {
class GOSTs;
}

class GOSTs : public QMainWindow
{
    Q_OBJECT

public:
    explicit GOSTs(QWidget *parent = 0);
    ~GOSTs();

private slots:
    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

private:
    Ui::GOSTs *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    int row = -1;
};

#endif // GOSTS_H
