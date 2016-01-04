#include "request.h"

void Request::get(QUrl url)
{
    reply = manager->get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),this,SLOT(replyFinished()));
}

void Request::replyFinished()
{
    qDebug() << reply->readAll();
}
