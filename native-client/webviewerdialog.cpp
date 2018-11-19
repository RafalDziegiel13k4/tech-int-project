#include "webviewerdialog.h"
#include "ui_webviewerdialog.h"

WebViewerDialog::WebViewerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WebViewerDialog)
{
    jQuerySrc.setFileName(":/js/webplugins/jquery.min.js");
    jQuerySrc.open(QIODevice::ReadOnly);
    jQuery = jQuerySrc.readAll();
    jQuery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
    jQuerySrc.close();

    ui->setupUi(this);
    webView->setFixedWidth(1280);
    webView->setFixedHeight(674);
    webView->load(QUrl("qrc:/web_editor/web-editor-qt.html"));
}

WebViewerDialog::~WebViewerDialog()
{
    delete ui;
}

void WebViewerDialog::prepareViewer()
{
    webView->page()->runJavaScript(jQuery);
    webView->page()->runJavaScript(jsRemoveToolbar);
    webView->page()->runJavaScript(jsDisableEditing);
    webView->page()->runJavaScript(jsSetPlaceholder);
    webView->setEnabled(false);
}
