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

    Q_PROPERTY(bool loginStatus READ loginStatus  NOTIFY loginStatusChanged)

public:
    typedef QNetworkReply::RawHeaderPair HeaderPair;
    explicit NetworkManger(QObject *parent=nullptr);
    Q_INVOKABLE void run();
    Q_INVOKABLE void testProxy();
    Q_INVOKABLE void testPost();
    Q_INVOKABLE void login();

    bool loginStatus() const{
        return mloginStatus;
    }

signals:
    void loginStatusChanged(bool status);

public slots:
    void replyFinally();
    void readFromReply();

private slots:

private:
    QUrl loginUrl;
    bool mloginStatus;
    QNetworkRequest *req;
    QNetworkReply *reply;
    QUrl *url;

};

#endif // NETWORKMANGER_H
