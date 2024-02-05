#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>

namespace Ui {
class Settings;
}

class Settings : public QMainWindow
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:
    void on_pushButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

    void on_radioButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::Settings *ui;
    bool is_new = true;

signals:
    void signal_formula(bool);
};

#endif // SETTINGS_H
