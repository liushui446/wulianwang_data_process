#ifndef MYMQTT_H
#define MYMQTT_H

#include <QMainWindow>
#include <qmqtt.h>
#include <QHostInfo>

#include <QChartView>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>

#include <QVector>
#include <QTimer>
#include <QDateTimeAxis>

#include <QtCore/QCoreApplication>
#include <QSettings>

#include "mysetting.h"
#include "myData.h"


#define     USER_NAME   "d17116adf3974250b43d3ae6f9bed1f8"
//#define     USER_NAME   "824675d8b3524ca0a5769affa5f8e969"

namespace Ui {
class MyMqtt;
}

using namespace QtCharts;

class MyMqtt : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyMqtt(QWidget *parent = nullptr);
    ~MyMqtt();

    void iniUI();
    void processTopic1Message(QString data);
    void processTopic2Message(QString data);
    void processTopic3Message(QString data);
    void showMessageBox(QString mess);
    void ChangeParam(my_data data);
    void AchiParam(my_data& data);
    void GetIniFile();
private slots:

    void on_btn_connect_clicked();

    void mqtt_connected();

    void mqtt_disconnected();

    void mqtt_sub_success(QString topic, quint8 qos = 0);

    void mqtt_recv_msg(QMQTT::Message msg);

    void on_btn_sub_tp_1_clicked();

    void on_btn_sub_tp_2_clicked();

    void on_btn_sub_tp_3_clicked();

    void on_btn_pub_clicked();

    void on_btn_clear_recv_clicked();

    void on_btn_clear_send_clicked();

    void on_actionsetting_triggered();

private:
    Ui::MyMqtt *ui;
    QMQTT::Client *mqtt = nullptr;

    MySetting* m_cMySetting;
    QSettings *m_settings = nullptr;

    QString USER_ID;
    QString host;
    quint16 port;

    QChartView* m_chartview_set_1;
    QChartView* m_chartview_set_2;
    QChartView* m_chartview_set_3;

    QChart* m_chart_set_1;
    QChart* m_chart_set_2;
    QChart* m_chart_set_3;

    QDateTimeAxis *m_axisX_set_1;
    QDateTimeAxis *m_axisX_set_2;
    QDateTimeAxis *m_axisX_set_3;

    QValueAxis *m_axisY_set_1;
    QValueAxis *m_axisY_set_2;
    QValueAxis *m_axisY_set_3;

    QSplineSeries *m_LoadSerise_set_1;
    QSplineSeries *m_LoadSerise_set_2;
    QSplineSeries *m_LoadSerise_set_3;

    double m_set_1_range_low;
    double m_set_1_range_high;
    double m_set_2_range_low;
    double m_set_2_range_high;
    double m_set_3_range_low;
    double m_set_3_range_high;

    QString m_tp_1;
    QString m_tp_2;
    QString m_tp_3;

    double m_topic_1_threshold;
    double m_topic_2_threshold;
    double m_topic_3_threshold;

    my_data m_setting;
};

#endif // MYMQTT_H
