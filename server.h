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

    void receive();
    void send(QString);
signals:

    void showMess(QByteArray);
private:
    QTcpSocket* socket;
};

#endif // SERVER_H
