#include "archive.h"
#include "ui_archive.h"

archive::archive(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::archive)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Создание базы данных
    db = QSqlDatabase::addDatabase("QSQLITE", "archive123");
    db.setDatabaseName("./archive.db");
    if (db.open())
        qDebug("open");
    else
        qDebug("not open");

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE archive(centre_freq TEXT, abs_center_err TEXT, emi_class TEXT, KSPC TEXT, KSPC_error TEXT, "
                "KSPC_40 TEXT, KSPC_50 TEXT, KSPC_60 TEXT, type_RES TEXT, net_name TEXT, place TEXT,"
                "date TEXT);");

    model = new QSqlTableModel(this, db);
    model->setTable("archive");
    model->setHeaderData(0, Qt::Horizontal, tr("Измеренная центральная частота"));
    model->setHeaderData(1, Qt::Horizontal, tr("Абсолютная погрешность центральной частоты"));
    model->setHeaderData(2, Qt::Horizontal, tr("Класс излучения"));
    model->setHeaderData(3, Qt::Horizontal, tr("КШПЧ"));
    model->setHeaderData(4, Qt::Horizontal, tr("Абсолютная погрешность КШПЧ"));
    model->setHeaderData(5, Qt::Horizontal, tr("В-40"));
    model->setHeaderData(6, Qt::Horizontal, tr("В-50"));
    model->setHeaderData(7, Qt::Horizontal, tr("В-60"));
    model->setHeaderData(8, Qt::Horizontal, tr("Тип РЭС"));
    model->setHeaderData(9, Qt::Horizontal, tr("Обозначение в сети"));
    model->setHeaderData(10, Qt::Horizontal, tr("Место установки РЭС"));
    model->setHeaderData(11, Qt::Horizontal, tr("Дата"));

    model->select();

    ui->tableView->setModel(model);


    model->insertRow(model->rowCount());    

    query->exec();

    model->select();
}

archive::~archive()
{
    db.close();
    db.removeDatabase("archive123");
    delete ui;
}

void archive::on_pushButton_2_clicked()
{
    this->close();
}

void archive::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

void archive::on_pushButton_3_clicked()
{
    if (row == -1)
    {
        QMessageBox::warning(this, "Ошибка!", "Выберите оборудование, которое необходимо удалить!");
        return;
    }
    model->removeRow(row);
    model->select();
    row = -1;
}
