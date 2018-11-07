#include "mainwindow.h"
#include "ui_mainwindow.h"

QString MainWindow::onlineState;
QString MainWindow::webAnswer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusBar->showMessage("Status: " + onlineState);

    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(netManagerFinished(QNetworkReply*)));

    connect(nameDial, &NameDialog::accepted, this, &MainWindow::addDocument);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::netManagerFinished(QNetworkReply *netReply)
{
    if(netReply->error())
    {
        return;
    }

    webAnswer = netReply->readAll();
    cout << webAnswer.toStdString() << endl;
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionAbout_triggered()
{
    aboutDial->show();
}

void MainWindow::on_actionNew_Document_triggered()
{
    nameDial->show();
}

void MainWindow::addDocument()
{
    ui->listWidget->addItem(nameDial->docName);
}

void MainWindow::on_pushButtonDelete_clicked()
{
    qDeleteAll(ui->listWidget->selectedItems());
}

void MainWindow::on_actionConfig_triggered()
{
    confDial->show();
}

void MainWindow::on_pushButtonView_clicked()
{
    netReq.setUrl(QUrl("https://jsonplaceholder.typicode.com/todos/1"));
    netManager->get(netReq);
}
