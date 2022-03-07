#include "commande.h"

commandes::commandes()
{

}
commandes::commandes(int id_commande, int quantite)
{
    this->id_commande=id_commande;
    this->quantite=quantite;
}

bool commandes::ajouter()
{
    QSqlQuery query;

    QString id_string=QString::number(id_commande);
    QString quantite_string=QString::number(quantite);
      query.prepare("INSERT INTO  commandes ( ID_COMMANDE, QUANTITE) "
                    "VALUES (FACTURES_SEQ.nextval,:quantite)");
      query.bindValue(":id_commande", id_string);
      query.bindValue(":quantite", quantite_string);
      return query.exec();
}

QSqlQueryModel *commandes::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from commandes");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
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
      query.prepare("update commandes set quantite=:quantite where id_commande=:id");
      query.bindValue(":id", res);
      query.bindValue(":quantite", resmon);

      return query.exec();
}
QSqlQueryModel *commandes::test(QString id)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM commandes where id_commande like '"+id+"' ");
             setQuantite(model->data(model->index(0, 1)).toInt());
    return model ;
}
