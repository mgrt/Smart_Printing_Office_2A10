#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QTranslator>
#include <QInputDialog>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator T;
    QStringList langues;
    langues << "French" << "English"<<"Arabic";
    const QString langue =QInputDialog::getItem(NULL,"Language","Select a language",langues);
    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    w.langue=langue;
    if (test)
    {
        if(langue =="English")
        {   qInfo()<<langue;
            T.load(":/anglais.qm");
        }else if(langue =="Arabic")
        {
            T.load(":/arabe.qm");
        }
        if(langue != "French")
        {
            a.installTranslator(&T);
        }

         w.show();
    }
    else
    {
        w.warning();
    }

    return a.exec();
}
