#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QVector>
#include <numberchar.h>
#include <numberword.h>

class ServerThread : public QThread{
    Q_OBJECT
public:
    ServerThread(qintptr socketDescriptor, QObject *parent);
    void run() Q_DECL_OVERRIDE; // с приходом с++11 вместо "Q_DECL_OVERRIDE" лучше писать "override"

signals:
    void error(QTcpSocket::SocketError);

public slots:
    void slotReadyRead();
    void slotDisconnect();

private:
    int socketDescriptor;
    QString resultFormation(const QString& data);
    std::unique_ptr<QTcpSocket> tcpSocket;
    quint32 nextBlockSize;
    QString data;
    void sendToClient(const QString& data);
    QVector<Algorithm*> algorithms;

};

#endif // SERVERTHREAD_H
