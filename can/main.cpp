
#include "mainwindow.h"
#include <QApplication>
#include"bmswindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   // bmswindow w;
    w.show();

    return a.exec();
}
