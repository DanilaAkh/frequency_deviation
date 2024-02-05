#include "add_norms_19.h"
#include "ui_add_norms_19.h"

add_norms_19::add_norms_19(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_norms_19)
{
    ui->setupUi(this);
}

add_norms_19::~add_norms_19()
{
    delete ui;
}

void add_norms_19::on_pushButton_2_clicked()
{
    this->close();
}

void add_norms_19::on_pushButton_clicked()
{
    //Создание базы данных
    db = QSqlDatabase::addDatabase("QSQLITE", "norms19_XX");
    db.setDatabaseName("./norms19_XX.db");
    if (db.open())
        qDebug("open");
    else
        qDebug("not open");

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE norms19_XX(emission_class TEXT, koef_vk TEXT, koef_v40 TEXT, koef_v50 TEXT, koef_v60 TEXT);");

    QString strs[5] = {ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(),
                       ui->lineEdit_4->text(), ui->lineEdit_5->text()};

    query->prepare("INSERT INTO norms19_XX(emission_class, koef_vk, koef_v40, koef_v50, koef_v60) "
            "VALUES (?, ?, ?, ?, ?)");
    for  (int i = 0 ; i < 5; ++i)
    {
        query->addBindValue(strs[i]);
    }

    query->exec();


    db.close();
    db.removeDatabase("norms19_XX");
    this->close();
}
