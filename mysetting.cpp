#include "mysetting.h"
#include "ui_mysetting.h"

#include "mymqtt.h"

MySetting::MySetting(my_data data,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MySetting)
{
    ui->setupUi(this);
    m_cMyMqtt = (MyMqtt*)parentWidget();
    m_setdata = data;
    iniUI();
}

MySetting::~MySetting()
{
    delete ui;
}

void MySetting::iniUI()
{
    ui->lineEdit_Client_Id->setText(m_setdata.m_client_id);
    ui->lineEdit_topic_1_low->setText(QString::number(m_setdata.m_set_1_range_low,2,2));
    ui->lineEdit_topic_1_high->setText(QString::number(m_setdata.m_set_1_range_high,2,2));
    ui->lineEdit_topic_2_low->setText(QString::number(m_setdata.m_set_2_range_low,2,2));
    ui->lineEdit_topic_2_high->setText(QString::number(m_setdata.m_set_2_range_high,2,2));
    ui->lineEdit_topic_3_low->setText(QString::number(m_setdata.m_set_3_range_low,2,2));
    ui->lineEdit_topic_3_high->setText(QString::number(m_setdata.m_set_3_range_high,2,2));
    ui->lineEdit_topic_1_theld->setText(QString::number(m_setdata.m_topic_1_threshold,2,2));
    ui->lineEdit_topic_2_theld->setText(QString::number(m_setdata.m_topic_2_threshold,2,2));
    ui->lineEdit_topic_3_theld->setText(QString::number(m_setdata.m_topic_3_threshold,2,2));
}

void MySetting::on_pushButton_save_clicked()
{
    my_data tmp_data;
    tmp_data.m_client_id = ui->lineEdit_Client_Id->text();

    tmp_data.m_set_1_range_low = ui->lineEdit_topic_1_low->text().toDouble();
    tmp_data.m_set_1_range_high = ui->lineEdit_topic_1_high->text().toDouble();
    tmp_data.m_set_2_range_low = ui->lineEdit_topic_2_low->text().toDouble();
    tmp_data.m_set_2_range_high = ui->lineEdit_topic_2_high->text().toDouble();
    tmp_data.m_set_3_range_low = ui->lineEdit_topic_3_low->text().toDouble();
    tmp_data.m_set_3_range_high = ui->lineEdit_topic_3_high->text().toDouble();

    tmp_data.m_topic_1_threshold = ui->lineEdit_topic_1_theld->text().toDouble();
    tmp_data.m_topic_2_threshold = ui->lineEdit_topic_2_theld->text().toDouble();
    tmp_data.m_topic_3_threshold = ui->lineEdit_topic_3_theld->text().toDouble();
    m_cMyMqtt->ChangeParam(tmp_data);
    m_cMyMqtt->showMessageBox(QString("Save param Success!"));
}

void MySetting::on_pushButton_close_clicked()
{
    this->close();
}
