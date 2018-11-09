#include "webeditordialog.h"
#include "ui_webeditordialog.h"

WebEditorDialog::WebEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WebEditorDialog)
{
    ui->setupUi(this);
    webView->setFixedWidth(1280);
    webView->setFixedHeight(674);
    webView->load(QUrl("http://www.qt.io/"));
}

WebEditorDialog::~WebEditorDialog()
{
    delete ui;
}
