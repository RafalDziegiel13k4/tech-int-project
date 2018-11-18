#include "configdialog.h"
#include "ui_configdialog.h"

QString ConfigDialog::userName;
QString ConfigDialog::webAddress;
QString ConfigDialog::webPort;

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    this->on_buttonBox_accepted();
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::on_buttonBox_accepted()
{
    userName = ui->lineEditUser->text();
    webAddress = ui->lineEditAddress->text();
    webPort = QString::number(ui->spinBoxPort->value());
}
