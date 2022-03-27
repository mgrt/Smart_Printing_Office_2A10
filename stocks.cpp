#include "stocks.h"
#include "connection.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QtCharts/QPieSeries>
 Stocks::Stocks()
 {  id=0;
    Nom_produit="";
    id_Categorie=0;
    prix=0;
    Quantite=0;
    image="";

 }
 Stocks::Stocks(int id,QString nom_produit,int id_Categorie,int prix,int quantite,QString image)
 {
     this->id=id;
     this->Nom_produit=nom_produit;
     this->id_Categorie=id_Categorie;
     this->prix=prix;
     this->Quantite=quantite;
     this->image=image;

 }
     Stocks::Stocks(QString nom_produit,int id_Categorie,int prix,int quantite)
     {
         this->Nom_produit=nom_produit;
         this->id_Categorie=id_Categorie;
         this->prix=prix;
         this->Quantite=quantite;
     }

 void Stocks::ajouter()
 {
   QSqlQuery query;
    QString i_d= QString::number(id);
    QString i_c= QString::number(id_Categorie);
    QString pri= QString::number(prix);
    QString qua= QString::number(Quantite);

   query.prepare("INSERT INTO STOCKS (ID,NOM_PRODUIT,ID_CATEGORIE,PRIX,QUANTITE,IMAGE)"
                        "VALUES (STOCKS_SEQ.nextval,:nom_prod,:id_cat,:prix,:quantite,:image)");
  //   query.bindValue(":id",i_d);

        query.bindValue(":nom_prod",Nom_produit);
            query.bindValue(":id_cat",i_c);
              query.bindValue(":prix",pri);
              query.bindValue(":quantite",qua);
                query.bindValue(":image",image);
         query.exec();



 }
    QSqlQueryModel *Stocks::afficher()
    {
        QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select *from Stocks");
   model->setHeaderData(0,Qt::Horizontal,"ID");
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_PRODUIT"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("ID_CATEGORIE"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRIX"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("QUANTITE"));
return model;
    }

      void Stocks::Supprimer(int id)
      {
          QSqlQuery query;
          query.prepare("delete from  Stocks where id=:id");
               query.bindValue(":id",id);
                query.exec();

      }
 void Stocks::Modifier(int id)
 {
     QSqlQuery query;


      QString pri= QString::number(prix);
      QString qua= QString::number(Quantite);

     query.prepare("UPDATE Stocks SET NOM_PRODUIT=:nom,PRIX=:prix,QUANTITE=:quan WHERE ID=:ID");
          query.bindValue(":ID",id);
          query.bindValue(":nom",Nom_produit);

                query.bindValue(":prix",pri);
                query.bindValue(":quan",qua);
           query.exec();

 }

 QSqlQueryModel *Stocks::Tri(QString x)
 {
     QSqlQueryModel * model=new QSqlQueryModel();
 model->setQuery(x);
model->setHeaderData(0,Qt::Horizontal,"ID");
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_PRODUIT"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("ID_CATEGORIE"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRIX"));
 model->setHeaderData(4,Qt::Horizontal,QObject::tr("QUANTITE"));
  //model->setHeaderData(5,Qt::Horizontal,QObject::tr("Image"));
return model;

 }
    QSqlQueryModel *Stocks::Rech(QString x)
    {
        QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select *from Stocks where ID like '"+x+"' OR  NOM_PRODUIT like '%"+x+"%' Or ID_CATEGORIE like '"+x+"' OR  PRIX like '"+x+"' OR  QUANTITE like '"+x+"'  ");
   model->setHeaderData(0,Qt::Horizontal,"ID");
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_PRODUIT"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("ID_CATEGORIE"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRIX"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("QUANTITE"));
return model;

    }


  QSqlQueryModel *Stocks::test(QString id)
  { QSqlQueryModel * model=new QSqlQueryModel();
      model->setQuery("SELECT * FROM stocks where ID like '"+id+"' ");
            set_prix( model->data(model->index(0, 3)).toInt());
      return model ;
  }

  QSqlQueryModel *Stocks::count(QString id)
  {
      QSqlQueryModel * model=new QSqlQueryModel();
           model->setQuery(id);
                 set_stat( model->data(model->index(0, 0)).toInt());
           return model ;


  }



