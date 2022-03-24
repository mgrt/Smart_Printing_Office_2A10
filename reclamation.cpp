#include "reclamation.h"

reclamations::reclamations()
{

}
reclamations::reclamations(int id_reclamation,int id_client,int id_facture,int id_employe,QString reclamation)
{
    this->id_reclamation=id_reclamation;
    this->id_client=id_client;
    this->id_facture=id_facture;
    this->id_employe=id_employe;
    this->reclamation=reclamation;

}

bool reclamations::ajouter_reclamation()
{
    QSqlQuery query;
   // QString id_string = QString::number(id_reclamation);


    query.prepare("INSERT INTO reclamations (id_reclamation, id_client, id_facture, id_employe, reclamation)"
                  "VALUES(RECLAMATIONS_SEQ2.nextval, :id_client, :id_facture, :id_employe, :reclamation)");


        query.bindValue(":id_client", id_client);
        query.bindValue(":id_facture", id_facture);
        query.bindValue(":id_employe", id_employe);
        query.bindValue(":reclamation", reclamation);


        return query.exec();
}



QSqlQueryModel* reclamations::afficher_reclamation()
{
QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM reclamations");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_reclamation"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("id_client"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("id_facture"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("id_employe"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("reclamation"));


  return model;


}
QSqlQueryModel* reclamations::afficher_employe()
{
QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT id_employe FROM employee");


  return model;


}
QSqlQueryModel *reclamations::afficher_facture()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from factures");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("montant"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("mode paiement"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date facture"));
    return model;
}

bool reclamations::supprimer_reclamation(int i){
    QSqlQuery query;
    query.prepare("DELETE FROM reclamations WHERE id_reclamation=:id");
    query.bindValue(":id",i);
    return query.exec();
}
void reclamations::recuperer_reclamation(int id,int &client,int &facture,int &employe,QString &reclamation)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM reclamationS WHERE ID_reclamation=:id");

        query.bindValue(":id", id);
        query.exec();
        query.next();
        client = query.value(1).toInt();
        facture = query.value(2).toInt();
        employe = query.value(3).toInt();
        reclamation = query.value(4).toString();



}
bool reclamations::modifier_reclamation(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE reclamations SET id_client = :client ,id_facture = :facture, id_employe = :employe, reclamation = :reclamation where id_reclamation=:id");
    query.bindValue(":id",id);
    query.bindValue(":client", id_client);
    query.bindValue(":facture", id_facture);
    query.bindValue(":employe", id_employe);
    query.bindValue(":reclamation", reclamation);

    return query.exec();
}
