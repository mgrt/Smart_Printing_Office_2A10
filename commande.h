#ifndef COMMANDE_H
#define COMMANDE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include<QDialog>


class commandes
{
    int id_commande;
    int quantite;

public:
    //constructeurs
    commandes();
    commandes(int, int);

    //getters
    int getId(){return id_commande;}
    int getQuantite(){return quantite;}


    //setters
    void setId(int i){id_commande=i;}
    void setQuantite(int m){quantite=m;}

    QSqlQueryModel *test(QString);


    //CRUD
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int id);
};

#endif // COMMANDE_H
