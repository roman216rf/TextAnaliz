#include "serverthread.h"

//Конструктор служит для записи полученного дескриптора в соответствующую переменную
ServerThread::ServerThread(qintptr socketDescriptor, QObject *parent): QThread(parent), socketDescriptor(socketDescriptor), nextBlockSize(0){}

void ServerThread::run(){

    //Создаём сокет и подключаем к нему слоты
    tcpSocket = std::make_unique<QTcpSocket>(this);

    if(!tcpSocket->setSocketDescriptor(socketDescriptor)){
        emit error(tcpSocket->error());
        return;
    }

    connect(tcpSocket.get(), SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(tcpSocket.get(), SIGNAL(disconnected()), SLOT(slotDisconnect()));

    //Добавляем объекты фабрики в массив. Новые алгоритмы регистрируются только здесь
    NumberCharFactory* numberCharFactory = new NumberCharFactory;
    NumberWordFactory* numberWordFactory = new NumberWordFactory;
    algorithms.push_back(numberCharFactory->createAlgorithm());
    algorithms.push_back(numberWordFactory->createAlgorithm());

    exec();
}

void ServerThread::slotReadyRead(){
    QDataStream in(tcpSocket.get());
    QString data;
    QByteArray block;
    in.setVersion(QDataStream::Qt_5_15);
    while(true){
        if (!nextBlockSize){
            if (tcpSocket.get()->bytesAvailable() < sizeof(quint32))
                break;
            in >> nextBlockSize;
        }

        if (tcpSocket.get()->bytesAvailable() < nextBlockSize)
            break;

        data += QString(in.device()->readAll()).toUtf8();
        nextBlockSize = 0;
    }

    //Возвращаем клиенту результат анализа полученного текста.
    sendToClient(resultFormation(data));
}

void ServerThread::slotDisconnect(){
    quit();
    requestInterruption();
}

QString ServerThread::resultFormation(const QString &data){
    QString result;
    for(Algorithm* algorithm: algorithms){
        result += algorithm->run(data);
    }
    return result;
}

void ServerThread::sendToClient(const QString &data){
    //Переводим данные в байтовый массив и записываем в сокет
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << data.toUtf8();

    out.device()->seek(0);
    out << quint32(block.size() - sizeof(quint32));

    tcpSocket.get()->write(block);
}
