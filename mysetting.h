#ifndef MYSETTING_H
#define MYSETTING_H

#include <QDialog>
#include "myData.h"

namespace Ui {
class MySetting;
}

class MyMqtt;

class MySetting : public QDialog
{
    Q_OBJECT

public:
    explicit MySetting(my_data data,QWidget *parent = nullptr);
    ~MySetting();

    void iniUI();
private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::MySetting *ui;
    MyMqtt* m_cMyMqtt;
    my_data m_setdata;
};

#endif // MYSETTING_H
