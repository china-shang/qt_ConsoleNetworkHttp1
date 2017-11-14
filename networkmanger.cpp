#include "networkmanger.h"
#include <QCoreApplication>
#include <QCoreApplication>
#include <QHttpMultiPart>
#include <QNetworkProxy>
#include <QFile>
#include <QThread>
#include <QStandardPaths>

NetworkManger::NetworkManger(QObject *parent):QNetworkAccessManager(parent),url(new QUrl("http://www.qt.io/"))
{
    loginUrl=QUrl("https://www.baiud.com");
    connect(this,&NetworkManger::encrypted,this,[=]{
        qDebug()<<"encrypted";
    });

}

void NetworkManger::run()
{
    qDebug()<<"start";

    this->connectToHostEncrypted(QString("www.baidu.com"));
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

void NetworkManger::testPost()
{
    req=new QNetworkRequest();
    req->setUrl(QUrl("http://localhost:8080/test/servlet"));

    QHttpPart *text=new QHttpPart();
    text->setHeader(QNetworkRequest::ContentDispositionHeader,
                    QVariant("form-data;name=\"text\""));
    text->setBody("hello world");

    QHttpPart *filePart=new QHttpPart();
    filePart->setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant("form-data;name=\"file\";filename=\"filename\""));
    QString b=QStandardPaths::standardLocations(QStandardPaths::HomeLocation).last();

    QFile *file=new QFile(b+"/ss.sh");
    file->open(QFile::ReadOnly|QFile::Text);
    filePart->setBodyDevice(file);

    QHttpMultiPart *multiPart=new QHttpMultiPart(QHttpMultiPart::FormDataType);
    multiPart->append(*text);
    multiPart->append(*filePart);

    reply=this->post(*req,multiPart);

    connect(reply,&QNetworkReply::finished,[&]{
        QByteArray arr=reply->readAll();
        QString s=QString::fromUtf8(arr);
        s.remove(s.size()-1,10);
        qDebug()<<"reply:";
        qDebug()<<s;

        reply->deleteLater();
        QCoreApplication::exit(0);

    });

}

void NetworkManger::login()
{

    QNetworkRequest req(QUrl("http://www.baidu.com"));
    QNetworkReply *reply=this->post(req,"hello");

    connect(reply,&QNetworkReply::finished,[&]{
        //verfication

        qDebug()<<"verfication";

        QByteArray arr=reply->readAll();
        qDebug()<<arr;
        emit this->loginStatusChanged(true);
    });


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
