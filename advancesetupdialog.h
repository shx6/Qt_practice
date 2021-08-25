#ifndef ADVANCESETUPDIALOG_H
#define ADVANCESETUPDIALOG_H

#include <QDialog>

namespace Ui {
class advanceSetupDialog;
}

class advanceSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit advanceSetupDialog(QWidget *parent = nullptr);
    ~advanceSetupDialog();

private:
    Ui::advanceSetupDialog *ui;
};

#endif // ADVANCESETUPDIALOG_H
