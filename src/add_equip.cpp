#include "add_equip.h"
#include "ui_add_equip.h"

add_equip::add_equip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_equip)
{
    ui->setupUi(this);
}

add_equip::~add_equip()
{
    delete ui;
}

void add_equip::on_pushButton_2_clicked()
{
    this->close();
}

void add_equip::on_pushButton_clicked()
{
    QString strs[12] = {ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(),
                     ui->dateEdit->text(), ui->lineEdit_4->text(), ui->dateEdit_2->text(),
                     ui->lineEdit_5->text(), ui->lineEdit_6->text(), ui->lineEdit_7->text(),
                     ui->lineEdit_8->text(), ui->dateEdit_3->text(),  ui->lineEdit_9->text()};
    emit signal_form(strs);
    this->close();
    QDate date;
    date.setDate(2010,1,1);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(date);
    ui->lineEdit_4->clear();
    ui->dateEdit_2->setDate(date);
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->dateEdit_3->setDate(date);
    ui->lineEdit_9->clear();
}
