#ifndef NAMEDIALOG_H
#define NAMEDIALOG_H

#include <QDialog>

using namespace std;

namespace Ui {
class NameDialog;
}

class NameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NameDialog(QWidget *parent = 0);
    ~NameDialog();

    static QString docName;

private slots:

    void update();

private:
    Ui::NameDialog *ui;
};

#endif // NAMEDIALOG_H
