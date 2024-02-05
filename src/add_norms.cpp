#include "add_norms.h"
#include "ui_add_norms.h"

add_norms::add_norms(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_norms)
{
    ui->setupUi(this);
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    db = QSqlDatabase::addDatabase("QSQLITE", "norms17_XX");
    db.setDatabaseName("./norms17_XX.db");
    if (db.open())
        qDebug("open");
    else
        qDebug("not open");

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE norms17_XX(ETC TEXT, start_freq TEXT, stop_freq TEXT, razmermost TEXT, abs_error TEXT, otn_error TEXT);");
    query->exec("SELECT ETC FROM norms17_XX");
    while (query->next())
    {
        ui->comboBox_3->addItem(query->value(0).toString());
    }
    db.close();
    db.removeDatabase("norms17_XX");
}

add_norms::~add_norms()
{
    delete ui;
}

void add_norms::on_pushButton_2_clicked()
{
    this->close();
}

void add_norms::on_pushButton_clicked()
{
    //Создание базы данных
    db = QSqlDatabase::addDatabase("QSQLITE", "norms17_XX");
    db.setDatabaseName("./norms17_XX.db");
    if (db.open())
        qDebug("open");
    else
        qDebug("not open");

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE norms17_XX(ETC TEXT, start_freq TEXT, stop_freq TEXT, razmermost TEXT, abs_error TEXT, otn_error TEXT);");

    QString strs[6] = {ui->comboBox_3->currentText(), ui->lineEdit_2->text(), ui->lineEdit_4->text(), ui->comboBox_2->currentText(), "", ""};

    if (ui->comboBox->currentIndex() == 0)
    {
        strs[5] = ui->lineEdit_3->text();
        strs[4] = "-";
    }
    else
    {
        strs[4] = ui->lineEdit_3->text();
        strs[5] = "-";
    }

    query->prepare("INSERT INTO norms17_XX(ETC, start_freq, stop_freq, razmermost, abs_error, otn_error) "
            "VALUES (?, ?, ?, ?, ?, ?)");
    for  (int i = 0 ; i < 6; ++i)
    {
        query->addBindValue(strs[i]);
    }

    query->exec();

    db.close();
    db.removeDatabase("norms17_XX");
    this->close();
}
