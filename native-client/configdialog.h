#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

using namespace std;

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

    static QString webAddress;

    static QString webPort;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ConfigDialog *ui;
};

#endif // CONFIGDIALOG_H
