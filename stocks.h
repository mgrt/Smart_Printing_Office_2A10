#ifndef STOCKS_H
#define STOCKS_H
#include <QString>
#include <QSqlDatabase>
#include <QGraphicsWidget>
#include <QSqlError>
#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

class Stocks
{
private:
    int id;
    QString Nom_produit;
    int id_Categorie;
    int prix;
    int Quantite;
   QString image;
   int stat;

public:
    Stocks();
    Stocks(int,QString,int,int,int,QString);
        Stocks(QString,int,int,int);
    int get_id(){return id;}
    QString get_NomProduit(){return Nom_produit; }
    int get_idCat(){return id_Categorie;}
    int get_prix(){return prix;}
    int get_Quantite(){return Quantite;}
    int get_stat(){return stat;}
void ajouter();
   QSqlQueryModel *afficher();
   QSqlQueryModel *Tri(QString x);
   QSqlQueryModel *Rech(QString x);
  QSqlQueryModel *test(QString);
    QSqlQueryModel *count(QString);
   void Supprimer(int id);
   void Modifier(int id);
   void set_prix(int pr){prix=pr;}
   void set_nomproduit(QString nom){Nom_produit=nom;}
   void set_Quantiter(int quantit){Quantite=quantit;}
   void set_stat(int st){stat=st;}

};

#endif // STOCKS_H
