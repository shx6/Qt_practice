#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"advancesetupdialog.h"
#include"server.h"
#include"client.h"
#include <QDebug>
#include <QNetworkInterface>
#include<QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QNetworkInterface *qni;
    qni = new QNetworkInterface();
    //qDebug()<<qni->allAddresses()[1].toString();
    ui->localIP->setText(qni->allAddresses()[1].toString());

    static int count=0; //  ui->receiveDataCount的计数




    //初始化

    QThread *t = new QThread;
    QThread *s=new QThread;

    Client *clients=new Client;
    clients->moveToThread(t);

    tcpSer=new QTcpServer(this);





    //客户端连接
    connect(this,&MainWindow::connect_client,clients,&Client::connectNetwork);
    connect(clients,&Client::connectedOK,this,[=](){
        ui->report->append(QDateTime::currentDateTime().time().toString("hh:mm:ss.zzz")+ "connect successfully,client  ") ;
        ui->sendButton->setDisabled(0);
        ui->stopButton->setDisabled(0);
        //qDebug()<<QDateTime::currentDateTime().time().toString("hh:mm:ss.zzz")+"connect successfully,client  ";
    });
    connect(this,&MainWindow::breakClientConnect,clients,&Client::breakConnect);
    connect(clients,&Client::disconnectOK,this,[=](){
        ui->report->append(QDateTime::currentDateTime().time().toString("hh:mm:ss.zzz")+"connect has been broken.") ;
        qDebug()<<QDateTime::currentDateTime().time().toString("hh:mm:ss.zzz")+"connect has been broken.";
        t->quit();
        t->wait();
        clients->deleteLater();
        t->deleteLater();
    });
    //
    connect(this,&MainWindow::connect_client,clients,&Client::receiveMessage);
    connect(clients,&Client::sendData,this,[=](QByteArray data){//显示接收的信息
        ui->receiveMess->append(QDateTime::currentDateTime().time().toString("hh:mm:ss.zzz")+"client receives message is "+data);
    });
    //connect(clients,&Client::showSendMess,this,[=](QString mess){   });//显示发送信息
    connect(this,&MainWindow::sendMessage2Serv,clients,&Client::sendMess);



    //服务器


    connect(tcpSer,&QTcpServer::newConnection,this,[=](){
        //qDebug()<<"connect have";
        QTcpSocket* socket = tcpSer->nextPendingConnection();

        static int i=0;
        ui->report->append( QDateTime::currentDateTime().time().toString("hh:mm:ss.zzz")+QString(" :The NO. %1 TCP socket %2 : %3 is accepted!").arg(i++).arg(socket->peerAddress().toString().mid(7)).arg(socket->peerPort()) );
        qDebug()<<socket->peerAddress();
        Server* server= new Server(socket);
        server->moveToThread(s);

        connect(socket, &QTcpSocket::disconnected, this, [=]()
        {
            qDebug()<<QDateTime::currentDateTime().time().toString("hh:mm:ss.zzz")+QString("The NO. 0 TCP socket 127.0.0.1:50464 is accepted!");
            s->exit();
            s->wait();
            s->deleteLater();
        });

        connect(server,&Server::showMess,this,[=](QByteArray data){
            ui->receiveMess->append(QDateTime::currentDateTime().time().toString("hh:mm:ss.zzz")+"        server:"+data);
        });
       // connect(this,&MainWindow::sendMessage2Serv,server,&Server::send);
        connect(this,&MainWindow::sendMessage2Serv,this,[=](QString mess){
            if(ui->workMode->currentText()=="tcp服务器")
                socket->write(mess.toUtf8());
        });



        s->start();
        server->receive();
    });



    t->start();




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{

    if(ui->startButton->text()=="打开"){
        QString ip=ui->destinationIP->text();
        int port=ui->destinationPort->text().toInt();
        if(ui->workMode->currentText() =="tcp客户端"){
            //qDebug()<<"okkkk";

            emit connect_client(ip,port);

        }
        else if (ui->workMode->currentText() == "tcp服务器") {

            int port = ui->localPort->text().toUShort();
            tcpSer->listen(QHostAddress::Any, port);
            ui->sendButton->setDisabled(0);
            ui->destinationIP->setDisabled(1);
            ui->destinationPort->setDisabled(1);
            ui->report->append(QDateTime::currentDateTime().time().toString("hh:mm:ss.zzz")+ QString(" : TCP listen at port %1 OK!").arg(ui->localPort->text()));
            //qDebug()<<QDateTime::currentDateTime().time().toString("hh:mm:ss.zzz")+ QString("TCP listen at port %1 OK!").arg(ui->localPort->text());

        }
        ui->startButton->setText("关闭");
    }
    else if (ui->startButton->text()=="关闭") {
        if(ui->workMode->currentText() =="tcp客户端"){
            emit breakClientConnect();
        }
        else if (ui->workMode->currentText() == "tcp服务器") {
            tcpSer->close();
        }
        ui->startButton->setText("打开");
    }

   qDebug()<<ui->workMode->currentText();
}

void MainWindow::on_stopButton_clicked()
{
    emit breakClientConnect();
}

void MainWindow::on_sendButton_clicked()
{
    QString mess=ui->sendMess->toPlainText();
    emit sendMessage2Serv(mess,ui->workMode->currentText());
    ui->sendMess->clear();
}

void MainWindow::on_clearButton_clicked()
{
    ui->report->clear();
}

void MainWindow::on_closeReport_stateChanged(int arg1)
{
    if(ui->closeReport->isChecked())
    {
    }
    else {
        ui->report;
    }
}

void MainWindow::on_workMode_activated(int index)
{
    if(index==0){
        ui->destinationIP->setDisabled(1);
        ui->destinationPort->setDisabled(1);
    }
    else if (index==1) {
        ui->destinationIP->setDisabled(0);
        ui->destinationPort->setDisabled(0);
    }
}

void MainWindow::on_advanceSetup_clicked()
{
    advanceSetupDialog *dlg=new advanceSetupDialog(this);
    // 模态, exec()
    // 阻塞程序的执行
    dlg->exec();
}
