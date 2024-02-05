#include "methods.h"
#include "ui_methods.h"

methods::methods(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::methods)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Создание базы данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./methods.db");
    if (db.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("not open");
    }

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE Methods(Methods TEXT, Path TEXT);");

    model = new QSqlTableModel(this, db);
    model->setTable("Methods");
    model->setHeaderData(0, Qt::Horizontal, tr("Методики"));
    model->select();

    ui->tableView->setModel(model);
    model->removeColumn(1);

}

methods::~methods()
{
    delete ui;
    delete query;
    delete model;
}

void methods::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath(), "Все документы *.* ;; Файлы PDF"
                                                                                                " *.pdf ;; Документы Word *.doc ; *.docx");

    if (!(fileName.size()))
    {
        return;
    }

    model->insertRow(model->rowCount());

    query->prepare("INSERT INTO Methods (Methods, Path) "
            "VALUES (?, ?)");
    QStringList parts = fileName.split("/");
    QString lastBit = parts.at(parts.size()-1);

    query->addBindValue(lastBit);
    query->addBindValue(fileName);
    query->exec();
    model->select();

}

void methods::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

void methods::on_pushButton_2_clicked()
{
    if (row == -1)
    {
        QMessageBox::warning(this, "Ошибка!", "Выберите Методику, которую необходимо удалить!");
        return;
    }
    model->removeRow(row);
    model->select();
    row = -1;

}

void methods::on_tableView_doubleClicked(const QModelIndex &index)
{
    //QMessageBox::information(this, "hello", "hello");
    query->exec("SELECT Methods, Path FROM Methods");
    query->seek(index.row());
    QString FileName = query->value(1).toString();
    if (QDesktopServices::openUrl(QUrl::fromLocalFile(FileName)))
    {
        qDebug("open");
    }
    else
    {
        QMessageBox::warning(this, "Ошибка!", "Данный файл не был найден");;
    }

}

void methods::on_pushButton_3_clicked()
{
    this->close();
}
