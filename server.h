#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include<QTcpServer>
#include<QTcpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QTcpSocket *socket,QObject *parent = nullptr);

    void receive(QString);
    void send(QString,QString ,bool);
    void sendfile(QString,QString);
    void receivefile(QString savePath,QString);

signals:

    void showMess(QByteArray);
    void showSendFile();
private:
    QTcpSocket* socket;
};

#endif // SERVER_H
