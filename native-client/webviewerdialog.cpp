#include "webviewerdialog.h"
#include "ui_webviewerdialog.h"

WebViewerDialog::WebViewerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WebViewerDialog)
{
    ui->setupUi(this);
}

WebViewerDialog::~WebViewerDialog()
{
    delete ui;
}
