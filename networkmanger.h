#ifndef NETWORKMANGER_H

#define NETWORKMANGER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QObject>

class NetworkManger : public QNetworkAccessManager
{
    Q_OBJECT
public:
    typedef QNetworkReply::RawHeaderPair HeaderPair;
    explicit NetworkManger(QObject *parent=nullptr);
    Q_INVOKABLE void run();
    void testProxy();

public slots:
    void replyFinally();
    void readFromReply();

private:
    QNetworkRequest *req;
    QNetworkReply *reply;
    QUrl *url;

};

#endif // NETWORKMANGER_H
