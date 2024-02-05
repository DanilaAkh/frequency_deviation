#include "norms17_xx.h"
#include "ui_norms17_xx.h"

norms17_xx::norms17_xx(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::norms17_xx)
{
    ui->setupUi(this);
}

norms17_xx::~norms17_xx()
{
    delete ui;
}
