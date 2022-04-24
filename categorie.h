#ifndef CATEGORIE_H
#define CATEGORIE_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStandardItemModel>
class Categorie
{
private:
    int id_categorie;
    QString Nom_categorie;



public:
    Categorie();
    Categorie(int,QString);

    int get_idcat(){return id_categorie;}
    QString get_Nomcateg(){return Nom_categorie; }

void ajouter();
   QSqlQueryModel *afficher(QString x);


   void Supprimer(int id);
   void Modifier(int id);

};

#endif // CATEGORIE_H
