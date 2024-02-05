#include "norms19.h"
#include "ui_norms19.h"

Norms19::Norms19(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Norms19)
{
    ui->setupUi(this);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Создание базы данных
    db = QSqlDatabase::addDatabase("QSQLITE", "norms19_XX");
    db.setDatabaseName("./norms19_XX.db");
    if (db.open())
        qDebug("open");
    else
        qDebug("not open");

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE norms19_XX(emission_class TEXT, koef_vk TEXT, koef_v40 TEXT, koef_v50 TEXT, koef_v60 TEXT);");

    model = new QSqlTableModel(this, db);
    model->setTable("norms19_XX");
    model->setHeaderData(0, Qt::Horizontal, tr("Класс излучения"));
    model->setHeaderData(1, Qt::Horizontal, tr("Коэффициент КШПЧ"));
    model->setHeaderData(2, Qt::Horizontal, tr("Коэффициент В-40"));
    model->setHeaderData(3, Qt::Horizontal, tr("Коэффициент В-50"));
    model->setHeaderData(4, Qt::Horizontal, tr("Коэффициент В-60"));
    model->select();

    ui->tableView->setModel(model);
}

Norms19::~Norms19()
{
    db.close();
    db.removeDatabase("norms19_XX");
    delete ui;
}

void Norms19::on_pushButton_2_clicked() //Кнопка добавления
{
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
    model->select();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

void Norms19::on_pushButton_clicked()
{
    if (row == -1)
    {
        QMessageBox::warning(this, "Ошибка!", "Выберите нормы, которые необходимо удалить!");
        return;
    }    
    model->removeRow(row);
    model->select();
    row = -1;
}

void Norms19::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

void Norms19::on_pushButton_3_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

void Norms19::on_pushButton_4_clicked() //Кнопка редактирования
{
    query->exec("SELECT * FROM norms19_XX");
    if (row == -1)
    {
        QMessageBox::warning(this, "Ошибка!", "Выберите нормы, которое необходимо редактировать!");
        return;
    }
    query->seek(row);
    ui->lineEdit->setText(query->value(0).toString());
    ui->lineEdit_2->setText(query->value(1).toString());
    ui->lineEdit_3->setText(query->value(2).toString());
    ui->lineEdit_4->setText(query->value(3).toString());
    ui->lineEdit_5->setText(query->value(4).toString());
    model->removeRow(row);
    model->select();
    row = -1;
}
