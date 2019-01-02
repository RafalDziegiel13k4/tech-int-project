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

void WebViewerDialog::setPlaceholder(QString tempText)
{
    QString jsSetPlaceholder = QString("qt.jQuery('span.fr-placeholder').html('%1')").arg(tempText);
    webView->page()->runJavaScript(jsSetPlaceholder);
}

void WebViewerDialog::setContent(QString docText)
{
    QString jsSetContents = QString("qt.jQuery('div.fr-view').html('%1')").arg(docText);
    webView->page()->runJavaScript(jsSetContents);
}

void WebViewerDialog::prepareViewer(QString webText)
{
    webView->page()->runJavaScript(jQuery);
    webView->page()->runJavaScript(jsRemoveToolbar);
    webView->page()->runJavaScript(jsDisableEditor);
    webView->page()->runJavaScript(jsDisableEditing);
    this->setPlaceholder("");

    if(webText.isEmpty())
    {
        this->setContent(" ");
        return;
    }

    webText = webText.replace("\n","");
    this->setContent(webText);
}
