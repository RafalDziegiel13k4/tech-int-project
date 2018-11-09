#include "mainwindow.h"
#include "ui_mainwindow.h"

QString MainWindow::onlineState;
QString MainWindow::webAnswer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    netReq.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

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

    netReq.setUrl(QUrl("http://" + confDial->webAddress + ":" + confDial->webPort + "/docs"));
    netManager->post(netReq, params.query(QUrl::FullyEncoded).toUtf8());
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

void MainWindow::clearDatabase()
{
    databaseId.clear();
    databaseName.clear();
    databaseStatus.clear();
    databaseModDate.clear();
}

void MainWindow::removeDatabaseItem(int index)
{
    databaseId.removeAt(index);
    databaseName.removeAt(index);
    databaseStatus.removeAt(index);
    databaseModDate.removeAt(index);
}

void MainWindow::processDatabase()
{
    QJsonDocument webDatabase = QJsonDocument::fromJson(webAnswer.toUtf8());
    QJsonArray jsonArray = webDatabase.array();
    readDatabase = false;

    this->clearDatabase();

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

void MainWindow::on_actionRefresh_triggered()
{
    ui->listWidget->clear();
    this->getDatabase();
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    ui->pushButtonView->setEnabled(true);
    ui->pushButtonEdit->setEnabled(true);
    ui->pushButtonDelete->setEnabled(true);

    selectedDocRow = index.row();
    ui->lineEditDate->setText(databaseModDate.at(selectedDocRow));
}

void MainWindow::on_pushButtonView_clicked()
{
    webDial->show();
}

void MainWindow::on_pushButtonEdit_clicked()
{
    webDial->show();
}

void MainWindow::on_pushButtonDelete_clicked()
{
    netReq.setUrl(QUrl("http://" + confDial->webAddress + ":" + confDial->webPort + "/docs/" + databaseId.at(selectedDocRow)));
    netManager->deleteResource(netReq);

    this->removeDatabaseItem(selectedDocRow);

    qDeleteAll(ui->listWidget->selectedItems());
}
