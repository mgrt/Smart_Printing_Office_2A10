#include "categorie.h"
#include "connection.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
 Categorie::Categorie()
 {

 }
 Categorie::Categorie(int id,QString nom)
 {
     this->id_categorie=id;
     this->Nom_categorie=nom;

 }
 void Categorie::ajouter()
 {
     QSqlQuery query;
      QString i_d= QString::number(id_categorie);



     query.prepare("INSERT INTO categorie (ID_CATEGORIE,NOM_CATEGORIE)"
                          "VALUES (CATEGORIE_SEQ.nextval,:nom_cat)");
    //   query.bindValue(":id",i_d);
          query.bindValue(":id",i_d);
              query.bindValue(":nom_cat",Nom_categorie);

           query.exec();


 }

 QSqlQueryModel *Categorie::afficher(QString x){
 QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery(x);
model->setHeaderData(0,Qt::Horizontal,"ID_categorie");
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_Categorie"));

return model;

 }
 void Categorie::Supprimer(int id)
 {
     QSqlQuery query;
     query.prepare("delete from  categorie where ID_CATEGORIE=:id");
          query.bindValue(":id",id);
           query.exec();
 }
 void Categorie::Modifier(int id){
 QSqlQuery query;




 query.prepare("UPDATE categorie SET  NOM_CATEGORIE=:nom WHERE ID_CATEGORIE=:ID");
      query.bindValue(":ID",id);
      query.bindValue(":nom",Nom_categorie);

       query.exec();


}



