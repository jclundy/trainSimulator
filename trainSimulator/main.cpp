#include "mainwindow.h"
#include <QApplication>

#include "tests/traintest.h"
#include "tests/tracksystemtest.h"

#define RUN_BASIC_TEST 0
#define RUN_SYSTEM_TEST 1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

#if RUN_BASIC_TEST
    TrainTest mainTest;
    mainTest.runTests();
#endif

#if RUN_SYSTEM_TEST
    TrackSystemTest test;
    test.runTests();
#endif

    return a.exec();
}
