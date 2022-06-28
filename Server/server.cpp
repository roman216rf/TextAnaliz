#include "server.h"

Server::Server(const int &port, QObject *parent): QTcpServer(parent){
    listen(QHostAddress::Any, port);
    if (!isListening()){
        qDebug() << "Сервер не может быть запущен. " << errorString();
        close();
        return;
    }
    qDebug() << "Сервер запущен";
}

// Во время нового подключения создаём поток, в котором будем обрабатывать запросы от клиента, для индентификации потока передаем дескриптор в поток
void Server::incomingConnection(qintptr socketDescriptor){
    ServerThread* thread = new ServerThread(socketDescriptor, this);
    connect(thread, &ServerThread::finished, thread, &ServerThread::deleteLater);
    thread->run();
}
