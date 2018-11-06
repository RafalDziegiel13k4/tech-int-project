#include "mainwindow.h"
#include "ui_mainwindow.h"

QString MainWindow::onlineState = "Online";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusBar->showMessage("Status: " + onlineState);

    connect(nameDial, &NameDialog::accepted, this, &MainWindow::addDocument);
}

MainWindow::~MainWindow()
{
    delete ui;
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
