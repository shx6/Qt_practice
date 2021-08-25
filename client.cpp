#include "client.h"

#include <QHostAddress>

Client::Client(QObject *parent) : QObject(parent)
{

}

void Client::connectNetwork(QString ip, int port)
{
    sockect=new QTcpSocket;
    sockect->connectToHost(QHostAddress(ip),port);

    connect(sockect,&QTcpSocket::connected,this,&Client::connectedOK);
    connect(sockect,&QTcpSocket::disconnected,this,[=](){
        sockect->close();
        sockect->deleteLater();
        emit disconnectOK();
    });
    //connect(this,&mainwindow)
}

void Client::receiveMessage()
{
    connect(sockect, &QTcpSocket::readyRead, this, [=]()
    {
         QByteArray data = sockect->readAll();

         emit sendData(data);
    });

}

void Client::breakConnect()
{
    sockect->close();
}

void Client::sendMess(QString message,QString mode)
{
    if(mode=="tcp客户端")
    {
         sockect->write(message.toUtf8());
         emit showSendMess(message);//show message of client's sending
}
}
