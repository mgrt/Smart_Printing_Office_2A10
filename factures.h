#ifndef FACTURES_H
#define FACTURES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include<QDialog>

class factures
{
    int id_facture;
    float montant;
    QString mode_paiement;
    QDate date_facture;
public:
    //constructeurs
    factures();
    factures(int, float, QString, QDate);

    //getters
    int getId(){return id_facture;}
    float getMontant(){return montant;}
    QString getMode_paiement(){return mode_paiement;}
    QDate getDate_facture(){return date_facture;}

    //setters
    void setId(int i){id_facture=i;}
    void setMontant(float m){montant=m;}
    void setMode_paiement(QString mp){mode_paiement=mp;}
    void setDate_facture(QDate d){date_facture=d;}

    QSqlQueryModel *test(QString);


    //CRUD
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int id);
};

#endif // FACTURES_H
