#ifndef NORMS17_XX_H
#define NORMS17_XX_H

#include <QMainWindow>

namespace Ui {
class norms17_xx;
}

class norms17_xx : public QMainWindow
{
    Q_OBJECT

public:
    explicit norms17_xx(QWidget *parent = 0);
    ~norms17_xx();

private:
    Ui::norms17_xx *ui;
};

#endif // NORMS17_XX_H
