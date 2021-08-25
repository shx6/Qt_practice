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

void Server::send(QString s)
{
    qDebug()<<"okkkkk";
    socket->write(s.toUtf8());
    qDebug()<<"sendadadada";
}
