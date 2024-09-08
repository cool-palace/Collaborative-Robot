#include "headers\mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Модель 6-осевого робота");
    w.show();
    return a.exec();
}
