#ifndef NORMS_H
#define NORMS_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>
#include "norms17.h"
#include "norms19.h"

namespace Ui {
class Norms;
}

class Norms : public QMainWindow
{
    Q_OBJECT

public:
    explicit Norms(QWidget *parent = 0);
    ~Norms();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Norms *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    int row = -1;
    Norms17 *norms_17;
    Norms19 *norms_19;
};

#endif // NORMS_H
