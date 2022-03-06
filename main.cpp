#include "mainwindow.h"
#include "connection.h"
#include <QTabWidget>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test = c.createconnect();
    MainWindow w;
    if(test)
    {

        w.update_output_data();
        w.show();
        w.initialisation_demarage();
    }
    else
 w.warning();



    return a.exec();
}
