#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <iostream>
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

    static QString webAnswer;

private slots:
    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionNew_Document_triggered();

    void on_pushButtonDelete_clicked();

    void on_actionConfig_triggered();

    void on_pushButtonView_clicked();

    void netManagerFinished(QNetworkReply *netReply);

    void getDatabase();

    void processDatabase();

    void addDocument();

    void on_actionRefresh_triggered();

private:
    Ui::MainWindow *ui;

    AboutDialog *aboutDial = new AboutDialog;

    NameDialog *nameDial = new NameDialog;

    ConfigDialog *confDial = new ConfigDialog;

    QNetworkAccessManager *netManager = new QNetworkAccessManager;

    QNetworkRequest netReq;

    QJsonDocument *jsonDoc = new QJsonDocument;
};

#endif // MAINWINDOW_H
