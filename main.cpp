#include "mymqtt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss("../mqtt_demo/Irrorater.qss");
    if(qss.open(QFile::ReadOnly)){
        a.setStyleSheet(qss.readAll());
    }
    qss.close();
    MyMqtt w;
    w.show();

    return a.exec();
}
