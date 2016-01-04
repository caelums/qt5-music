#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtMultimedia>
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QStandardPaths>
#include <QString>


#include "requests.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QMediaPlayer *player;

    ~MainWindow();

private slots:
    void open();
    void play();
    void pause();

    void percent(int);
    void positionChanged(qint64);
    void durationChanged(qint64);
    void volume(int);

    void response();

    void doubleClick(QModelIndex);

    void search(QStandardItemModel*);
    void detail(QString);

    void doSearch();

    void playerStateChange(int);
private:
    Ui::MainWindow *ui;
    QNetworkReply *reply;
    QStandardItemModel *model;
    Requests *r;

};

#endif // MAINWINDOW_H
