#include "webeditordialog.h"
#include "ui_webeditordialog.h"

QString WebEditorDialog::contentForSave;

WebEditorDialog::WebEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WebEditorDialog)
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

WebEditorDialog::~WebEditorDialog()
{
    delete ui;
}

void WebEditorDialog::setPlaceholder(QString tempText)
{
    QString jsSetPlaceholder = QString("qt.jQuery('span.fr-placeholder').html('%1')").arg(tempText);
    webView->page()->runJavaScript(jsSetPlaceholder);
}

void WebEditorDialog::setContent(QString docText)
{
    QString jsSetContents = QString("qt.jQuery('div.fr-view').html('%1')").arg(docText);
    webView->page()->runJavaScript(jsSetContents);
}

void WebEditorDialog::prepareEditor(QString webText)
{
    webView->page()->runJavaScript(jQuery);
    this->setPlaceholder("");

    webText = webText.replace("\n","");
    this->setContent(webText);
}

void WebEditorDialog::showResults(QString text)
{
    contentForSave = text;
    this->editingFinished();
}

void WebEditorDialog::on_buttonBox_accepted()
{
    webView->page()->runJavaScript(jQuery);
    webView->page()->runJavaScript(jsEditorContent, [&](const QVariant &v){ this->showResults(v.toString()); });
}
