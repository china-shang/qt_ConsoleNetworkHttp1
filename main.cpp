#include <QGuiApplication>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QQmlContext>
#include <QNetworkReply>
#include <QDebug>
#include <QFile>
#include <QStandardPaths>
#include <QQmlApplicationEngine>


#include "networkmanger.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication a(argc, argv);

    QQmlApplicationEngine *engine=new QQmlApplicationEngine();

    qmlRegisterType<NetworkManger>("networkmanger",1,0,"NetworkManger");
    NetworkManger manager;

    engine->rootContext()->setContextProperty("manger",&manager);

    engine->load(QUrl("qrc:/main.qml"));

//    manager->testProxy();
//    manager->testPost();


    return a.exec();
}
