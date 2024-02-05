#include "res.h"
#include "ui_res.h"
RES::RES(QWidget *parent) : //Реализация окна "измерение технических параметров РЭС"
    QMainWindow(parent),
    ui(new Ui::RES)
{
    ui->setupUi(this);
    //установление индексов комбобоксов на 0 позицию и блокировка вкладок при создании окна
    ui->tabWidget->setCurrentIndex(0);
    ui->comboBox_4->setCurrentIndex(0);
    ui->comboBox_7->setCurrentIndex(2);
    ui->comboBox_3->setCurrentIndex(0);
    ui->comboBox_9->setCurrentIndex(1);
    ui->tabWidget->setTabEnabled(0, false);
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);
    ui->tabWidget->setTabEnabled(3, false);
    ui->tab->setEnabled(1);
    ui->tab_2->setEnabled(1);
    ui->tab_3->setEnabled(1);
    ui->tab_4->setEnabled(1);

    db = QSqlDatabase::addDatabase("QSQLITE", "norms19_XX");
    db.setDatabaseName("./norms19_XX.db");
    if (db.open())
        qDebug("open");
    else
        qDebug("not open");

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE norms19_XX(emission_class TEXT, koef_vk TEXT, koef_v40 TEXT, koef_v50 TEXT, koef_v60 TEXT);");

    query->exec("SELECT emission_class, koef_vk, koef_v40, koef_v50, koef_v60 FROM norms19_XX");
    while (query->next())
    {
        ui->comboBox_6->addItem(query->value(0).toString());
    }

    db.close();
    db.removeDatabase("norms19_XX");

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
        if (!uniqueSet.contains(query->value(0).toString()))
        {
            ui->comboBox_2->addItem(query->value(0).toString());
            uniqueSet.insert(query->value(0).toString());
        }
    }
    db.close();
    db.removeDatabase("norms17_XX");

    db = QSqlDatabase::addDatabase("QSQLITE", "new123");
    db.setDatabaseName("./equipment.db");
    if (db.open())
        qDebug("open");
    else
        qDebug("not open");

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE equipment(type_ts TEXT, kind_ts TEXT, manufac TEXT, year TEXT, serial_num TEXT, date TEXT, inverter_num TEXT, place TEXT,"
                "subdivision TEXT, num_certifi TEXT, date_verific TEXT, stability FLOAT);");
    query->exec("SELECT type_ts FROM equipment");
    while (query->next())
    {
        ui->comboBox_8->addItem(query->value(0).toString());
    }
    db.close();
    db.removeDatabase("new123");

}
RES::~RES()
{
    delete ui;
}
//функция для получения размерности (Гц, кГц, МГц)
int RES::razmernost(int index)
{
    int result = 1;
    if (index == 0)    
        result = 1;
    else if (index == 1)
        result = 1000;
    else
        result = 1000000;
    return result;
}
//Обработка кнопки "далее"
void RES::on_pushButton_2_clicked()
{
    if (curIndex == 3)
        return;
    ui->tabWidget->setCurrentIndex(++curIndex);
}
//Обработка кнопки "назад"
void RES::on_pushButton_clicked()
{
    if (curIndex == 0)
        return;
    ui->tabWidget->setCurrentIndex(--curIndex);
}
//Обработка чекбокса группбокса
void RES::on_groupBox_clicked()
{
    if (!(ui->groupBox->isChecked()))
    {
        ui->groupBox_3->setEnabled(1);        
        if (ui->comboBox_3->currentIndex() == 0)
            ui->comboBox_4->setEnabled(0);
        ui->pushButton_5->setEnabled(1);
        ui->label_26->setEnabled(1);
        ui->lineEdit_4->setEnabled(1);
        ui->comboBox_5->setEnabled(1);
    }
    else
    {
        ui->comboBox->setEnabled(1);
        ui->comboBox_2->setEnabled(1);
        ui->groupBox_3->setEnabled(0);
    }
}
//Обработка чекбокса группбокса2
void RES::on_groupBox_2_clicked()
{
    if (!(ui->groupBox_2->isChecked()))
    {
        ui->checkBox_2->setEnabled(1);
        ui->label_23->setEnabled(1);
        ui->lineEdit_3->setEnabled(1);
        ui->lineEdit_21->setEnabled(1);
        ui->lineEdit_22->setEnabled(1);
        ui->lineEdit_23->setEnabled(1);
        ui->lineEdit_24->setEnabled(1);
        ui->label_4->setEnabled(1);
        ui->label_5->setEnabled(1);
        ui->label_6->setEnabled(1);
        ui->groupBox_7->setEnabled(1);
        ui->comboBox_10->setEnabled(1);
        ui->label_18->setEnabled(1);
        ui->label_24->setEnabled(1);
        ui->label_25->setEnabled(1);
    }
    else
    {
        ui->label_23->setEnabled(0);
        ui->lineEdit_21->setEnabled(0);
        ui->lineEdit_22->setEnabled(0);
        ui->lineEdit_23->setEnabled(0);
        ui->lineEdit_24->setEnabled(0);
        ui->label_5->setEnabled(0);
        ui->label_6->setEnabled(0);
        ui->label_18->setEnabled(0);
        ui->label_24->setEnabled(0);
        ui->label_25->setEnabled(0);
    }
}
//отправка сигнала для открытия окна Норм
void RES::on_pushButton_5_clicked()
{
    emit signal_form();
}
//Обработка чекбокса группбокса5
void RES::on_groupBox_5_clicked()
{
    if (!(ui->groupBox_5->isChecked()))
    {
        ui->label_7->setEnabled(1);
        ui->lineEdit_6->setEnabled(1);
        ui->comboBox_7->setEnabled(1);
        ui->label_39->setEnabled(1);
        ui->lineEdit_19->setEnabled(1);
        ui->comboBox_9->setEnabled(1);
    }
    else
    {
        ui->label_7->setEnabled(0);
        ui->lineEdit_6->setEnabled(0);
        ui->comboBox_7->setEnabled(0);
        ui->label_39->setEnabled(0);
        ui->lineEdit_19->setEnabled(0);
        ui->comboBox_9->setEnabled(0);
    }
}
//обработка чекбокса "Ручной ввод"
void RES::on_checkBox_clicked()
{
    if (!(ui->checkBox->isChecked()))
    {
        ui->comboBox_8->setEnabled(1);
        ui->label_31->setEnabled(0);
        ui->label_12->setEnabled(0);
        ui->lineEdit_7->setEnabled(0);
        ui->lineEdit_27->setEnabled(0);

    }
    else
    {
        ui->comboBox_8->setEnabled(0);
        ui->label_31->setEnabled(1);
        ui->label_12->setEnabled(1);
        ui->lineEdit_7->setEnabled(1);
        ui->lineEdit_27->setEnabled(1);
    }
}
//расчет допустимых погрешностей
void RES::on_pushButton_6_clicked()
{
    float razresh_freq = 0;    
    int razmern_cb5 = 1;
    int razmern_cb4 = 1;
    int razmern_cb10 = 1;
    float NSPC = 0;
    float KSPC, KSPC40, KSPC50, KSPC60 = 0;
    razmern_cb4 = razmernost(ui->comboBox_4->currentIndex());
    razmern_cb5 = razmernost(ui->comboBox_5->currentIndex());
    razresh_freq = ui->lineEdit_4->text().replace(",", ".").toDouble() * razmern_cb5;

    if (ui->comboBox_3->currentIndex() == 0)
    {
        N = ui->lineEdit->text().replace(",", ".").toDouble() * razresh_freq / 1000000;
    }
    else
    {
        N = ui->lineEdit->text().replace(",", ".").toDouble() * razmern_cb4; //Расчет N
    }

    double result1 = (razresh_freq - N);
    double result2 = (razresh_freq + N);
    switch (ui->comboBox_4->currentIndex())
    {
    case 0:
        ui->label_22->setText("Гц");
        break;
    case 1:
        ui->label_22->setText("кГц");
        result1 = result1 / 1000;
        result2 = result2 / 1000;
        break;
    case 2:
        ui->label_22->setText("МГц");
        result1 = result1 / 1000000;
        result2 = result2 / 1000000;
        break;
    }
    ui->lineEdit_17->setText(QString::number(result1, 'f', 2));
    ui->lineEdit_20->setText(QString::number(result2, 'f', 2));

    razmern_cb10 = razmernost(ui->comboBox_10->currentIndex());
    NSPC = ui->lineEdit_3->text().replace(",", ".").toDouble() * razmern_cb10;
    KSPC = ui->lineEdit_21->text().replace(",", ".").toDouble();
    KSPC40 = ui->lineEdit_22->text().replace(",", ".").toDouble();
    KSPC50 = ui->lineEdit_23->text().replace(",", ".").toDouble();
    KSPC60 = ui->lineEdit_24->text().replace(",", ".").toDouble();
    float result3 = NSPC * KSPC;
    float result4 = NSPC * KSPC40;
    float result5 = NSPC * KSPC50;
    float result6 = NSPC * KSPC60;
    float result7 = result3 * 0.2 + result3;
    float result40 = result4 * 0.2 + result4;
    float result50 = result5 * 0.2 + result5;
    float result60 = result6 * 0.2 + result6;
    switch (ui->comboBox_10->currentIndex())
    {
    case 0:
        ui->label_6->setText(" Гц");
        ui->label_32->setText(" Гц");
        ui->label_36->setText(" Гц");
        ui->label_37->setText(" Гц");
        if (ui->checkBox_2->isChecked())
        {
            ui->label_49->setText("Гц");
            ui->label_57->setText("Гц");
            ui->label_59->setText("Гц");
            ui->label_61->setText("Гц");
        }
        break;
    case 1:
        ui->label_6->setText(" кГц");
        ui->label_32->setText(" кГц");
        ui->label_36->setText(" кГц");
        ui->label_37->setText(" кГц");
        if (ui->checkBox_2->isChecked())
        {
            ui->label_49->setText("кГц");
            ui->label_57->setText("кГц");
            ui->label_59->setText("кГц");
            ui->label_61->setText("кГц");
        }
        result3 = result3 / 1000;
        result4 = result4 / 1000;
        result5 = result5 / 1000;
        result6 = result6 / 1000;
        result7 = result7 / 1000;
        result40 = result40 / 1000;
        result50 = result50 / 1000;
        result60 = result60 / 1000;
        break;
    case 2:
        ui->label_6->setText(" МГц");
        ui->label_32->setText(" МГц");
        ui->label_36->setText(" МГц");
        ui->label_37->setText(" МГц");
        if (ui->checkBox_2->isChecked())
        {
            ui->label_49->setText("МГц");
            ui->label_57->setText("МГц");
            ui->label_59->setText("МГц");
            ui->label_61->setText("МГц");
        }
        result3 = result3 / 1000000;
        result4 = result4 / 1000000;
        result5 = result5 / 1000000;
        result6 = result6 / 1000000;
        result7 = result7 / 1000000;
        result40 = result40 / 1000000;
        result50 = result50 / 1000000;
        result60 = result60 / 1000000;
    }
    ui->lineEdit_18->setText(QString::number(result3));
    ui->lineEdit_28->setText(QString::number(result4));
    ui->lineEdit_30->setText(QString::number(result5));
    ui->lineEdit_29->setText(QString::number(result6));
    if (ui->checkBox_2->isChecked()) //ГОСТ + 20%
    {
        ui->lineEdit_38->setText(QString::number(result7, 'f', 2));
        ui->lineEdit_41->setText(QString::number(result40, 'f', 2));
        ui->lineEdit_42->setText(QString::number(result50, 'f', 2));
        ui->lineEdit_43->setText(QString::number(result60, 'f', 2));
    }

}
void RES::on_comboBox_3_currentIndexChanged(int index)
{
    if (index == 1)
    {
        ui->comboBox_4->setEnabled(1);
    }
    else
    {
        ui->comboBox_4->setEnabled(0);
    }
}
void RES::on_pushButton_3_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath()," SPA файлы *.spa"); //получение пути к файлу для постройки спектра
    ui->lineEdit_31->setText(fileName);
}
void RES::on_pushButton_7_clicked()// кнопка сохранения
{
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
    QString strs[] = {ui->lineEdit_6->text(), ui->lineEdit_39->text(), ui->comboBox_6->currentText(),
                      ui->lineEdit_19->text(), ui->lineEdit_40->text(), ui->lineEdit_28->text(), ui->lineEdit_30->text(), ui->lineEdit_20->text(),
                      ui->lineEdit_5->text(), ui->lineEdit_25->text(), ui->lineEdit_26->text(), ui->dateEdit->text()
                     };
    query->prepare("INSERT INTO archive(centre_freq, abs_center_err, emi_class ,KSPC, KSPC_error, KSPC_40, KSPC_50, KSPC_60, "
                   "type_RES, net_name, place, date) "
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    for  (int i = 0 ; i < 12; ++i)
    {
        query->addBindValue(strs[i]);
    }
    query->exec();


    db.close();
    db.removeDatabase("archive123");
}
void RES::on_pushButton_10_clicked()
{
    emit signal_form2(); //отправка сигнала для открытия реестра РКО
}
void RES::on_pushButton_4_clicked()
{
    QFile file(fileName);
    if (!(file.open(QFile::ReadOnly | QFile::Text))) //проверка на открытие файла
    {
        QMessageBox::warning(this, "Ошибка!", "Не удалось открыть файл!");
        return;
    }
    QString SPAN = "SPAN";
    QString RBW = "RBW";
    QString datap = "UI_DATA_POINTS";
    QString trace_c = "# Begin TRACE C Data"; //строка для поиска необходимой в файле
    QTextStream in(&file);
    QString grap;
    while(!in.atEnd())
    {
        bool a = true;
        QString str = in.readLine();
        for (int i = 0; i < SPAN.size(); i++)
        {
            if (!(str[i] == SPAN[i]))
                a = false;
        }
        if (a) //выполнения алгоритма при нахождении необходимой строки
        {
            QStringList parts;
            parts = str.split("=");
            SPAN = parts.at(1);
            ui->lineEdit_8->setText(SPAN);
            break;
        }
    }
    while(!in.atEnd())
    {
        bool a = true;
        QString str = in.readLine();
        for (int i = 0; i < RBW.size(); i++)
        {
            if (!(str[i] == RBW[i]))
                a = false;
        }
        if (a) //выполнения алгоритма при нахождении необходимой строки
        {
            QStringList parts;
            parts = str.split("=");
            RBW = parts.at(1);
            ui->lineEdit_9->setText(RBW);
            break;
        }
    }
    while(!in.atEnd())
    {
        bool a = true;
        QString str = in.readLine();
        for (int i = 0; i < datap.size(); i++)
        {
            if (!(str[i] == datap[i]))
                a = false;
        }
        if (a) //выполнения алгоритма при нахождении необходимой строки
        {
            QStringList parts;
            parts = str.split("=");
            datap = parts.at(1);
            ui->lineEdit_27->setText(datap);
            break;
        }
    }
    while(!in.atEnd())
    {
        bool a = true;
        QString str = in.readLine();
        for (int i = 0; i < trace_c.size(); i++)
        {
            if (!(str[i] == trace_c[i]))
                a = false;
        }
        if (a) //выполнения алгоритма при нахождении необходимой строки
        {
            QStringList parts;
            QString first_num;
            QString second_num;
            QString temp;
            for (int j = 0; j < 551; ++j) //обработка строк с полученными точками
            {
                grap = in.readLine();
                grap += "\n";
                parts = grap.split(" , ");
                first_num = parts.at(parts.size() - 2);
                second_num = parts.at(parts.size() - 1);
                parts = first_num.split("=");
                temp = parts.at(parts.size() - 1);
                y.push_back(temp.toDouble());
                parts = second_num.split(" ");
                temp = parts.at(parts.size() - 2);
                x.push_back(temp.toDouble());
            }
            break;
        }
    }
    //расчет центральной частоты и КШПЧ
    double max_value;
    int max_value_iterator;
    if (height == 100)
    {
        max_value = -300;
        for (int i = 0; i < y.size(); ++i)
        {
            if (y.at(i) > max_value)
            {
                max_value = y.at(i);
                max_value_iterator = i;
            }
        }
    }
    else
    {
        double temp = fabs(y.at(0));
        max_value = height;
        for (int i = 1; i < y.size() - 1; ++i)
        {
            if(fabs(max_value - y.at(i)) < temp)
            {
                temp = fabs(max_value - y.at(i));
                max_value_iterator = i;
            }
        }
    }
    int left_item, right_item = 0;
    double left_num = fabs(y.at(0));
    double right_num = fabs(max_value_iterator);

    for (int i = 1; i < max_value_iterator; ++i)
    {
        if(fabs((max_value - 30) - y.at(i)) < left_num)
        {
            left_num = fabs((max_value - 30) - y.at(i));
            left_item = i;
        }
    }
    for (int i = max_value_iterator + 1; i < y.size() - 1; ++i)
    {
        if(fabs((max_value - 30) - y.at(i)) < right_num)
        {
            right_num = fabs((max_value - 30) - y.at(i));
            right_item = i;
        }
    }
    ui->lineEdit_6->setText(QString::number(((x.at(right_item) + x.at(left_item)) / 2), 'f', 8));
    ui->lineEdit_19->setText(QString::number(((x.at(right_item) - x.at(left_item)) * 1000), 'f', 8));
    x.clear();
    y.clear();
    file.close();
}
void RES::on_pushButton_9_clicked()
{
    QFile file(fileName);
    if (!(file.open(QFile::ReadOnly | QFile::Text))) //проверка на открытие файла
    {
        QMessageBox::warning(this, "Ошибка!", "Не удалось открыть файл!");
        return;
    }
    QString trace_c = "# Begin TRACE C Data"; //строка для поиска необходимой в файле
    QTextStream in(&file);
    QString grap;
    while(!in.atEnd())
    {
        bool a = true;
        QString str = in.readLine();
        for (int i = 0; i < trace_c.size(); i++)
        {
            if (!(str[i] == trace_c[i]))            
                a = false;
        }
        if (a) //выполнения алгоритма при нахождении необходимой строки
        {
            QStringList parts;
            QString first_num;
            QString second_num;
            QString temp;
            for (int j = 0; j < 551; ++j) //обработка строк с полученными точками
            {
                grap = in.readLine();
                grap += "\n";
                parts = grap.split(" , ");
                first_num = parts.at(parts.size() - 2);
                second_num = parts.at(parts.size() - 1);
                parts = first_num.split("=");
                temp = parts.at(parts.size() - 1);
                y.push_back(temp.toDouble());
                parts = second_num.split(" ");
                temp = parts.at(parts.size() - 2);
                x.push_back(temp.toDouble());
            }
            break;
        }
    }
    graphic = new graphics(this); //создание окна с графиком и отправка точек сигналом
    graphic->show();
    connect(this, &RES::signal_graphics, graphic, &graphics::graphic_slot);
    emit signal_graphics(x, y);
    x.clear();
    y.clear();
    file.close();
}
void RES::on_pushButton_12_clicked() //кнопка очистки на 1 вкладке
{
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_4->setCurrentIndex(0);
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_3->clear();
    ui->lineEdit_17->clear();
    ui->lineEdit_20->clear();
    ui->lineEdit_18->clear();
    ui->lineEdit_38->clear();
    ui->lineEdit_21->clear();
    ui->lineEdit_22->clear();
    ui->lineEdit_23->clear();
    ui->lineEdit_28->clear();
    ui->lineEdit_29->clear();
    ui->lineEdit_30->clear();
    ui->lineEdit_24->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit->clear();
    ui->comboBox_5->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    ui->comboBox_6->setCurrentIndex(0);
    ui->comboBox_10->setCurrentIndex(0);
    ui->checkBox_2->setChecked(0);
    ui->label_6->clear();
    ui->label_22->clear();
    ui->label_49->clear();
    ui->label_32->clear();
    ui->label_36->clear();
    ui->label_37->clear();
}
void RES::on_checkBox_2_clicked() //очистка ГОСТ + 20% при отжатой галочке
{
    if (!ui->checkBox_2->isChecked())
    {
        ui->label_49->clear();
        ui->lineEdit_38->clear();
    }
}
void RES::on_pushButton_13_clicked() //очистка "расчета погрешности" (вторая вкладка)
{
    ui->comboBox_8->setCurrentIndex(0);
    fileName = "";
    x.clear();
    y.clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_31->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_19->clear();
    ui->lineEdit_10->setText("0.005");
    ui->lineEdit_11->setText("0.1");
    ui->lineEdit_27->clear();
    ui->lineEdit_39->clear();
    ui->lineEdit_40->clear();
    ui->comboBox_7->setCurrentIndex(0);
    ui->comboBox_9->setCurrentIndex(0);
}
void RES::on_pushButton_11_clicked() //кнопка расчета погрешностей и детализации
{
    double izm_center_freq = 0;
    double KSPC = 0;
    double stability_gen = 0;
    double SPAN = 0;
    double RBW = 0;
    double k1 = 0;
    double k2 = 0;
    double k3 = 0;
    double sigma_1_cf, sigma_1_kspc = 0;
    double sigma_2_cf, sigma_2_kspc = 0;
    double sigma_3_cf, sigma_3_kspc = 0;
    double sigma_abs_cf, sigma_abs_kspc = 0;
    double sigma_otn_cf, sigma_otn_kspc = 0;
    int razmernost_cb7 = 1;
    int razmernost_cb9 = 1;
    //расчет погрешности центральной ширины полосы и КШПЧ по новой формуле
    razmernost_cb9 = razmernost(ui->comboBox_9->currentIndex());
    razmernost_cb7 = razmernost(ui->comboBox_7->currentIndex());
    izm_center_freq = razmernost_cb7 * ui->lineEdit_6->text().replace(",", ".").toDouble();
    KSPC = ui->lineEdit_19->text().replace(",", ".").toFloat() * razmernost_cb9;    
    stability_gen = ui->lineEdit_7->text().replace(",", ".").toDouble();
    k3 = ui->lineEdit_27->text().replace(",", ".").toDouble();
    SPAN = ui->lineEdit_9->text().replace(",", ".").toFloat();
    RBW = ui->lineEdit_8->text().replace(",", ".").toFloat();
    k1 = ui->lineEdit_10->text().replace(",", ".").toFloat();
    k2 = ui->lineEdit_11->text().replace(",", ".").toFloat();
    if (use_new_formula)
    {
        sigma_1_cf = stability_gen * izm_center_freq;
        sigma_2_cf = k1 * SPAN + SPAN / k3;
        sigma_3_cf = RBW * k2;
        sigma_1_kspc = stability_gen * KSPC;
        sigma_2_kspc = k1 * SPAN + SPAN / k3;
        sigma_3_kspc = RBW * k2;
        sigma_abs_cf = sqrt(pow(sigma_1_cf, 2) + pow(sigma_2_cf, 2) + pow(sigma_3_cf, 2));
        sigma_abs_kspc = sqrt(pow(sigma_1_kspc, 2) + pow(sigma_2_kspc, 2) + pow(sigma_3_kspc, 2));
        sigma_otn_cf = sigma_abs_cf / izm_center_freq;
        sigma_otn_kspc = sigma_abs_kspc / KSPC;
    }
    else
    {
        sigma_abs_kspc = 2 * (k1 * SPAN + (SPAN / k3) + k2 * RBW + 0.000001);
        sigma_abs_cf = (stability_gen * izm_center_freq + k1 * SPAN + (SPAN / k3) + k2 + 0.000001);
    }
    switch (ui->comboBox_7->currentIndex())
    {
    case 0:
        sigma_abs_cf = sigma_abs_cf / 1;
        ui->label_47->setText("Гц");
        ui->label_53->setText("Гц - границы неисключенной систематической погрешности средств измерений частоты");
        ui->label_54->setText("Гц - границы неисключенной систематической погрешности частоты, обусловленной дискретизацией частоты");
        ui->label_51->setText("Гц - границы неисключенной систематической погрешности измерений, обусловленной шириной полосы пропускания\nфильтров.");
        ui->label_55->setText("Гц - относительное значение результирующей границы неисключенной систематической погрешности измерений.");
        ui->label_52->setText("Гц - результирующая граница неисключенной систематической погрешности измерений.");
        break;
    case 1:
        sigma_abs_cf = sigma_abs_cf / 1000;
        ui->label_47->setText("кГц");
        ui->label_53->setText("кГц - границы неисключенной систематической погрешности средств измерений частоты");
        ui->label_54->setText("кГц - границы неисключенной систематической погрешности частоты, обусловленной дискретизацией частоты");
        ui->label_51->setText("кГц - границы неисключенной систематической погрешности измерений, обусловленной шириной полосы пропускания\nфильтров.");
        ui->label_55->setText("кГц - относительное значение результирующей границы неисключенной систематической погрешности измерений.");
        ui->label_52->setText("кГц - результирующая граница неисключенной систематической погрешности измерений.");
        break;
    case 2:
        sigma_abs_cf = sigma_abs_cf / 1000000;
        ui->label_47->setText("МГц");
        ui->label_53->setText("МГц - границы неисключенной систематической погрешности средств измерений частоты");
        ui->label_54->setText("МГц - границы неисключенной систематической погрешности частоты, обусловленной дискретизацией частоты");
        ui->label_51->setText("МГц - границы неисключенной систематической погрешности измерений, обусловленной шириной полосы пропускания\nфильтров.");
        ui->label_55->setText("МГц - относительное значение результирующей границы неисключенной систематической погрешности измерений.");
        ui->label_52->setText("МГц - результирующая граница неисключенной систематической погрешности измерений.");
        break;
    }
    switch (ui->comboBox_9->currentIndex())
    {
    case 0:
        sigma_abs_kspc = sigma_abs_kspc / 1;
        ui->label_48->setText("Гц");
        ui->label_40->setText("Гц - границы неисключенной систематической погрешности средств измерений частоты");
        ui->label_42->setText("Гц - границы неисключенной систематической погрешности частоты, обусловленной дискретизацией частоты");
        ui->label_41->setText("Гц - границы неисключенной систематической погрешности измерений, обусловленной шириной полосы пропускания\nфильтров.");
        ui->label_43->setText("Гц - относительное значение результирующей границы неисключенной систематической погрешности измерений.");
        ui->label_44->setText("Гц - результирующая граница неисключенной систематической погрешности измерений.");
        break;
    case 1:
        sigma_abs_kspc = sigma_abs_kspc / 1000;
        ui->label_48->setText("кГц");
        ui->label_40->setText("кГц - границы неисключенной систематической погрешности средств измерений частоты");
        ui->label_42->setText("кГц - границы неисключенной систематической погрешности частоты, обусловленной дискретизацией частоты");
        ui->label_41->setText("кГц - границы неисключенной систематической погрешности измерений, обусловленной шириной полосы пропускания\nфильтров.");
        ui->label_43->setText("кГц - относительное значение результирующей границы неисключенной систематической погрешности измерений.");
        ui->label_44->setText("кГц - результирующая граница неисключенной систематической погрешности измерений.");
        break;
    case 2:
        sigma_abs_kspc = sigma_abs_kspc / 1000000;
        ui->label_48->setText("МГц");
        ui->label_40->setText("МГц - границы неисключенной систематической погрешности средств измерений частоты");
        ui->label_42->setText("МГц - границы неисключенной систематической погрешности частоты, обусловленной дискретизацией частоты");
        ui->label_41->setText("МГц - границы неисключенной систематической погрешности измерений, обусловленной шириной полосы пропускания\nфильтров.");
        ui->label_43->setText("МГц - относительное значение результирующей границы неисключенной систематической погрешности измерений.");
        ui->label_44->setText("МГц - результирующая граница неисключенной систематической погрешности измерений.");
        break;
    }

    //запись погрешности измеренной центральной частоты
    if (use_new_formula)
    {
        ui->lineEdit_12->setText(QString::number(sigma_1_cf, 'f', 12));
        ui->lineEdit_13->setText(QString::number(sigma_2_cf, 'f', 12));
        ui->lineEdit_14->setText(QString::number(sigma_3_cf, 'f', 12));
        ui->lineEdit_16->setText(QString::number(sigma_otn_cf, 'f', 12));
    }
    ui->lineEdit_15->setText(QString::number(sigma_abs_cf, 'f', 12));
    ui->lineEdit_39->setText(QString::number(sigma_abs_cf, 'f', 8));
    //Запись погрешности КШПЧ
    if (use_new_formula)
    {
        ui->lineEdit_34->setText(QString::number(sigma_otn_kspc, 'f', 12));
        ui->lineEdit_36->setText(QString::number(sigma_1_kspc, 'f', 12));
        ui->lineEdit_35->setText(QString::number(sigma_2_kspc, 'f', 12));
        ui->lineEdit_32->setText(QString::number(sigma_3_kspc, 'f', 12));
    }
    ui->lineEdit_40->setText(QString::number(sigma_abs_kspc, 'f', 8));
    ui->lineEdit_33->setText(QString::number(sigma_abs_kspc, 'f', 12));
}
void RES::on_pushButton_14_clicked() //очистка окна детализации
{
    ui->lineEdit_12->clear();
    ui->lineEdit_13->clear();
    ui->lineEdit_14->clear();
    ui->lineEdit_16->clear();
    ui->lineEdit_15->clear();
    ui->lineEdit_36->clear();
    ui->lineEdit_35->clear();
    ui->lineEdit_32->clear();
    ui->lineEdit_34->clear();
    ui->lineEdit_33->clear();
}
void RES::on_pushButton_15_clicked() //Очистка окна сохранения
{
    ui->lineEdit_5->clear();
    ui->lineEdit_25->clear();
    ui->lineEdit_26->clear();
    QDate date;
    date.setDate(2023,1,1);
    ui->dateEdit->setDate(date);
}

void RES::on_radioButton_2_clicked()
{
    if (ui->radioButton_2->isChecked())
    {
        ui->lineEdit_2->setEnabled(1);
        height = ui->lineEdit_2->text().toDouble();
    }
}

void RES::on_radioButton_clicked()
{
    if (ui->radioButton->isChecked())
    {
        ui->lineEdit_2->setEnabled(0);
        ui->lineEdit_2->clear();
        height = 100;
    }
}

void RES::on_comboBox_6_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Класс излучения")
    {
        ui->lineEdit_21->clear();
        ui->lineEdit_22->clear();
        ui->lineEdit_23->clear();
        ui->lineEdit_24->clear();
        return;
    }
    db = QSqlDatabase::addDatabase("QSQLITE", "norms19_XX");
    db.setDatabaseName("./norms19_XX.db");
    if (db.open())
        qDebug("open");
    else
        qDebug("not open");

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE norms19_XX(emission_class TEXT, koef_vk TEXT, koef_v40 TEXT, koef_v50 TEXT, koef_v60 TEXT);");

    query->exec("SELECT emission_class, koef_vk, koef_v40, koef_v50, koef_v60 FROM norms19_XX");
    while (query->next())
    {
        if (query->value(0).toString() == arg1)
        {
            ui->lineEdit_21->setText(query->value(1).toString());
            ui->lineEdit_22->setText(query->value(2).toString());
            ui->lineEdit_23->setText(query->value(3).toString());
            ui->lineEdit_24->setText(query->value(4).toString());
        }
    }
    db.close();
    db.removeDatabase("norms19_XX");
}

