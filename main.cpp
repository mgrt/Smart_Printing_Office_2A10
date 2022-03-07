#include "mainwindow.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    if (test)
    {
         w.show();
    }
    else
    {
        w.warning();
    }

    return a.exec();
}
