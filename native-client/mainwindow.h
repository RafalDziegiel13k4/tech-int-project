#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aboutdialog.h"
#include "namedialog.h"
#include "configdialog.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static QString onlineState;

private slots:
    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionNew_Document_triggered();

    void addDocument();

    void on_pushButtonDelete_clicked();

    void on_actionConfig_triggered();

private:
    Ui::MainWindow *ui;

    AboutDialog *aboutDial = new AboutDialog;

    NameDialog *nameDial = new NameDialog;

    ConfigDialog *confDial = new ConfigDialog;
};

#endif // MAINWINDOW_H
