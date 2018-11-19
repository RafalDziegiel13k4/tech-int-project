#ifndef WEBVIEWERDIALOG_H
#define WEBVIEWERDIALOG_H

#include <QDialog>
#include <QtWebEngine>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <iostream>

using namespace std;

namespace Ui {
class WebViewerDialog;
}

class WebViewerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WebViewerDialog(QWidget *parent = 0);
    ~WebViewerDialog();

public slots:
    void prepareViewer(QString webText);

    void setPlaceholder(QString tempText);

    void setContent(QString docText);

private:
    Ui::WebViewerDialog *ui;

    QFile jQuerySrc;

    QString jQuery;

    QString jsRemoveToolbar = "qt.jQuery('div.fr-toolbar').remove()";

    QString jsDisableEditing = "qt.jQuery('div.fr-view').attr('contenteditable','false')";

    QWebEngineView *webView = new QWebEngineView(this);
};

#endif // WEBVIEWERDIALOG_H
