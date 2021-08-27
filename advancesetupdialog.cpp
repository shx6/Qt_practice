#include "advancesetupdialog.h"
#include "ui_advancesetupdialog.h"

advanceSetupDialog::advanceSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::advanceSetupDialog)
{
    ui->setupUi(this);
}

advanceSetupDialog::~advanceSetupDialog()
{
    delete ui;
}

//关闭按钮
void advanceSetupDialog::on_cancel_clicked()
{
    ui->dataBits->setCurrentText(QString::number(this->dataBit));
    ui->check->setCurrentText(this->check);
    ui->gapTime->setText(QString::number( this->gapTime));
    ui->passwd->setText(this->passwd);
    ui->plaintextHEX->setText(this->plaintextHEX);
    ui->receiveGap->setText(QString::number( this->receiveGap));
    ui->heartbeat->setText(this->heartbeat);
    ui->heartbeatGap->setText( QString::number( this->heartbeatGap));
    this->close();

}

void  advanceSetupDialog::closeEvent(QCloseEvent *ev)
{
    ui->cancel->click();
}

//   确定按钮
//void advanceSetupDialog::on_pushButton_2_clicked()


void advanceSetupDialog::on_confirm_clicked()
{

    this->dataBit=ui->dataBits->currentText().toUInt();
    this->check=ui->check->currentText();
    this-> gapTime= ui->gapTime->text().toUInt();
    this->passwd=ui->passwd->text();
    this-> plaintextHEX=ui->plaintextHEX->text();
    this->receiveGap=ui->receiveGap->text().toUInt();
    this->heartbeat=ui->heartbeat->text();
    this->heartbeatGap=ui->heartbeatGap->text().toUInt();
    this->close();
}
