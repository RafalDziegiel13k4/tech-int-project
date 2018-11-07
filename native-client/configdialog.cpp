#include "configdialog.h"
#include "ui_configdialog.h"

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
    webAddress = ui->lineEditAddress->text();
    webPort = QString::number(ui->spinBoxPort->value());
}
