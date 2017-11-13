#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QFile>
#include <QStandardPaths>


#include "networkmanger.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    NetworkManger *manager=new NetworkManger();

//    manager->testProxy();
    manager->testPost();

    return a.exec();
}
