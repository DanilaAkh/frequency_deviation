#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "methods.h"
#include "settings.h"
#include "res.h"
#include "equip.h"
#include "gosts.h"
#include "norms.h"
#include "archive.h"
#include "add_norms.h"
#include "about.h"
#include "etc.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QFileDialog>
#include <QDesktopServices>
#include <QAxObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_2_triggered();

    void on_action_8_triggered();

    void on_action_triggered();

    void on_action_6_triggered();

    void on_action_4_triggered();

    void on_action_3_triggered();

    void on_action_9_triggered();

    void on_action_10_triggered();

    void on_action_5_triggered();

private:
    Ui::MainWindow *ui;
    methods *met;
    Settings *sets;
    RES *res;
    Equip *equip;
    GOSTs *gosts;
    Norms *norms;
    archive *arch;
    add_norms *adn;
    about *ab;
    ETC *etc;
    bool is_new_formula = true;

public slots:
    void Slot_form1();
    void Slot_form2();    
    void Slot_formula(bool);

signals:
    void signal_formula_to_res(bool);
};

#endif // MAINWINDOW_H
