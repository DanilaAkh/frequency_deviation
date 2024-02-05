#ifndef METHODS_H
#define METHODS_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>

namespace Ui {
class methods;
}

class methods : public QMainWindow
{
    Q_OBJECT

public:
    explicit methods(QWidget *parent = 0);
    ~methods();

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

private:
    Ui::methods *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    int row = -1;
};

#endif // METHODS_H
