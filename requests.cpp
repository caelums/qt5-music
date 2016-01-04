#include "requests.h"

Requests::Requests()
{
    manager = new QNetworkAccessManager();
}


void Requests::detail(QString id)
{
    QString path = QString(DETAIL_PATH).arg(id);
    QString url = QString(OLD_API).arg(path);
    qDebug() << id;
    qDebug() << url;

    QNetworkRequest request = QNetworkRequest(QUrl(url));
    reply = manager->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(detailResponse()));
}

void Requests::search(QString keyWord)
{
    QString url = QString(OLD_API).arg(SEARCH_PATH);

    QByteArray data;
    QUrlQuery params;
    //,{"type","1"},{"offset","0"},{"total","true"},{"limit","1"}
    params.addQueryItem("type", "1");
    params.addQueryItem("offset", "0");
    params.addQueryItem("total", "true");
    params.addQueryItem("limit", "10");
    params.addQueryItem("s",keyWord);
    data.append(params.toString());

    qDebug() << url;
    qDebug() << data;
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setRawHeader("User-Agent", "Accept");
    request.setRawHeader("Accept-Language", "zh-CN,en-US;q=0.7,en;q=0.3");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
    request.setRawHeader("Host", "music.163.com");
    request.setRawHeader("Referer", "http://music.163.com/");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:39.0) Gecko/20100101 Firefox/39.0");

    reply = manager->post(request,data);
    connect(reply,SIGNAL(finished()),this,SLOT(searchResponse()));
}

void Requests::detailResponse()
{
    QString res = QString::fromUtf8(reply->readAll());

    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(res.toUtf8(), &error);

    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject()) {
            QJsonObject object = jsonDocument.object();
            QJsonArray songs = object["songs"].toArray();
            for (int index = 0; index < songs.size(); ++index) {
                QJsonObject song = songs[index].toObject();
                QString mp3Url = song["mp3Url"].toString();

                emit detailResult(mp3Url);
                qDebug() << mp3Url;

            }

        }else{
            qDebug() << "fail";
        }

    }else {
        qDebug() << error.errorString().toUtf8().constData();
        exit(1);
    }
}

void Requests::searchResponse()
{
    QString res = QString::fromUtf8(reply->readAll());

    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(res.toUtf8(), &error);

    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject()) {
            QJsonObject object = jsonDocument.object();
            int code = object["code"].toInt();
            if(code == 200)
            {
                QJsonObject songResult = object["result"].toObject();
                int songCount = songResult["songCount"].toInt();
                QJsonArray songs = songResult["songs"].toArray();



                QStandardItemModel *model = new QStandardItemModel(songs.size(),5,this);

                model->setHeaderData( 0, Qt::Horizontal, QObject::tr("id") );
                model->setHeaderData( 1, Qt::Horizontal, QObject::tr("标题") );
                model->setHeaderData( 2, Qt::Horizontal, QObject::tr("歌手") );
                model->setHeaderData( 3, Qt::Horizontal, QObject::tr("专辑") );
                model->setHeaderData( 4, Qt::Horizontal, QObject::tr("时长") );

                for (int index = 0; index < songs.size(); ++index) {
                    QJsonObject song = songs[index].toObject();
                    int songId = song["id"].toInt();
                    int songDuration = song["duration"].toInt();
                    QString time = QDateTime::fromTime_t(songDuration/1000).toString("mm:ss");

                    QString songName = song["name"].toString();

                    QJsonArray artists = song["artists"].toArray();
                    QJsonObject artist = artists[0].toObject();
                    QString artistName = artist["name"].toString();

                    QJsonObject album = song["album"].toObject();
                    QString albumName = album["name"].toString();


                    model->setItem(index,0,new QStandardItem(QString::number(songId)));
                    model->setItem(index,1,new QStandardItem(songName));
                    model->setItem(index,2,new QStandardItem(artistName));
                    model->setItem(index,3,new QStandardItem(albumName));
                    model->setItem(index,4,new QStandardItem(time));
                    qDebug() << songId << songDuration << artistName << songName << albumName;
                }

                emit searchResult(model);
            }else{
                qDebug() << "fail";
            }
        }
    } else {
        qDebug() << error.errorString().toUtf8().constData();
        exit(1);
    }
}


