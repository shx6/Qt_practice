#ifndef ADVANCESETUPDIALOG_H
#define ADVANCESETUPDIALOG_H

#include <QDialog>
#include<QCloseEvent>

namespace Ui {
class advanceSetupDialog;
}

class advanceSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit advanceSetupDialog(QWidget *parent = nullptr);
    ~advanceSetupDialog();

private slots:


    void on_confirm_clicked();

    void on_cancel_clicked();

private:
    Ui::advanceSetupDialog *ui;
    int dataBit=8;
    QString check="NONE";
    int gapTime=0;
    QString passwd="";
    QString  plaintextHEX="";
    int receiveGap=500;
    QString heartbeat="";
    int heartbeatGap=0;
    //advanceSetupDialog predata;

protected:
    void closeEvent(QCloseEvent *) ;
};

#endif // ADVANCESETUPDIALOG_H
