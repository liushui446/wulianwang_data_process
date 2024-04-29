#include "mymqtt.h"
#include "ui_mymqtt.h"

#include <QMessageBox>

MyMqtt::MyMqtt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMqtt)
{
    ui->setupUi(this);
    iniUI();
}

MyMqtt::~MyMqtt()
{
    if(mqtt != nullptr)
    {
        mqtt->disconnectFromHost();
    }
    delete ui;
}

void MyMqtt::iniUI()
{
    //自定义设置接收设备数据范围
    m_set_1_range_low = 0;
    m_set_1_range_high = 20;
    m_set_2_range_low = 0;
    m_set_2_range_high = 20;
    m_set_3_range_low = 0;
    m_set_3_range_high = 20;

    //阈值设定
    m_topic_1_threshold = 10;
    m_topic_2_threshold = 10;
    m_topic_3_threshold = 10;

    m_LoadSerise_set_1 = new QSplineSeries(this);
    m_LoadSerise_set_2 = new QSplineSeries(this);
    m_LoadSerise_set_3 = new QSplineSeries(this);
    m_LoadSerise_set_1->clear();
    m_LoadSerise_set_2->clear();
    m_LoadSerise_set_3->clear();
    QDateTime timeStart=QDateTime::currentDateTime();
    QDateTime timeEnd=timeStart.addSecs(1800);

    m_axisX_set_1 = new QDateTimeAxis(this);
    m_axisX_set_2 = new QDateTimeAxis(this);
    m_axisX_set_3 = new QDateTimeAxis(this);

    m_axisX_set_1->setTitleText("时间");
    m_axisX_set_1->setTitleBrush(Qt::white);
    m_axisX_set_1->setFormat("hh:mm:ss");
    m_axisX_set_1->setRange(timeStart, timeEnd);
    m_axisX_set_1->setTickCount(10);
    m_axisX_set_2->setTitleText("时间");
    m_axisX_set_2->setTitleBrush(Qt::white);
    m_axisX_set_2->setFormat("hh:mm:ss");
    m_axisX_set_2->setRange(timeStart, timeEnd);
    m_axisX_set_2->setTickCount(10);
    m_axisX_set_3->setTitleText("时间");
    m_axisX_set_3->setTitleBrush(Qt::white);
    m_axisX_set_3->setFormat("hh:mm:ss");
    m_axisX_set_3->setRange(timeStart, timeEnd);
    m_axisX_set_3->setTickCount(10);

    m_axisY_set_1 = new QValueAxis(this);
    m_axisY_set_2 = new QValueAxis(this);
    m_axisY_set_3 = new QValueAxis(this);

    m_axisY_set_1->setTitleText("data");
    m_axisY_set_1->setTitleBrush(Qt::white);
    m_axisY_set_1->setLabelFormat("%.1f");
    m_axisY_set_1->setRange(m_set_1_range_low, m_set_1_range_high);
    m_axisY_set_1->setTickCount(4);
    m_axisY_set_2->setTitleText("data");
    m_axisY_set_2->setTitleBrush(Qt::white);
    m_axisY_set_2->setLabelFormat("%.1f");
    m_axisY_set_2->setRange(m_set_2_range_low, m_set_2_range_high);
    m_axisY_set_2->setTickCount(4);
    m_axisY_set_3->setTitleText("data");
    m_axisY_set_3->setTitleBrush(Qt::white);
    m_axisY_set_3->setLabelFormat("%.1f");
    m_axisY_set_3->setRange(m_set_3_range_low, m_set_3_range_high);
    m_axisY_set_3->setTickCount(4);

    m_chart_set_1 = new QChart();
    m_chart_set_1->addSeries(m_LoadSerise_set_1);//曲线加入到坐标
    m_chart_set_1->addAxis(m_axisX_set_1, Qt::AlignBottom);
    m_LoadSerise_set_1->attachAxis(m_axisX_set_1);
    m_chart_set_1->addAxis(m_axisY_set_1, Qt::AlignLeft);
    m_LoadSerise_set_1->attachAxis(m_axisY_set_1);
    m_chart_set_1->setTitle("Set_1-Data");
    m_chart_set_1->setTitleBrush(Qt::white);
    //m_chart_set_1->setBackgroundVisible(false);
    m_chart_set_1->legend()->hide();
    m_chart_set_1->setTheme(QtCharts::QChart::ChartTheme::ChartThemeDark);

    m_chart_set_2 = new QChart();
    m_chart_set_2->addSeries(m_LoadSerise_set_2);//曲线加入到坐标
    m_chart_set_2->addAxis(m_axisX_set_2, Qt::AlignBottom);
    m_LoadSerise_set_2->attachAxis(m_axisX_set_2);
    m_chart_set_2->addAxis(m_axisY_set_2, Qt::AlignLeft);
    m_LoadSerise_set_2->attachAxis(m_axisY_set_2);
    m_chart_set_2->setTitle("Set_2-Data");
    m_chart_set_2->setTitleBrush(Qt::white);
    //m_chart_set_2->setBackgroundVisible(false);
    m_chart_set_2->legend()->hide();
    m_chart_set_2->setTheme(QtCharts::QChart::ChartTheme::ChartThemeDark);

    m_chart_set_3 = new QChart();
    m_chart_set_3->addSeries(m_LoadSerise_set_3);//曲线加入到坐标
    m_chart_set_3->addAxis(m_axisX_set_3, Qt::AlignBottom);
    m_LoadSerise_set_3->attachAxis(m_axisX_set_3);
    m_chart_set_3->addAxis(m_axisY_set_3, Qt::AlignLeft);
    m_LoadSerise_set_3->attachAxis(m_axisY_set_3);
    m_chart_set_3->setTitle("Set_3-Data");
    m_chart_set_3->setTitleBrush(Qt::white);
    //m_chart_set_3->setBackgroundVisible(false);
    m_chart_set_3->legend()->hide();
    m_chart_set_3->setTheme(QtCharts::QChart::ChartTheme::ChartThemeDark);

    m_chartview_set_1 = new QChartView(this);
    m_chartview_set_1->setEnabled(true);
    m_chartview_set_1->setChart(m_chart_set_1);
    m_chartview_set_1->setRenderHint(QPainter::Antialiasing);//防止图形走样
    m_chartview_set_2 = new QChartView(this);
    m_chartview_set_2->setEnabled(true);
    m_chartview_set_2->setChart(m_chart_set_2);
    m_chartview_set_2->setRenderHint(QPainter::Antialiasing);//防止图形走样
    m_chartview_set_3 = new QChartView(this);
    m_chartview_set_3->setEnabled(true);
    m_chartview_set_3->setChart(m_chart_set_3);
    m_chartview_set_3->setRenderHint(QPainter::Antialiasing);//防止图形走样

    ui->Layout_Topic_1->addWidget(m_chartview_set_1);
    ui->Layout_Topic_2->addWidget(m_chartview_set_2);
    ui->Layout_Topic_3->addWidget(m_chartview_set_3);

}

