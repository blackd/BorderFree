#include "mainwindow.h"
#include "borderfreeapp.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    BorderFreeApp a(argc, argv);
    //MainWindow w;
    //w.show();

    return a.exec();
}
