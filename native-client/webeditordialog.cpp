#include "webeditordialog.h"
#include "ui_webeditordialog.h"

WebEditorDialog::WebEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WebEditorDialog)
{
    ui->setupUi(this);
}

WebEditorDialog::~WebEditorDialog()
{
    delete ui;
}
