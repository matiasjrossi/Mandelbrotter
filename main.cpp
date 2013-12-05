#include <QtGui/QApplication>
#include "mainwindow.h"
#include "logger.h"

int main(int argc, char *argv[])
{
    Logger::init("mandelbrotter.log", Logger::QUIET);
    Logger::get()->output("Starting Mandelbrotter ;)");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.init();
    return a.exec();
}
