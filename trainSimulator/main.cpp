#include "mainwindow.h"
#include <QApplication>

#include "tests/traintest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TrainTest mainTest;
    mainTest.testSetup();

    return a.exec();
}
