#include "networkmanger.h"
#include <QCoreApplication>
#include <QThread>

NetworkManger::NetworkManger(QObject *parent):QNetworkAccessManager(parent),url(new QUrl("http://www.qt.io/"))
{

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
    connect(this,&NetworkManger::encrypted,this,[=]{
        qDebug()<<"encrypted";
    });

}

void NetworkManger::replyFinally()
{
    if(reply->error()){
        reply->deleteLater();
        reply=Q_NULLPTR;
    }
    qDebug()<<"finally";

}

void NetworkManger::readFromReply()
{
    QString a=reply->header(QNetworkRequest::ContentTypeHeader).toString();
    reply->rawHeaderList();
    foreach (HeaderPair i, reply->rawHeaderPairs()) {
        if(i.first=="Date"){
            qDebug()<<"this is Date\n"<<i.second;
        }
        qDebug()<<i.first<<":"<<i.second;

    }

    qDebug()<<a;
    QCoreApplication::exit(0);

}
