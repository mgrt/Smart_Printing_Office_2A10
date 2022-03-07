#include "factures.h"

factures::factures()
{

}

factures::factures(int id_facture, float montant, QString mode_paiement, QDate date_facture)
{
    this->id_facture=id_facture;
    this->montant=montant;
    this->mode_paiement=mode_paiement;
    this->date_facture=date_facture;
}

bool factures::ajouter()
{
    QSqlQuery query;

    QString id_string=QString::number(id_facture);
    QString montant_string=QString::number(montant);
      query.prepare("INSERT INTO factures ( id_facture, montant, mode_paiement, date_facture) "
                    "VALUES (FACTURES_SEQ.nextval,:montant,:mode_paiement,:date_facture)");
      query.bindValue(":id_facture", id_string);
      query.bindValue(":montant", montant_string);
      query.bindValue(":mode_paiement", mode_paiement);
      query.bindValue(":date_facture", date_facture);
      return query.exec();
}

QSqlQueryModel *factures::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from factures");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("montant"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("mode paiement"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date facture"));
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
      query.prepare("update factures set montant=:montant, mode_paiement=:mode_paiement,date_facture=:date_facture where id_facture=:id");
      query.bindValue(":id", res);
      query.bindValue(":montant", resmon);
      query.bindValue(":mode_paiement", mode_paiement);
      query.bindValue(":date_facture", date_facture);

      return query.exec();
}
QSqlQueryModel *factures::test(QString id)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM factures where id_facture like '"+id+"' ");
             setMontant(model->data(model->index(0, 1)).toInt());
             setMode_paiement(model->data(model->index(0, 2)).toString());
             setDate_facture(model->data(model->index(0, 3)).toDate());
    return model ;
}

