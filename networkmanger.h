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
    void run();

public slots:
    void replyFinally();
    void readFromReply();

private:
    QNetworkReply *reply;
    QUrl *url;

};

#endif // NETWORKMANGER_H
