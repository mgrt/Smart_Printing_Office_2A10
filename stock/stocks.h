#ifndef STOCKS_H
#define STOCKS_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStandardItemModel>
class Stocks
{
private:
    int id;
    QString Nom_produit;
    int id_Categorie;
    int prix;
    int Quantite;
   QString image;

public:
    Stocks();
    Stocks(int,QString,int,int,int,QString);
        Stocks(QString,int,int,int);
    int get_id(){return id;}
    QString get_NomProduit(){return Nom_produit; }
    int get_idCat(){return id_Categorie;}
    int get_prix(){return prix;}
    int get_Quantite(){return Quantite;}
void ajouter();
   QSqlQueryModel *afficher();
   QSqlQueryModel *Tri(QString x);
   QSqlQueryModel *Rech(QString x);
  QSqlQueryModel *test(QString);
   void Supprimer(int id);
   void Modifier(int id);
   void set_prix(int pr){prix=pr;}
};

#endif // STOCKS_H
