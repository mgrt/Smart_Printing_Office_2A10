#ifndef FACTURES_H
#define FACTURES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>
#include<QDialog>

class factures
{
    int id_facture;
    float montant;
    QString mode_paiement;
    QDateTime date_facture;
    int id_employe;
    int id_client;
    int num;
public:
    //constructeurs
    factures();
    factures(int, float, QString, QDateTime, int, int);

    //getters
    int getId(){return id_facture;}
    float getMontant(){return montant;}
    QString getMode_paiement(){return mode_paiement;}
    QDateTime getDate_facture(){return date_facture;}
    int getIdEmployefact(){return id_employe;}
    int getIdClientfact(){return id_client;}

    //setters
    void setId(int i){id_facture=i;}
    void setMontant(float m){montant=m;}
    void setMode_paiement(QString mp){mode_paiement=mp;}
    void setDate_facture(QDateTime d){date_facture=d;}
    void setIdEmployefact(int ie){id_employe= ie;}
    void setIdClientfact(int ic){id_client= ic;}

    QSqlQueryModel *test(QString);


    //CRUD
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int id);

    //metier*
     QSqlQueryModel *tridate();
     QSqlQueryModel *recherche(QString);
     bool calcul(QString);

};

#endif // FACTURES_H
