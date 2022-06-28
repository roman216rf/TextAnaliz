#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>
#include <QFile>

class Client : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString status MEMBER status NOTIFY connectingStatus)
    Q_PROPERTY(QString color MEMBER color NOTIFY connectingStatus)

public:
    explicit Client(QObject *parent = nullptr);    

signals:
    void connectingStatus(const QString&);
    void msgViewSignal(const QString& title, const QString& text);
    void printResult(const QString& data);   

public slots:
    void clickedConnectingButton(const QString& ip, const QString& port);
    void sendToServer();
    void setFilePath(const QString& path);
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);

private:
    QString filePath;
    quint32 nextBlockSize;
    std::unique_ptr<QTcpSocket> tcpSocket;
    QString status = "Отключен";
    QString color = "RED";
};

#endif // CLIENT_H
