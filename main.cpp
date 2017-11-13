#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>


#include "networkmanger.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    NetworkManger *manager=new NetworkManger();

    manager->run();

    return a.exec();
}
