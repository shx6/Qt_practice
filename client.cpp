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

void Client::sendMess(QString message,QString mode,bool isHex)
{
    if(mode=="tcp客户端")
    {
         emit showSendMess(message);//show message of client's sending
         if (!isHex)
             sockect->write(message.toUtf8());
         else {
             //16进制转换
             QByteArray str=QByteArray::fromHex(message.toUtf8());
             sockect->write(str);
         }
}
}
