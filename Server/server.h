#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <serverthread.h>
#include <QDebug>

class Server: public QTcpServer{
    Q_OBJECT
public:
    Server(const int& port, QObject* parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;
};

#endif // SERVER_H
