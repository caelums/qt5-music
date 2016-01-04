#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "requests.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->volume->setRange(0,100);
    ui->volume->setValue(50);

    player = new QMediaPlayer(this);

    model = new QStandardItemModel(0,5,this);
    r = new Requests();

    model->setHeaderData( 0, Qt::Horizontal, QObject::tr("id") );
    model->setHeaderData( 1, Qt::Horizontal, QObject::tr("标题") );
    model->setHeaderData( 2, Qt::Horizontal, QObject::tr("歌手") );
    model->setHeaderData( 3, Qt::Horizontal, QObject::tr("专辑") );
    model->setHeaderData( 4, Qt::Horizontal, QObject::tr("时长") );

    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setShowGrid(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setStyleSheet("QTableView{selection-background-color: #dddddd;}");

    ui->tableView->setColumnHidden(0,true);
//    ui->tableView->setColumnWidth(0,300);

    connect(r,SIGNAL(searchResult(QStandardItemModel*)),this,SLOT(search(QStandardItemModel*)));
    connect(r,SIGNAL(detailResult(QString)),this,SLOT(detail(QString)));

    connect(ui->tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleClick(QModelIndex)));

    QPalette p = QPalette();
    p.setColor(QPalette::AlternateBase,QColor("#eeeeee"));
    ui->tableView->setPalette(p);

    connect(ui->volume,SIGNAL(sliderMoved(int)),this,SLOT(volume(int)));
    connect(player, SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    connect(player, SIGNAL(durationChanged(qint64)), this,SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(bufferStatusChanged(int)),this,SLOT(playerStateChange(int)));

    connect(ui->playBtn,SIGNAL(clicked()),this,SLOT(play()));
    connect(ui->pauseBtn,SIGNAL(clicked()),this,SLOT(pause()));

    connect(ui->searchEdit,SIGNAL(returnPressed()),this,SLOT(doSearch()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),QStandardPaths::writableLocation(QStandardPaths::MusicLocation));

    qDebug() <<"fileName:" <<fileName;

    if(!fileName.isEmpty()){
        player->setMedia(QUrl::fromLocalFile(fileName));
        player->setVolume(50);
    }
}

void MainWindow::play()
{
    if(player)
    {
        player->play();
    }
}

void MainWindow::pause()
{
    if(player)
    {
        player->pause();
    }
}


void MainWindow::volume(int v)
{
    if(player)
    {
        player->setVolume(v);
    }
}

void MainWindow::percent(int p)
{
    qDebug() << p;
}

void MainWindow::positionChanged(qint64 p)
{
//    qint64 res = p/player->position()
    ui->proccess->setValue(p/1000);

}

void MainWindow::durationChanged(qint64 duration)
{
    qDebug() << "max:" <<  duration / 1000;
    ui->proccess->setRange(0, duration / 1000);
}

void MainWindow::search(QStandardItemModel *model)
{
    this->model = model;
    ui->tableView->setModel(model);
}

void MainWindow::detail(QString mp3Url)
{
        player->setMedia(QUrl(mp3Url));
        player->setVolume(50);
        player->play();
}


void MainWindow::doubleClick(QModelIndex index)
{
    int row = index.row();
    QString id = model->item(row,0)->text();
    r->detail(id);
}


void MainWindow::response()
{
    QString res = QString(reply->readAll());
    qDebug() << res;
}

void MainWindow::doSearch()
{
    r->search(ui->searchEdit->text());
}

void MainWindow::playerStateChange(int state)
{
    qDebug() << state;
    qDebug() << "stateChange";
    if(state == QMediaPlayer::EndOfMedia)
    {
        player->play();
    }
}