void MyMqtt::on_btn_connect_clicked()
{
    if(ui->btn_connect->text()=="连接")//连接服务器
    {
        if(mqtt == nullptr)
        {
            host = ui->lineEdit_host->text();
            port = ui->lineEdit_port->text().toUShort();
            QHostAddress bafa_host = QHostInfo::fromName(host).addresses()[0];
            mqtt = new QMQTT::Client(bafa_host, port);
            connect(mqtt, SIGNAL(connected()),    this, SLOT(mqtt_connected()));
            connect(mqtt, SIGNAL(disconnected()), this, SLOT(mqtt_disconnected()));
            connect(mqtt, SIGNAL(subscribed(QString, quint8)), this, SLOT(mqtt_sub_success(QString, quint8)));
            connect(mqtt, SIGNAL(received(QMQTT::Message)),   this, SLOT(mqtt_recv_msg(QMQTT::Message)));
            mqtt->setClientId(USER_NAME); // 设置客户端ID为自己的私钥
            mqtt->setKeepAlive(10);

            mqtt->setCleanSession(true);
            mqtt->connectToHost(); //连接mqtt
        }
    }
    else
    {
        if(mqtt->isConnectedToHost())
        {
            mqtt->disconnectFromHost();
        }
    }
}

void MyMqtt::mqtt_connected() //连接成功
{
    ui->textBrowser->append("连接成功");
    ui->btn_connect->setText("断开");
    ui->label_8->setText("连接中");
}

void MyMqtt::mqtt_disconnected() //连接断开
{
    ui->textBrowser->append("连接断开");
    ui->btn_connect->setText("连接");
    ui->label_8->setText("等待连接");
    //delete mqtt;
    mqtt = nullptr;
}

