#include "mainwindow.h"
#include <QApplication>
#include "client.h"
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Client c;
    c.show();

    Server server;
    server.startServer();

    return a.exec();
}
