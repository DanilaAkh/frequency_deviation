#include "norms17.h"
#include "ui_norms17.h"

Norms17::Norms17(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Norms17)
{
    ui->setupUi(this);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Создание базы данных
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
    model = new QSqlTableModel(this, db);
    model->setTable("norms17_XX");
    model->setHeaderData(0, Qt::Horizontal, tr("Категория станции (ЕТС РЭС и ВЧУ)"));
    model->setHeaderData(1, Qt::Horizontal, tr("Начальная частота"));
    model->setHeaderData(2, Qt::Horizontal, tr("Конечная частота"));
    model->setHeaderData(3, Qt::Horizontal, tr("Размерность"));
    model->setHeaderData(4, Qt::Horizontal, tr("Абсолютная погрешность"));
    model->setHeaderData(5, Qt::Horizontal, tr("Относительная погрешность"));
    model->select();

    ui->tableView->setModel(model);    
}

Norms17::~Norms17()
{

    db.close();
    db.removeDatabase("norms17_XX");
    delete ui;
}

void Norms17::on_pushButton_2_clicked()//Кнопка добавить
{
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
    model->select();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_3->addItem(ui->comboBox_3->currentText());
    ui->comboBox_3->setCurrentIndex(0);
}

void Norms17::on_pushButton_3_clicked()//Кнопка удаления
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

void Norms17::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}


void Norms17::on_pushButton_clicked() //Кнопка очищения
{
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
}

void Norms17::on_pushButton_4_clicked() //Кнопка редактирования
{
    query->exec("SELECT * FROM norms17_XX");
    if (row == -1)
    {
        QMessageBox::warning(this, "Ошибка!", "Выберите нормы, которое необходимо редактировать!");
        return;
    }
    query->seek(row);
    ui->comboBox_3->setCurrentText(query->value(0).toString());
    ui->lineEdit_2->setText(query->value(1).toString());
    ui->lineEdit_4->setText(query->value(2).toString());
    if (query->value(4).toString() == "-")
    {
        ui->lineEdit_3->setText(query->value(5).toString());
        ui->comboBox->setCurrentIndex(0);
    }
    else
    {
        ui->lineEdit_3->setText(query->value(4).toString());
        ui->comboBox->setCurrentIndex(1);
    }
    if (query->value(3).toString() == "Гц")
        ui->comboBox_2->setCurrentIndex(0);
    else if (query->value(3).toString() == "кГц")
        ui->comboBox_2->setCurrentIndex(1);
    else
        ui->comboBox_2->setCurrentIndex(2);
    model->removeRow(row);
    model->select();
    row = -1;
}
