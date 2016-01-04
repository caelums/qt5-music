#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>

#ifndef REQUESTS_H
#define REQUESTS_H

//STATIC
#define URL_SIZE 256
#define PATH_SIZE 16
//API URL
#define OLD_API "http://music.163.com/api/%1"
#define NEW_API "http://music.163.com/weapi/%1"

//PATH
#define DETAIL_PATH "song/detail?ids=[%1]"
#define LYRIC_PATH "song/lyric?os=android&id=%s&lv=-1&tv=-1"
#define RADIO_PATH "radio/get"
#define SEARCH_PATH "search/get/web"

#include <QObject>
#include <QDateTime>

class Requests : public QObject
{
    Q_OBJECT
public:
    explicit Requests();
    void detail(QString);
    void search(QString);
signals:
    void searchResult(QStandardItemModel*);
    void detailResult(QString);

public slots:
    void searchResponse();
    void detailResponse();
private:
    QNetworkReply *reply;
    QNetworkAccessManager *manager ;

};

#endif // REQUESTS_H
