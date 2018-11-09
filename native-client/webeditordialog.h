#ifndef WEBEDITORDIALOG_H
#define WEBEDITORDIALOG_H

#include <QDialog>

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
};

#endif // WEBEDITORDIALOG_H
