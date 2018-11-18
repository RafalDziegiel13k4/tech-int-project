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
    connect(webEditDial, &WebEditorDialog::accepted, this, &MainWindow::saveDocument);
    connect(webEditDial, &WebEditorDialog::rejected, this, &MainWindow::editingFinished);

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
    params.addQueryItem("user", confDial->userName);

    netReq.setUrl(QUrl("http://" + confDial->webAddress + ":" + confDial->webPort + "/docs"));
    netManager->post(netReq, params.query(QUrl::FullyEncoded).toUtf8());
}

void MainWindow::saveDocument()
{
    //save doc contents here
    this->editingFinished();
}

void MainWindow::editingFinished()
{
    QUrlQuery params;
    params.addQueryItem("status", "free");
    params.addQueryItem("user", confDial->userName);
    netManager->put(netReq, params.query(QUrl::FullyEncoded).toUtf8());
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
    databaseUser.clear();
    databaseModDate.clear();
}

void MainWindow::removeDatabaseItem(int index)
{
    databaseId.removeAt(index);
    databaseName.removeAt(index);
    databaseStatus.removeAt(index);
    databaseUser.removeAt(index);
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
        databaseUser.append(jsonObject["user"].toString());
        databaseModDate.append(jsonObject["modification_date"].toString());
    }

    ui->listWidget->clear();

    for(int i = 0; i < jsonArray.size(); i++)
    {
        ui->listWidget->addItem(databaseName.at(i));
    }

    ui->listWidget->setCurrentRow(-1);
}

void MainWindow::on_actionRefresh_triggered()
{
    this->getDatabase();
}

void MainWindow::enableButtons(bool enabled)
{
    ui->pushButtonView->setEnabled(enabled);
    ui->pushButtonEdit->setEnabled(enabled);
    ui->pushButtonDelete->setEnabled(enabled);
}

void MainWindow::on_pushButtonView_clicked()
{
    webViewDial->prepareViewer();
    webViewDial->show();
}

void MainWindow::on_pushButtonEdit_clicked()
{
    QUrlQuery params;
    params.addQueryItem("status", "used");

    netReq.setUrl(QUrl("http://" + confDial->webAddress + ":" + confDial->webPort + "/docs/" + databaseId.at(selectedDocRow)));
    netManager->put(netReq, params.query(QUrl::FullyEncoded).toUtf8());
    webEditDial->show();
}

void MainWindow::on_pushButtonDelete_clicked()
{
    netReq.setUrl(QUrl("http://" + confDial->webAddress + ":" + confDial->webPort + "/docs/" + databaseId.at(selectedDocRow)));
    netManager->deleteResource(netReq);

    this->removeDatabaseItem(selectedDocRow);
    ui->listWidget->setCurrentRow(-1);
    ui->listWidget->takeItem(selectedDocRow);
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    if(currentRow >= 0)
    {
        selectedDocRow = currentRow;
        ui->lineEditAuthor->setText(databaseUser.at(selectedDocRow));
        ui->lineEditDate->setText(databaseModDate.at(selectedDocRow));

        this->enableButtons(true);
    }
    else
    {
        ui->lineEditAuthor->clear();
        ui->lineEditDate->clear();
        this->enableButtons(false);
    }
}
