#ifndef MACHINE_H
#define MACHINE_H

#include <QMainWindow>
#include "QMessageBox"
#include <QTabWidget>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Machine
{
    int ID ;
    QString nom ;


public:
    //constructeur
    Machine();
    Machine( QString );
    //getter
    int get_ID(){return ID ;}
    QString get_nom(){return nom ;}
    //setter
    void set_nom(QString nom ){this->nom=nom;}
    //base de donnee
    bool ajouter();
    bool supprimer(int id);
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher_nom();
    void afficher_une_machines(int id,QString &nom );
    bool modifier_machine(int id );


};

#endif // MACHINE_H
