#include "mainwindow.h"
#include "ui_mainwindow.h"

QString MainWindow::onlineState;
QString MainWindow::webAnswer;
//QString MainWindow::webDatabase;

bool readDatabase;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(netManagerFinished(QNetworkReply*)));
    this->getDatabase();



    ui->statusBar->showMessage("Status: " + onlineState);
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
        webAnswer = "";
        return;
    }

    webAnswer = netReply->readAll();
    //cout << webAnswer.toStdString() << endl;

    if(readDatabase) this->processDatabase();
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

void MainWindow::getDatabase()
{
    readDatabase = true;
    netReq.setUrl(QUrl("http://" + confDial->webAddress + ":" + confDial->webPort + "/docs"));
    netManager->get(netReq);
}

void MainWindow::processDatabase()
{
    QJsonDocument webDatabase = QJsonDocument::fromJson(webAnswer.toUtf8());
    QJsonArray jsonArray = webDatabase.array();
    readDatabase = false;

    foreach (const QJsonValue &val, jsonArray)
    {
        QString docName = val.toObject().value("name").toString();
        ui->listWidget->addItem(docName);
    }
}

void MainWindow::on_pushButtonView_clicked()
{

}
