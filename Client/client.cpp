#include "client.h"

Client::Client(QObject *parent): nextBlockSize(0), tcpSocket(std::make_unique<QTcpSocket>(this)){
    //Создаем сокет и подключаем слоты обрабатывающие события подключения, ошибки и получения данных с сервера
    connect(tcpSocket.get(), &QTcpSocket::connected, this, [this]() { setProperty("status", "Подключен");
                                                                setProperty("color", "GREEN");});

    connect(tcpSocket.get(), SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(tcpSocket.get(), SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
}

void Client::clickedConnectingButton(const QString& ip, const QString& port){
    //Отключаемся от сервера, если были подключены и подключаемся заново
    //Устанавливает отображение статуса "Отключен"
    setProperty("status", "Отключен");
    setProperty("color", "RED");

    tcpSocket->abort();
    tcpSocket->connectToHost(QString(ip), port.toInt());

    //Устанавливает отображение статуса "Идёт подключение"
    setProperty("status", "Идет подключение");
    setProperty("color", "YELLOW");
}

void Client::sendToServer(){
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)){
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_15);
        //Считываем весь файл и конвентируем данные в UTF-8
        out << QString(file.readAll()).toUtf8();

        //В начало сообщения записываем его размер
        out.device()->seek(0);
        out << quint32(block.size() - sizeof(quint32));

        tcpSocket.get()->write(block);
    }
    else{
        emit msgViewSignal("Ошибка открытия файла", file.errorString());
    }
}

void Client::slotReadyRead(){
    QDataStream in(tcpSocket.get());
    QString data;
    in.setVersion(QDataStream::Qt_5_15);
    while(true){
        //Если переменная, хранящая размер следующего блока равна 0, то считываем размер
        if (!nextBlockSize){
            if (tcpSocket.get()->bytesAvailable() < sizeof(quint32))
                break;
            in >> nextBlockSize;
        }

        if (tcpSocket.get()->bytesAvailable() < nextBlockSize)
            break;

        //Считываем данные и обнуляем размер следующего блока
        data += QString(in.device()->readAll()).toUtf8();
        nextBlockSize = 0;
    }
    emit printResult(data);
}

void Client::slotError(QAbstractSocket::SocketError error){
    //Обработка ошибок в зависимости от их типа
    setProperty("status", "Отключен");
    setProperty("color", "RED");
    QString errMsg = (error == QAbstractSocket::HostNotFoundError ? "Хост не найден." :
                          error == QAbstractSocket::RemoteHostClosedError ? "Удаленный хост закрыт." :
                          error == QAbstractSocket::ConnectionRefusedError ? "В соединении было отказано." :
                          QString(tcpSocket->errorString()));
    emit msgViewSignal("Ошибка соединения", errMsg);
}

void Client::setFilePath(const QString& path){
    filePath = path;
}
