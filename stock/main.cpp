#include "mainwindow.h"
#include "connection.h"
#include <QSystemTrayIcon>
#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include "test.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    Connection c;
    bool test=c.ouvrirConnection();

    if(test)
    {
        emit w.test();

        w.show();
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
           notifyIcon->showMessage("succèses ","database open",QSystemTrayIcon::Information,15000);
        QMessageBox::information(nullptr, QObject::tr("database open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();}

