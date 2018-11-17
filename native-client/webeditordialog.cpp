#include "webeditordialog.h"
#include "ui_webeditordialog.h"

WebEditorDialog::WebEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WebEditorDialog)
{
    QFile jQuerySrc;
    jQuerySrc.setFileName(":/js/webplugins/jquery.min.js");
    jQuerySrc.open(QIODevice::ReadOnly);
    jQuery = jQuerySrc.readAll();
    jQuery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
    cout << jQuery.toStdString() << endl;
    jQuerySrc.close();

    ui->setupUi(this);
    webView->setFixedWidth(1280);
    webView->setFixedHeight(674);
    webView->load(QUrl("qrc:/web_editor/web-editor-qt.html"));
}

WebEditorDialog::~WebEditorDialog()
{
    delete ui;
}

void WebEditorDialog::showResults(QString text)
{
    cout << text.toStdString() << endl;
}

void WebEditorDialog::on_buttonBox_accepted()
{
    webView->page()->runJavaScript(jQuery);
    webView->page()->runJavaScript(jsEditorContent, [&](const QVariant &v){ this->showResults(v.toString()); });
}
