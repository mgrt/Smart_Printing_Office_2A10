#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QVariant>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QMainWindow>
#include "QMessageBox"
#include <QTabWidget>
#include <QSqlQueryModel>
#include<QDebug>


class Maintenance
{
    int ID_maintenance , ID_machine ;
    QString description ;
    QDate date ;



public:
    //constructeur

    Maintenance();
    Maintenance( int , QString , QDate );

    //getter

    int get_ID_maintenance(){return ID_maintenance ;}
    int get_ID_machine(){return ID_machine ;}
    QDate get_date(){return date ;}
    QString get_description(){return description ;}

    //setter

     void set_ID_machine(int ID_machine){this->ID_machine=ID_machine ;}
     void set_date(QDate date){this->date=date ;}
     void set_description(QString description){this->description=description ;}

     //base de donnee

     QSqlQueryModel * recherche_par_machine(QString id );
     bool ajouter();
     bool supprimer(int id);
     QSqlQueryModel * afficher(int);
     void afficher_une_maintenances(int id,int &id_machine ,QDate &date,QString &desc);
     bool modifier_maintenances(int id );

};

#endif // MAINTENANCE_H
