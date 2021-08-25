#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
//#include<QString>
#include<QTcpSocket>
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void connectNetwork(QString,int);
    void receiveMessage();
    void breakConnect();
    void sendMess(QString,QString,bool);

signals:
    void connectedOK();
    void disconnectOK();
    void sendData(QByteArray);
    void showSendMess(QString);


private:
    QTcpSocket *sockect;

};

#endif // CLIENT_H
