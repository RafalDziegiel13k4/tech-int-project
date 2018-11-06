#include "namedialog.h"
#include "ui_namedialog.h"

QString NameDialog::docName = "New Document";

NameDialog::NameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NameDialog)
{
    ui->setupUi(this);
}

NameDialog::~NameDialog()
{
    delete ui;
}

void NameDialog::update()
{
    docName = ui->lineEdit->text();
}
