#ifndef WEBVIEWERDIALOG_H
#define WEBVIEWERDIALOG_H

#include <QDialog>

namespace Ui {
class WebViewerDialog;
}

class WebViewerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WebViewerDialog(QWidget *parent = 0);
    ~WebViewerDialog();

private:
    Ui::WebViewerDialog *ui;
};

#endif // WEBVIEWERDIALOG_H
