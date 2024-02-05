#ifndef ETC_H
#define ETC_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>

namespace Ui {
class ETC;
}

class ETC : public QDialog
{
    Q_OBJECT

public:
    explicit ETC(QWidget *parent = 0);
    ~ETC();

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

private:
    Ui::ETC *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    int row = -1;
};

#endif // ETC_H
