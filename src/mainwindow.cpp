#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_2_triggered() //открытие окна справочника методик
{
    met = new methods(this);
    met->show();
}

void MainWindow::on_action_8_triggered() //открытие окна настроек формул
{
    sets = new Settings(this);
    connect(sets, &Settings::signal_formula, this, &MainWindow::Slot_formula);
    sets->show();

}

void MainWindow::on_action_triggered() //открытие окна измерения технических параметров
{
    res = new RES(this);
    connect(res, &RES::signal_form, this, &MainWindow::Slot_form1);
    connect(res, &RES::signal_form2, this, &MainWindow::Slot_form2);
    connect(this, &MainWindow::signal_formula_to_res, res, &RES::Slot_formula);
    emit signal_formula_to_res(is_new_formula);
    res->show();
}

void MainWindow::on_action_6_triggered() //открытие окна реестра рко
{
    equip = new Equip(this);
    equip->show();
}

void MainWindow::on_action_4_triggered() // открытие окна справочника ГОСТов
{
    gosts = new GOSTs(this);
    gosts->show();
}

void MainWindow::Slot_form1() // Открытие окна справочника норм через сигнал с окна тех. параметров
{
    norms = new Norms(this);
    norms->show();
}

void MainWindow::Slot_form2() // Открытие окна реестра рко с окна тех. параметров
{
    equip = new Equip(this);
    equip->show();
}

void MainWindow::Slot_formula(bool formula)
{
    if (formula)
    {
        is_new_formula = true;
    }
    else
    {
        is_new_formula = false;
    }
}

void MainWindow::on_action_3_triggered() // Открытие окна справочника норм
{
    norms = new Norms(this);
    norms->show();
}

void MainWindow::on_action_9_triggered() // Открытие окна архива
{
    arch = new archive(this);
    arch->show();
}

void MainWindow::on_action_10_triggered() // Открытие окна о программе
{
    ab = new about(this);
    ab->show();
}

void MainWindow::on_action_5_triggered() // Открытие окна справочника ЕТС и ВЧУ
{
    etc = new ETC(this);
    etc->show();
}