void RES::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    ui->comboBox->clear();
    ui->comboBox->addItem("Полоса радиочастот РЭС");
    if (arg1 == "Категория станции (ЕТС РЭС и ВЧУ)")
        return;
    db = QSqlDatabase::addDatabase("QSQLITE", "norms17_XX");
    db.setDatabaseName("./norms17_XX.db");
    if (db.open())
        qDebug("open");
    else
        qDebug("not open");
    query = new QSqlQuery(db);
    query->exec("CREATE TABLE norms17_XX(ETC TEXT, start_freq TEXT, stop_freq TEXT, razmermost TEXT, abs_error TEXT, otn_error TEXT);");
    query->exec("SELECT * FROM norms17_XX");
    while (query->next())
    {
        if (query->value(0).toString() == arg1)
            ui->comboBox->addItem(query->value(1).toString() + "-" + query->value(2).toString() + " " + query->value(3).toString());
    }
    db.close();
    db.removeDatabase("norms17_XX");
}

void RES::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "Полоса радиочастот РЭС")
    {
        ui->comboBox_3->setCurrentIndex(0);
        ui->comboBox_4->setCurrentIndex(0);
        ui->lineEdit->clear();
        return;
    }
    db = QSqlDatabase::addDatabase("QSQLITE", "norms17_XX");
    db.setDatabaseName("./norms17_XX.db");
    if (db.open())
        qDebug("open");
    else
        qDebug("not open");
    query = new QSqlQuery(db);
    query->exec("CREATE TABLE norms17_XX(ETC TEXT, start_freq TEXT, stop_freq TEXT, razmermost TEXT, abs_error TEXT, otn_error TEXT);");
    query->exec("SELECT * FROM norms17_XX");
    while (query->next())
    {
        QStringList fparts = arg1.split("-");
        if (fparts.size() == 1)
            return;
        QStringList sparts = fparts.at(1).split(" ");
        if (query->value(1).toString() == fparts.at(0) && query->value(2).toString() == sparts.at(0) && query->value(3).toString() == sparts.at(1))
        {
            if (query->value(3).toString() == "Гц")
                ui->comboBox_4->setCurrentIndex(0);
            else if (query->value(3).toString() == "кГц")
                ui->comboBox_4->setCurrentIndex(1);
            else
                ui->comboBox_4->setCurrentIndex(2);
            if (query->value(4).toString() == "-")
            {
                ui->comboBox_3->setCurrentIndex(0);
                ui->lineEdit->setText(query->value(5).toString());
            }
            else
            {
                ui->lineEdit->setText(query->value(4).toString());
                ui->comboBox_3->setCurrentIndex(1);
            }
        }
    }

    db.close();
    db.removeDatabase("norms17_XX");
}


void RES::on_lineEdit_2_textChanged(const QString &arg1)
{
    QString str = arg1;
    height = -fabs(str.replace(",", ".").toDouble());
}

void RES::on_pushButton_8_clicked()
{
    this->close();
}

void RES::Slot_formula(bool value)
{
    if (value)
    {
        use_new_formula = true;
        qDebug("новая формула");
    }
    else
    {
        use_new_formula = false;
        qDebug("старая формула");
    }
}