void MyMqtt::mqtt_sub_success(QString topic, quint8 qos) //订阅成功
{
    //Q_UNUSED(topic);
    Q_UNUSED(qos);

    QString msg = "订阅主题 ";
    msg += topic;
    msg += " 成功";
    ui->textBrowser->append(msg);
}

void MyMqtt::mqtt_recv_msg(QMQTT::Message msg) //接收消息处理
{
    QString recv_msg = "Topic:";
    QString data = msg.payload();
    recv_msg += msg.topic();
    recv_msg += "    Payload:";
    recv_msg += data;
    ui->textBrowser->append(recv_msg);

    if (msg.topic() == m_tp_1) {
        processTopic1Message(msg.payload());
    } else if (msg.topic() == m_tp_2) {

        processTopic2Message(msg.payload());
    } else if (msg.topic() == m_tp_3) {
        processTopic3Message(msg.payload());
    } else {
        qDebug() << "Unhandled topic:" << msg.topic();
    }
}

void MyMqtt::on_btn_sub_tp_1_clicked() //订阅1
{
    m_tp_1 = ui->lineEdit_sub_topic_1->text();
    if(m_tp_1 == "")
    {
        showMessageBox(QString("topic_1 editbox is null!"));
        return;
    }
    mqtt->subscribe(ui->lineEdit_sub_topic_1->text(), 1);
}

void MyMqtt::on_btn_sub_tp_2_clicked() //订阅2
{
    m_tp_2 = ui->lineEdit_sub_topic_2->text();
    if(m_tp_2 == "")
    {
        showMessageBox(QString("topic_2 editbox is null!"));
        return;
    }
    mqtt->subscribe(ui->lineEdit_sub_topic_2->text(), 1);
}

void MyMqtt::on_btn_sub_tp_3_clicked() //订阅3
{
    m_tp_3 = ui->lineEdit_sub_topic_3->text();
    if(m_tp_3 == "")
    {
        showMessageBox(QString("topic_3 editbox is null!"));
        return;
    }
    mqtt->subscribe(ui->lineEdit_sub_topic_3->text(), 1);
}

void MyMqtt::on_btn_pub_clicked() //发布消息
{
    QMQTT::Message msg;
    msg.setTopic(ui->lineEdit_pub_topic->text());
    msg.setPayload(ui->textEdit_msg->toPlainText().toLocal8Bit());
    mqtt->publish(msg);
}

void MyMqtt::on_btn_clear_recv_clicked()
{
    ui->textBrowser->clear();
}

void MyMqtt::on_btn_clear_send_clicked()
{
    ui->textEdit_msg->clear();
}

void MyMqtt::processTopic1Message(QString data)
{
    double painter_data = data.toDouble();
    QDateTime time = QDateTime::currentDateTime();
    m_LoadSerise_set_1->append(time.toMSecsSinceEpoch(), painter_data);
    if(painter_data > m_topic_1_threshold)
    {
        ui->label_tp_1_status->setText("警报");
        ui->label_tp_1_status->setStyleSheet("color: rgb(255, 0, 0);");
    }
}

void MyMqtt::processTopic2Message(QString data)
{
    double painter_data = data.toDouble();
    QDateTime time = QDateTime::currentDateTime();
    m_LoadSerise_set_2->append(time.toMSecsSinceEpoch(),painter_data);
    if(painter_data > m_topic_2_threshold)
    {
        ui->label_tp_2_status->setText("警报");
        ui->label_tp_2_status->setStyleSheet("color: rgb(255, 0, 0);");
    }
}

void MyMqtt::processTopic3Message(QString data)
{
    double painter_data = data.toDouble();
    QDateTime time = QDateTime::currentDateTime();
    m_LoadSerise_set_3->append(time.toMSecsSinceEpoch(),painter_data);
    if(painter_data > m_topic_3_threshold)
    {
        ui->label_tp_3_status->setText("警报");
        ui->label_tp_3_status->setStyleSheet("color: rgb(255, 0, 0);");
    }
}

void MyMqtt::showMessageBox(QString mess) {
    QMessageBox messageBox;
    messageBox.setWindowTitle("提示");
    messageBox.setText(mess);

    messageBox.setDefaultButton(QMessageBox::Ok);

    messageBox.exec();
}
