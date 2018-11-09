#ifndef WEBEDITORDIALOG_H
#define WEBEDITORDIALOG_H

#include <QDialog>
#include <QtWebEngine>
#include <QWebEngineView>
#include <QWebEnginePage>

namespace Ui {
class WebEditorDialog;
}

class WebEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WebEditorDialog(QWidget *parent = 0);
    ~WebEditorDialog();

private:
    Ui::WebEditorDialog *ui;

    QWebEngineView *webView = new QWebEngineView(this);
};

#endif // WEBEDITORDIALOG_H
