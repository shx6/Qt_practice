#include "client.h"

#include <QFileInfo>
#include <QHostAddress>
#include<QFile>
#include <QThread>
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
    sockect->deleteLater();
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

void Client::sendFile(QString path,QString mode)
{
    qDebug()<<mode;
    if (mode=="文件模式"){
        qDebug() << "发送文件线程: " << QThread::currentThread()<<path;
        QFile file(path);
        QFileInfo info(path);
        int fileSize = info.size();

        file.open(QFile::ReadOnly);
        int percent=0;
        while(!file.atEnd())
        {
            static int num = 0;
            if(num == 0)
            {
                //sockect->write((char*)&fileSize, 4);
            }


            QByteArray line = file.readLine();
            num += line.size();

             percent = (num * 100 / fileSize);
            //emit curPercent(percent);
             qDebug()<<percent<<"%"<<line;

            sockect->write(line);
        }
        qDebug()<<"099887";
        emit sendfileFinish(percent);

    }
}

void Client::receivefile(QString path)
{

}

