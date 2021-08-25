#include "server.h"
#include<QDebug>
Server::Server(QTcpSocket *sock,QObject *parent) : QObject(parent)
{

    this->socket=sock;
}

void Server::receive()
{
    connect(socket, &QTcpSocket::readyRead, this, [=]()
    {
        QByteArray data = socket->readAll();
        emit showMess(data);
    });

}

void Server::send(QString s,QString workmode,bool isSendHex)
{
    if(workmode=="tcp服务器"){
        if (!isSendHex)
            socket->write(s.toUtf8());
        else {
            //16进制转换
            QByteArray str=QByteArray::fromHex(s.toUtf8());
            socket->write(str);
        }
    }
}
