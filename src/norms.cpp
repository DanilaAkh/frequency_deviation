#include "norms.h"
#include "ui_norms.h"

Norms::Norms(QWidget *parent) : //Реализация справочника Норм
    QMainWindow(parent),
    ui(new Ui::Norms)
{
    ui->setupUi(this);


    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Создание базы данных
    db = QSqlDatabase::addDatabase("QSQLITE", "norms123");
    db.setDatabaseName("./Norms.db");
    if (db.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("not open");
    }

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE Norms(Norms TEXT, Path TEXT);");

    model = new QSqlTableModel(this, db);
    model->setTable("Norms");
    model->setHeaderData(0, Qt::Horizontal, tr("Нормы"));
    model->select();

    ui->tableView->setModel(model);
    model->removeColumn(1);
}
Norms::~Norms()
{
    db.close();
    db.removeDatabase("norms123");
    delete ui;
}
void Norms::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath(), "Все документы *.* ;; Файлы PDF"
                                                                                                " *.pdf ;; Документы Word *.doc ; *.docx");
    if (!(fileName.size()))
    {
        return;
    }
    model->insertRow(model->rowCount());
    query->prepare("INSERT INTO Norms (Norms, Path) "
            "VALUES (?, ?)");
    QStringList parts = fileName.split("/");
    QString lastBit = parts.at(parts.size()-1);
    query->addBindValue(lastBit);
    query->addBindValue(fileName);
    query->exec();
    model->select();
}
void Norms::on_pushButton_2_clicked()
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
void Norms::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}
void Norms::on_tableView_doubleClicked(const QModelIndex &index)
{
    query->exec("SELECT Norms, Path FROM Norms");
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
void Norms::on_pushButton_3_clicked()
{
    norms_17 = new Norms17(this);
    norms_17->show();
}
void Norms::on_pushButton_4_clicked()
{
    norms_19 = new Norms19(this);
    norms_19->show();
}

void Norms::on_pushButton_5_clicked()
{
    this->close();
}
