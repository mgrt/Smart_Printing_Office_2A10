#include "commande.h"
#include <iostream>

commandes::commandes()
{

}
commandes::commandes(int id_commande, int quantite, int id_produit , int id_facture)
{
    this->id_commande=id_commande;
    this->quantite=quantite;
    this->id_produit=id_produit;
    this->id_facture=id_facture;
}

bool commandes::ajouter()
{
    QSqlQuery query;
 std::cout<<id_facture<<" id ajout "<<std::endl;
    QString id_string=QString::number(id_commande);
    QString quantite_string=QString::number(quantite);
    QString idprod_string=QString::number(id_produit);
    QString idfact_string=QString::number(id_facture);
      query.prepare("INSERT INTO  commandes ( ID_COMMANDE, QUANTITE, id_produit, id_facture) "
                    "VALUES (COMMANDES_SEQ.nextval,:quantite,:id_produit,:id_facture)");
      query.bindValue(":id_commande", id_string);
      query.bindValue(":quantite", quantite_string);
      query.bindValue(":id_produit", idprod_string);
      query.bindValue(":id_facture", idfact_string);
      return query.exec();
}

QSqlQueryModel *commandes::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from commandes");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID commande"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("quantite"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("produit"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("id facture"));
    return model;
}

QSqlQueryModel *commandes::afficheractif(QString id)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select s.nom_produit, c.quantite, s.prix \"prix unitaire\", c.quantite*s.prix \"total de cet article\"  from commandes c join stocks s on c.id_produit=s.id_produit where id_facture like '"+id+"'");

    //model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID commande"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom produit"));
    //model->setHeaderData(2,Qt::Horizontal,QObject::tr("id facture"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("quantite"));
    return model;
}

bool commandes::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
      query.prepare("Delete from commandes where id_commande=:id");
      query.bindValue(":id", res);

      return query.exec();
}

bool commandes::modifier(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    QString resmon=QString::number(quantite);
    QString resprod=QString::number(id_produit);
    QString resfact=QString::number(id_facture);
      query.prepare("update commandes set quantite=:quantite, id_produit=:id_produit, id_facture=:id_facture where id_commande=:id");
      query.bindValue(":id", res);
      query.bindValue(":quantite", resmon);
      query.bindValue(":id_produit", resprod);
      query.bindValue(":id_facture", resfact);

      return query.exec();
}
QSqlQueryModel *commandes::test(QString id)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM commandes where id_commande like '"+id+"' ");
             setQuantite(model->data(model->index(0, 1)).toInt());
             setidprod(model->data(model->index(0, 2)).toInt());
             setidfact(model->data(model->index(0, 3)).toInt());
    return model ;
}

QSqlQueryModel *commandes::triquantite()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM commandes order by quantite");
        setQuantite(model->data(model->index(0, 1)).toInt());
        setidprod(model->data(model->index(0, 2)).toInt());
        setidfact(model->data(model->index(0, 3)).toInt());
    return model ;
}
QSqlQueryModel *commandes::recherche(QString rech)
{
    QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM commandes where  ID_commande like '"+rech+"' or quantite like '"+rech+"' or ID_PRODUIT like '"+rech+"' or ID_FACTURE like '"+rech+"'  ");
              setQuantite(model->data(model->index(0, 1)).toInt());
              setidprod(model->data(model->index(0, 2)).toInt());
              setidfact(model->data(model->index(0, 3)).toInt());

     return model ;
}
