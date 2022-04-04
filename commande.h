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
    int id_produit;
    int id_facture;

public:
    //constructeurs
    commandes();
    commandes(int, int, int, int);

    //getters
    int getId(){return id_commande;}
    int getQuantite(){return quantite;}
    int getidprod(){return id_produit;}
    int getidfact(){return id_facture;}


    //setters
    void setId(int i){id_commande=i;}
    void setQuantite(int m){quantite=m;}
    void setidprod(int p){id_produit=p;}
    void setidfact(int f){id_facture=f;}

    QSqlQueryModel *test(QString);


    //CRUD
    bool ajouter();
    QSqlQueryModel *afficheractif(QString);
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int id);

    //metier
    QSqlQueryModel *triquantite();
    QSqlQueryModel *recherche(QString);
};

#endif // COMMANDE_H
