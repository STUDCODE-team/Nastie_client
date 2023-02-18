#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNmeaPositionInfoSource>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    source = QGeoPositionInfoSource::createSource("corelocation",this);
    qDebug() << QGeoPositionInfoSource::availableSources();
    source = QNmeaPositionInfoSource::createDefaultSource(this);
    if (source) {
        qDebug() << "source is ready";
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(positionUpdated(QGeoPositionInfo)));
    }

    _client = new TcpClient;
    _client->connectToHost("localhost", "30391");
    connect(_client, &TcpClient::locationRequired, source, &QGeoPositionInfoSource::startUpdates);
}

void MainWindow::positionUpdated(const QGeoPositionInfo &info)
{
#ifdef QT_DEBUG
    qDebug() << "Position updated:" << info;
#endif
    QString longi = QString::number(info.coordinate().longitude());
    QString lati = QString::number(info.coordinate().latitude());
    _client->send(longi + "-" + lati);
}

MainWindow::~MainWindow()
{
    delete source;
    delete _client;
    delete ui;
}

