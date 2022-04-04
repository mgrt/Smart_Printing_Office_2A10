#include "factures.h"

factures::factures()
{

}

factures::factures(int id_facture, float montant, QString mode_paiement, QDateTime date_facture, int id_employe, int id_client)
{
    this->id_facture=id_facture;
    this->montant=montant;
    this->mode_paiement=mode_paiement;
    this->date_facture=date_facture;
    this->id_employe=id_employe;
    this->id_client=id_client;
}

bool factures::ajouter()
{
    QSqlQuery query;

    QString id_string=QString::number(id_facture);
    QString montant_string=QString::number(montant);
    QString id_Empstring=QString::number(id_employe);
    QString id_Cltstring=QString::number(id_client);
    QString numstring=QString::number(num);


      query.prepare("INSERT INTO factures ( id_facture, montant, mode_paiement, date_facture, id_employe, id_client, num) "
                    "VALUES (FACTURES_SEQ.nextval,:montant,:mode_paiement,:date_facture, :id_employe, :id_client, (select count(montant)+1 from factures))");
      query.bindValue(":id_facture", id_string);
      query.bindValue(":montant", montant_string);
      query.bindValue(":mode_paiement", mode_paiement);
      query.bindValue(":date_facture", date_facture);
      query.bindValue(":id_employe", id_Empstring);
      query.bindValue(":id_client", id_Cltstring);
      query.bindValue(":num", numstring);

          return query.exec();
      /* if(query.exec())
       {
           int id=query.value(0).toInt();
           return id;
       }*/
}

QSqlQueryModel *factures::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from factures");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("montant"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("mode paiement"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date facture"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("id employe"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("id client"));
    return model;
}

bool factures::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
      query.prepare("Delete from factures where id_facture=:id");
      query.bindValue(":id", res);

      return query.exec();
}

bool factures::modifier(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    QString resmon=QString::number(montant);
    QString resemp=QString::number(id_employe);
    QString resclt=QString::number(id_client);

      query.prepare("update factures set montant=:montant, mode_paiement=:mode_paiement,date_facture=:date_facture, id_employe=:id_employe, id_client=:id_client where id_facture=:id");
      query.bindValue(":id", res);
      query.bindValue(":montant", resmon);
      query.bindValue(":mode_paiement", mode_paiement);
      query.bindValue(":date_facture", date_facture);
      query.bindValue(":id_employe", resemp);
      query.bindValue(":id_client", resclt);

      return query.exec();
}
QSqlQueryModel *factures::test(QString id)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM factures where id_facture like '"+id+"' ");
             setMontant(model->data(model->index(0, 1)).toInt());
             setMode_paiement(model->data(model->index(0, 2)).toString());
             setDate_facture(model->data(model->index(0, 3)).toDateTime());
             setIdEmployefact(model->data(model->index(0, 4)).toInt());
             setIdClientfact(model->data(model->index(0, 5)).toInt());
    return model ;
}
QSqlQueryModel *factures::tridate()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM factures order by DATE_FACTURE");
             setMontant(model->data(model->index(0, 1)).toInt());
             setMode_paiement(model->data(model->index(0, 2)).toString());
             setDate_facture(model->data(model->index(0, 3)).toDateTime());
             setIdEmployefact(model->data(model->index(0, 4)).toInt());
             setIdClientfact(model->data(model->index(0, 5)).toInt());
    return model ;
}

 QSqlQueryModel *factures::recherche(QString rech)
 {
     QSqlQueryModel * model=new QSqlQueryModel();
      model->setQuery("SELECT * FROM factures where  ID_FACTURE like '"+rech+"' or MONTANT like '"+rech+"' or MODE_PAIEMENT like '"+rech+"' or DATE_FACTURE like '"+rech+"'  ");
               setMontant(model->data(model->index(0, 1)).toInt());
               setMode_paiement(model->data(model->index(0, 2)).toString());
               setDate_facture(model->data(model->index(0, 3)).toDateTime());
               setIdEmployefact(model->data(model->index(0, 4)).toInt());
               setIdClientfact(model->data(model->index(0, 5)).toInt());
      return model ;
 }

 bool factures::calcul(QString prixprodfquantite)
 {
     QSqlQuery query;
    //QString res=QString::number(id);
     QString resmon=QString::number(montant);
     QString resemp=QString::number(id_employe);
     QString resclt=QString::number(id_client);
     query.prepare("update factures set montant=:montant+'"+prixprodfquantite+"' where id_facture like (select max(id_facture) from factures)");

     query.bindValue(":montant", resmon);
     query.bindValue(":mode_paiement", mode_paiement);
     query.bindValue(":date_facture", date_facture);
     query.bindValue(":id_employe", resemp);
     query.bindValue(":id_client", resclt);

     return query.exec();
 }

