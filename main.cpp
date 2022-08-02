#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QtEndian>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    a.setWindowIcon(QIcon("://icon.png"));

    MainWindow w;
    w.show();

    qDebug()<<qToBigEndian(83);

    return a.exec();
}
