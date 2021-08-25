#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QString>
#include<QThread>
#include<QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

signals:
    void connect_client(QString,int);
    void breakClientConnect();
    void sendMessage2Serv(QString,QString);

    //void openSubThread();
private:
    Ui::MainWindow *ui;
    QTcpServer *tcpSer;
};
#endif // MAINWINDOW_H
