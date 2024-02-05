#ifndef EQUIP_H
#define EQUIP_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "add_equip.h"
#include <QString>
#include <QMessageBox>

namespace Ui {
class Equip;
}

class MyModel : public QSqlTableModel
{
   Q_OBJECT
public:
    MyModel(){}
protected:
    QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const
    {
        qDebug("here");
        //Роль - выравнивание
        if (role == Qt::TextAlignmentRole)
        {
           return Qt::AlignCenter;
        }
        return QSqlTableModel::data(index, role);
    }
};



class Equip : public QMainWindow
{
    Q_OBJECT

public:
    explicit Equip(QWidget *parent = 0);
    ~Equip();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Equip *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    int row = -1;


};

#endif // EQUIP_H
