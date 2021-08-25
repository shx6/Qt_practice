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
