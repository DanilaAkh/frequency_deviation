#include "equip.h"
#include "ui_equip.h"

Equip::Equip(QWidget *parent) : //Реализация окна реестра РКО
    QMainWindow(parent),
    ui(new Ui::Equip)
{
    ui->setupUi(this);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    //Создание базы данных
    db = QSqlDatabase::addDatabase("QSQLITE", "new123");
    db.setDatabaseName("./equipment.db");
    if (db.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("not open");
    }

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE equipment(type_ts TEXT, kind_ts TEXT, manufac TEXT, year TEXT, serial_num TEXT, date TEXT, inverter_num TEXT, place TEXT,"
                "subdivision TEXT, num_certifi TEXT, date_verific TEXT, stability FLOAT, otn_pogreshnost FLOAT);");

    model = new QSqlTableModel(this, db);
    model->setTable("equipment");

    model->setHeaderData(0, Qt::Horizontal, tr("Тип ТС"));
    model->setHeaderData(1, Qt::Horizontal, tr("Вид ТС"));
    model->setHeaderData(2, Qt::Horizontal, tr("Изготовитель"));
    model->setHeaderData(3, Qt::Horizontal, tr("Год выпуска"));
    model->setHeaderData(4, Qt::Horizontal, tr("Заводской номер"));
    model->setHeaderData(5, Qt::Horizontal, tr("Дата ввода в эксплуатацию"));
    model->setHeaderData(6, Qt::Horizontal, tr("Инв. номер"));
    model->setHeaderData(7, Qt::Horizontal, tr("Размещение"));
    model->setHeaderData(8, Qt::Horizontal, tr("Подразделение"));
    model->setHeaderData(9, Qt::Horizontal, tr("№ свидетельства"));
    model->setHeaderData(10, Qt::Horizontal, tr("Дата поверки"));
    model->setHeaderData(11, Qt::Horizontal, tr("Относит. погрешн. частоты ОГ СИ/ТС"));
    model->setHeaderData(12, Qt::Horizontal, tr("Относит. погрешн. уровня СИ/ТС"));
    model->select();

    ui->tableView->setModel(model);    
}

Equip::~Equip()
{
    delete ui;
    db.close();
    db.removeDatabase("new123");
}

void Equip::on_pushButton_clicked()
{
    if (ui->lineEdit->text().size() == 0 || ui->lineEdit_2->text().size() == 0 || ui->lineEdit_3->text().size() == 0 || ui->lineEdit_4->text().size() == 0)
    {
        QMessageBox::warning(this, "Ошибка!", "Вы не ввели необходимые параметры!");
        return;
    }
    model->insertRow(model->rowCount());
    QString strs[] = {ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(),
                      ui->dateEdit->text(), ui->lineEdit_4->text(), ui->dateEdit_2->text(),
                      ui->lineEdit_5->text(), ui->lineEdit_6->text(), ui->lineEdit_7->text(),
                      ui->lineEdit_8->text(), ui->dateEdit_3->text(), ui->lineEdit_9->text(),
                      ui->lineEdit_10->text()};
    query->prepare("INSERT INTO equipment (type_ts, kind_ts, manufac, year, serial_num, date, inverter_num, place, subdivision, num_certifi, date_verific, stability, otn_pogreshnost) "
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    for  (int i = 0 ; i < 13; ++i)
    {
        query->addBindValue(strs[i]);
    }

    query->exec();
    QDate date;
    date.setDate(2010,1,1);
    model->select();
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
    ui->lineEdit_10->clear();

}

void Equip::on_pushButton_2_clicked()
{
    if (row == -1)
    {
        QMessageBox::warning(this, "Ошибка!", "Выберите оборудование, которое необходимо удалить!");
    }
    model->removeRow(row);
    model->select();
    row = -1;
}

void Equip::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

void Equip::on_pushButton_3_clicked()
{
    query->exec("SELECT * FROM equipment");
    if (row == -1)
    {
        QMessageBox::warning(this, "Ошибка!", "Выберите оборудование, которое необходимо редактировать!");
        return;
    }
    query->seek(row);
    QString date_year = query->value(3).toString();
    QString date_expl = query->value(5).toString();
    QString date_verific = query->value(10).toString();
    QDate date;
    ui->lineEdit->setText(query->value(0).toString());
    ui->lineEdit_2->setText(query->value(1).toString());
    ui->lineEdit_3->setText(query->value(2).toString());    
    date.setDate(date_year.toInt(), 1, 1);
    ui->dateEdit->setDate(date);
    ui->lineEdit_4->setText(query->value(4).toString());
    QStringList parts;
    parts = date_expl.split(".");
    date.setDate(parts.at(2).toInt(), parts.at(1).toInt(), parts.at(0).toInt());
    ui->dateEdit_2->setDate(date);
    ui->lineEdit_5->setText(query->value(6).toString());
    ui->lineEdit_6->setText(query->value(7).toString());
    ui->lineEdit_7->setText(query->value(8).toString());
    ui->lineEdit_8->setText(query->value(9).toString());
    parts = date_verific.split(".");
    date.setDate(parts.at(2).toInt(), parts.at(1).toInt(), parts.at(0).toInt());
    ui->dateEdit_3->setDate(date);
    ui->lineEdit_9->setText(query->value(11).toString());
    ui->lineEdit_10->setText(query->value(12).toString());
    model->removeRow(row);
    model->select();
    row = -1;
}

void Equip::on_pushButton_4_clicked()
{
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
    ui->lineEdit_10->clear();
}
