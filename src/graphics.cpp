#include "graphics.h"
#include "ui_graphics.h"


graphics::graphics(QWidget *parent) : // Окно построения графика
    QDialog(parent),
    ui(new Ui::graphics)
{
    ui->setupUi(this);
    ui->widget->yAxis->setLabel("Уровень, дБм");
    ui->widget->xAxis->setLabel("Частота, МГц");
}
graphics::~graphics()
{
    delete ui;
}
void graphics::graphic_slot(QVector<double> a, QVector<double> b)
{
    height = 100;
    x = a;
    y = b;
    ui->widget->legend->setVisible(1);
    ui->widget->legend->setBrush(QBrush(QColor(255,255,255,230)));
    ui->widget->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
    ui->widget->xAxis->setRange(x.at(0), x.at(x.size()-1));
    for (int i = 0; i < y.size(); ++i)
    {
        if (y.at(i) > max)
            max = y.at(i);
        if (y.at(i) < min)
            min = y.at(i);
    }    
    ui->widget->addGraph();
    for (int i = 0; i < x.size(); ++i)
    {
        maxV.push_back(max);
        ui->widget->graph(0)->setName("По уровню несущей");
    }

    ui->widget->graph(0)->addData(x, maxV);

    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->yAxis->setRange(min-3, max+3);
    ui->widget->addGraph();
    ui->widget->graph(1)->addData(x, y);
    ui->widget->graph(1)->setName("Спектрограмма");
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->widget->replot();
}

void graphics::on_pushButton_clicked()
{
    this->close();
}

void graphics::on_radioButton_clicked()
{
    ui->lineEdit->setEnabled(0);
    ui->lineEdit->clear();
    maxV.clear();
    height = 100;
    for (int i = 0; i < x.size(); ++i)
    {
        maxV.push_back(max);
        ui->widget->graph(0)->setName("По уровню несущей");
    }
    ui->widget->graph(0)->setData(x, maxV);
    ui->widget->replot();
}

void graphics::on_radioButton_2_clicked()
{
    ui->lineEdit->setEnabled(1);
}

void graphics::on_lineEdit_textChanged(const QString &arg1)
{
    QString str = arg1;
    height = str.replace(",", ".").toDouble();
    maxV.clear();
    for (int i = 0; i < x.size(); ++i)
    {
        maxV.push_back(height);
        ui->widget->graph(0)->setName("По боковой полосе, смещение " + QString::number(height) + " дБм");
    }
    ui->widget->graph(0)->setData(x, maxV);
    ui->widget->replot();
}
