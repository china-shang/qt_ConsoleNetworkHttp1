#include "networkmanger.h"
#include <QCoreApplication>
#include <QCoreApplication>
#include <QNetworkProxy>
#include <QThread>

NetworkManger::NetworkManger(QObject *parent):QNetworkAccessManager(parent),url(new QUrl("http://www.qt.io/"))
{
    connect(this,&NetworkManger::encrypted,this,[=]{
        qDebug()<<"encrypted";
    });

}

void NetworkManger::run()
{
    qDebug()<<"start";

    this->connectToHostEncrypted("www.baidu.com");
    QThread::sleep(5);
    qDebug()<<"sleep end";

    QNetworkRequest req(QUrl("https://www.baidu.com"));
    reply=this->get(req);

    connect(reply,SIGNAL(finished()),this,SLOT(replyFinally()));
    connect(reply,&QNetworkReply::readyRead,this,qOverload<>(&NetworkManger::readFromReply));
}

void NetworkManger::testProxy()
{
    QNetworkProxy proxy(QNetworkProxy::Socks5Proxy,"127.0.0.1",1080);
    this->setProxy(proxy);
    qDebug()<<"has set proxy";

    req=new QNetworkRequest();
    req->setUrl(QUrl("https://www.google.com"));
    req->setRawHeader("DNT","1");

    reply=this->get(*req);

    connect(reply,SIGNAL(finished()),this,SLOT(replyFinally()));
    connect(reply,&QNetworkReply::readyRead,this,qOverload<>(&NetworkManger::readFromReply));

}

void NetworkManger::replyFinally()
{

    foreach (HeaderPair i, reply->rawHeaderPairs()) {
        if(i.first=="Date"){
            qDebug()<<"this is Date\n"<<i.second;
        }
        qDebug()<<i.first<<":"<<i.second;
    }

    qDebug()<<reply->url();

    reply->deleteLater();
    reply=Q_NULLPTR;
    qDebug()<<"finally";
    QCoreApplication::exit(0);

}

void NetworkManger::readFromReply()
{
    QByteArray arr=reply->readAll();
    qDebug()<<QString::fromUtf8(arr);

}
