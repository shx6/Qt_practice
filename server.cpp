#include "server.h"
#include<QDebug>
#include <QFile>
#include <QFileInfo>
#include <QThread>
Server::Server(QTcpSocket *sock,QObject *parent) : QObject(parent)
{

    this->socket=sock;
}

void Server::receive(QString mode)
{

    connect(socket, &QTcpSocket::readyRead, this, [=]()
    {
        if(mode=="文件模式")
        {
            QByteArray data = socket->readAll();
            emit showMess(data);
        }
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

void Server::sendfile(QString path,QString mode)
{
    if (mode=="信息模式"){
        QFile file(path);
        QFileInfo info(path);
        int fileSize = info.size();

        file.open(QFile::ReadOnly);

        while(!file.atEnd())
        {
            static int num = 0;
            if(num == 0)
            {
                socket->write((char*)&fileSize, 4);
            }
            QByteArray line = file.readLine();
    //        num += line.size();
    //        int percent = (num * 100 / fileSize);
    //        emit curPercent(percent);

            socket->write(line);
        }
    }
}

void Server::receivefile(QString savePath,QString mode)
{

    if(mode=="文件模式"){
        qDebug() << "服务器子线程: " << QThread::currentThread();

        QFile* file = new QFile(savePath);
        file->open(QFile::WriteOnly);

    // 接收数据
    connect(socket, &QTcpSocket::readyRead, this, [=]()
    {
        if(mode=="文件模式"){

            static int count = 0;
            static int total = 0;
            if(count == 0)
            {
                socket->read((char*)&total, 4);
            }
            // 读出剩余的数据
            QByteArray all = socket->readAll();
            count += all.size();
            file->write(all);

            // 判断数据是否接收完毕了
            if(count == total)
            {
                socket->close();
                socket->deleteLater();
                file->close();
                file->deleteLater();
                //emit over();
            }
        }
        });
    }

}
