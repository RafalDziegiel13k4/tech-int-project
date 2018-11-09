#include "mainwindow.h"
#include "ui_mainwindow.h"

QString MainWindow::onlineState;
QString MainWindow::webAnswer;

bool readDatabase;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    netReq.setUrl(QUrl("http://" + confDial->webAddress + ":" + confDial->webPort + "/docs"));
    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(netManagerFinished(QNetworkReply*)));
    connect(nameDial, &NameDialog::accepted, this, &MainWindow::addDocument);
    this->getDatabase();
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
        onlineState = "Offline";
        ui->statusBar->showMessage("Status: " + onlineState);
        return;
    }

    onlineState = "Online";
    ui->statusBar->showMessage("Status: " + onlineState);
    webAnswer = netReply->readAll();

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
    QUrlQuery params;
    params.addQueryItem("name", nameDial->docName);

    netReq.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    netManager->post(netReq, params.query(QUrl::FullyEncoded).toUtf8());
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
    netManager->get(netReq);
}

void MainWindow::processDatabase()
{
    QJsonDocument webDatabase = QJsonDocument::fromJson(webAnswer.toUtf8());
    QJsonArray jsonArray = webDatabase.array();
    readDatabase = false;

    foreach(const QJsonValue &jsonValue, jsonArray)
    {
        QJsonObject jsonObject = jsonValue.toObject();

        databaseId.append(jsonObject["_id"].toString());
        databaseName.append(jsonObject["name"].toString());
        databaseStatus.append(jsonObject["status"].toString());
        databaseModDate.append(jsonObject["Modification_date"].toString());
    }

    for(int i = 0; i < jsonArray.size(); i++)
    {
        ui->listWidget->addItem(databaseName.at(i));
    }
}

void MainWindow::on_pushButtonView_clicked()
{

}

void MainWindow::on_actionRefresh_triggered()
{
    ui->listWidget->clear();
    this->getDatabase();
}
