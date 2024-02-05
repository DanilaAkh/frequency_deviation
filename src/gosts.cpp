#include "gosts.h"
#include "ui_gosts.h"

GOSTs::GOSTs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GOSTs)
{
    ui->setupUi(this);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Создание базы данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./gosts.db");
    if (db.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("not open");
    }

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE Gosts(Gosts TEXT, Path TEXT);");

    model = new QSqlTableModel(this, db);
    model->setTable("Gosts");
    model->setHeaderData(0, Qt::Horizontal, tr("ГОСТы"));
    model->select();

    ui->tableView->setModel(model);
    model->removeColumn(1);
}

GOSTs::~GOSTs()
{
    delete ui;
}

void GOSTs::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath(), "Все документы *.* ;; Файлы PDF"
                                                                                                " *.pdf ;; Документы Word *.doc ; *.docx");

    if (!(fileName.size()))
    {
        return;
    }

    model->insertRow(model->rowCount());

    query->prepare("INSERT INTO Gosts (Gosts, Path) "
            "VALUES (?, ?)");
    QStringList parts = fileName.split("/");
    QString lastBit = parts.at(parts.size()-1);

    query->addBindValue(lastBit);
    query->addBindValue(fileName);
    query->exec();
    model->select();
}

void GOSTs::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

void GOSTs::on_pushButton_clicked()
{
    if (row == -1)
    {
        QMessageBox::warning(this, "Ошибка!", "Выберите ГОСТ, который необходимо удалить!");
        return;
    }
    model->removeRow(row);
    model->select();
    row = -1;
}

void GOSTs::on_tableView_doubleClicked(const QModelIndex &index)
{
    //QMessageBox::information(this, "hello", "hello");
    query->exec("SELECT Gosts, Path FROM Gosts");
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

void GOSTs::on_pushButton_3_clicked()
{
    this->close();
}
