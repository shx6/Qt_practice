#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QString>
#include<QThread>
#include<QTcpServer>
#include"advancesetupdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

static QByteArray stringToHex(QString s){
    //bool a;
    QByteArray temp1 = s.toLatin1().toHex();
    QByteArray temp2;
    for(int i = 0; i < temp1.length()/2;i++)
        {
            temp2 += temp1.mid(i*2,2) + " ";
        }
    return  temp2;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_sendButton_clicked();

    void on_clearButton_clicked();

    void on_closeReport_stateChanged(int arg1);

    void on_workMode_activated(int index);

    void on_advanceSetup_clicked();

    void on_sendGap_stateChanged(int arg1);

    void on_sendReceiveMode_activated(int index);

    void on_modifyName_clicked();

    void on_receiveAndReply_stateChanged(int arg1);

    void on_pushButton_3_clicked();

    void on_receiveFileOrsStop_stateChanged(int arg1);

    void on_clearWindow_clicked();

signals:
    void connect_client(QString,int,QString);
    void breakClientConnect();
    void sendMessage2Serv(QString,QString,bool);
    void sendfile(QString,QString);
    //void openSubThread();
private:
    Ui::MainWindow *ui;
    QTcpServer *tcpSer;
    advanceSetupDialog *dlg;
};
#endif // MAINWINDOW_H
