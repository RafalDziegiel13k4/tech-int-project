#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QDesktopWidget *desktop = QApplication::desktop();

    int middleWidth = (desktop->width() - w.width())/2;
    int middleHeight = (desktop->height() - w.height()-50)/2;
    w.move(middleWidth,middleHeight);
    w.show();

    return a.exec();
}
