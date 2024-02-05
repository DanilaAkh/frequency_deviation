#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_2_clicked()
{
    this->close();
}

void Settings::on_radioButton_3_clicked()
{
    ui->radioButton->setChecked(1);
    is_new = true;
}

void Settings::on_radioButton_2_clicked()
{
    ui->radioButton_4->setChecked(1);
    is_new = false;
}

void Settings::on_radioButton_clicked()
{
    ui->radioButton_3->setChecked(1);
    is_new = true;
}

void Settings::on_radioButton_4_clicked()
{
    ui->radioButton_2->setChecked(1);
    is_new = false;
}

void Settings::on_pushButton_clicked()
{
    emit signal_formula(is_new);
    this->close();
}
