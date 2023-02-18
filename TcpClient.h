#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

#ifdef QT_DEBUG
    #include <QTime>
#endif

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient();
    void connectToHost(const QString &ip, const QString &port);

public slots:
    void send(const QString &message);

signals:
    void locationRequired();

private slots:
    void onReadyRead();

private:
    QTcpSocket _socket;
    QString ip;
    QString port;
    QTimer reconn_timer;
    void reconnect();
    void reply(const QByteArray &rep);
};

#endif // TCPCLIENT_H
