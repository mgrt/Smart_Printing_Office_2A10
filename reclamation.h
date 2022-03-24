#ifndef RECLAMATION_H
#define RECLAMATION_H


#include <QVariant>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QMainWindow>
#include "QMessageBox"
#include <QTabWidget>
#include <QSqlQueryModel>


class reclamations
{

  int id_reclamation;
  int id_client;
  int id_facture;
  int id_employe;
  QString reclamation;



public:

  //Constructeurs
    reclamations();
    reclamations(int,int,int,int,QString);

  //Getters

    int getid_client(){return id_client;}
    int getid_facture(){return id_facture;}
    int getid_employe(){return id_employe;}
    QString getreclamation(){return reclamation;}



    //Setters
    void setid_client(int n){id_client=n;}
    void setid_facture(int p){id_facture=p;}
    void setid_employe(int g){id_employe=g;}
    void setreclamation(QString e){reclamation=e;}


    //Fonctionnalités
    bool ajouter_reclamation();
    QSqlQueryModel * afficher_reclamation();
    bool supprimer_reclamation(int);
    bool modifier_reclamation(int);
    void recuperer_reclamation(int id,int &client,int &facture,int &employe,QString &reclamation);
    QSqlQueryModel* afficher_employe();
    QSqlQueryModel *afficher_facture();
};
#endif // RECLAMATION_H
