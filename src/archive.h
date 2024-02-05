#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>

namespace Ui {
class archive;
}

class archive : public QMainWindow
{
    Q_OBJECT

public:
    explicit archive(QWidget *parent = 0);
    ~archive();

private slots:
    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

private:
    Ui::archive *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    int row = -1;
};

#endif // ARCHIVE_H
