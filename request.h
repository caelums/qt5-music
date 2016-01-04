#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

class Request : public QObject
{
    Q_OBJECT
public:
    explicit Request(QObject *parent = 0);
    void get(QUrl);

signals:

public slots:
    void replyFinished ();

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
};

#endif // REQUEST_H
