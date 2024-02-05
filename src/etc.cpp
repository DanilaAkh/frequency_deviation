#include "etc.h"
#include "ui_etc.h"

ETC::ETC(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ETC)
{
    ui->setupUi(this);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Создание базы данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./ETC.db");
    if (db.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("not open");
    }

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE ETC(ETC TEXT, Path TEXT);");

    model = new QSqlTableModel(this, db);
    model->setTable("ETC");
    model->setHeaderData(0, Qt::Horizontal, tr("ETC"));
    model->select();

    ui->tableView->setModel(model);
    model->removeColumn(1);
}

ETC::~ETC()
{
    delete ui;
}

void ETC::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath(), "Все документы *.* ;; Файлы PDF"
                                                                                                " *.pdf ;; Документы Word *.doc ; *.docx");

    if (!(fileName.size()))
    {
        return;
    }

    model->insertRow(model->rowCount());

    query->prepare("INSERT INTO ETC (ETC, Path) "
            "VALUES (?, ?)");
    QStringList parts = fileName.split("/");
    QString lastBit = parts.at(parts.size()-1);

    query->addBindValue(lastBit);
    query->addBindValue(fileName);
    query->exec();
    model->select();
}

void ETC::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

void ETC::on_pushButton_2_clicked()
{
    if (row == -1)
    {
        QMessageBox::warning(this, "Ошибка!", "Выберите ЕТС РЭС И ВЧУ, который необходимо удалить!");
        return;
    }
    model->removeRow(row);
    model->select();
    row = -1;
}

void ETC::on_tableView_doubleClicked(const QModelIndex &index)
{
    query->exec("SELECT ETC, Path FROM ETC");
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

void ETC::on_pushButton_3_clicked()
{
    this->close();
}
