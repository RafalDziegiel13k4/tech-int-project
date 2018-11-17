#ifndef WEBEDITORDIALOG_H
#define WEBEDITORDIALOG_H

#include <QDialog>
#include <QtWebEngine>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <iostream>

using namespace std;

namespace Ui {
class WebEditorDialog;
}

class WebEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WebEditorDialog(QWidget *parent = 0);
    ~WebEditorDialog();

private slots:
    void on_buttonBox_accepted();

    void showResults(QString text);

private:
    Ui::WebEditorDialog *ui;

    QString jQuery;

    QString jsEditorContent = "qt.jQuery('div.fr-view').html()";

    QWebEngineView *webView = new QWebEngineView(this);

    QWebEnginePage *webPage = new QWebEnginePage(this);
};

#endif // WEBEDITORDIALOG_H
