#include "clients.h"

Clients::Clients()
{

}

Clients::Clients(int id_client, QString nom_client, QString prenom_client, QString genre_client, int num_telephone_client,
                 QString email_client, int cin_client, QDate date_naissance_client, QString nationalite_client)
{
    this->id_client=id_client;
    this->nom_client=nom_client;
    this->prenom_client=prenom_client;
    this->genre_client=genre_client;
    this->num_telephone_client=num_telephone_client;
    this->email_client=email_client;
    this->cin_client=cin_client;
    this->date_naissance_client=date_naissance_client;
    this->nationalite_client=nationalite_client;
}

bool Clients::ajouter_client()
{
    QSqlQuery query;
   // QString id_string = QString::number(id_client);


    query.prepare("INSERT INTO clients (id_client, nom_client, prenom_client, genre_client, num_telephone_client, email_client, cin_client, date_naissance_client, nationalite_client)"
                  "VALUES(CLIENTS_SEQ.nextval, :nom_client, :prenom_client, :genre_client, :num_telephone_client, :email_client, :cin_client, :date_naissance_client, :nationalite_client)");


        query.bindValue(":nom_client", nom_client);
        query.bindValue(":prenom_client", prenom_client);
        query.bindValue(":genre_client", genre_client);
        query.bindValue(":num_telephone_client", num_telephone_client);
        query.bindValue(":email_client", email_client);
        query.bindValue(":cin_client", cin_client);
        query.bindValue(":date_naissance_client", date_naissance_client);
        query.bindValue(":nationalite_client", nationalite_client);

        return query.exec();
}



QSqlQueryModel* Clients::afficher_client()
{
QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM clients");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_client"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom_client"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("genre_client"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("num_telephone_client"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("email_client"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("cin_client"));
  model->setHeaderData(7, Qt::Horizontal, QObject::tr("date_naissance_client"));
  model->setHeaderData(8, Qt::Horizontal, QObject::tr("nationalite_client"));


  return model;


}
bool Clients::supprimer_client(int i){
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENTS WHERE id_client=:id");
    query.bindValue(":id",i);
    return query.exec();
}
void Clients::recuperer_client(int id,QString &nom,QString &prenom,QString &genre,QString &num,QString &email,QString &cin,QDate &date,QString &nationalite)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM CLIENTS WHERE ID_CLIENT=:id");

        query.bindValue(":id", id);
        query.exec();
        query.next();
        nom = query.value(1).toString();
        prenom = query.value(2).toString();
        genre = query.value(3).toString();
        num = query.value(4).toString();
        email = query.value(5).toString();
        cin = query.value(6).toString();
        date = query.value(7).toDate();
        nationalite = query.value(8).toString();


}
bool Clients::modifier_client(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENTS SET NOM_CLIENT = :nom ,PRENOM_CLIENT = :prenom, GENRE_CLIENT = :genre, NUM_TELEPHONE_CLIENT = :num "
                  ",EMAIL_CLIENT = :email,CIN_CLIENT = :cin,DATE_NAISSANCE_CLIENT = :date,NATIONALITE_CLIENT = :nationalite WHERE id_client=:id");
    query.bindValue(":id",id);
    query.bindValue(":nom", nom_client);
    query.bindValue(":prenom", prenom_client);
    query.bindValue(":genre", genre_client);
    query.bindValue(":num", num_telephone_client);
    query.bindValue(":email", email_client);
    query.bindValue(":cin", cin_client);
    query.bindValue(":date", date_naissance_client);
    query.bindValue(":nationalite", nationalite_client);
    return query.exec();
}
QSqlQueryModel * Clients::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString example = rech ;
        bool ischar=false ;
        for (int i =0;i<example.size();i++)
        {
            if (example[i].isLetter())
                ischar=true;
        }

        QString select;
        if(ischar)
        {
            select = "select * from CLIENTS where regexp_like(NOM_CLIENT ,'"+rech+"') OR regexp_like(PRENOM_CLIENT ,'"+rech+"') OR regexp_like(GENRE_CLIENT ,'"+rech+"')"
                     " OR regexp_like(EMAIL_CLIENT ,'"+rech+"')  OR regexp_like(NATIONALITE_CLIENT ,'"+rech+"')  ";
        }
        else
        {
            select = "select *  from CLIENTS  where id_client='"+rech+"' or cin_client='"+rech+"' or num_telephone_client='"+rech+"' " ;
            //qInfo() << id.toInt() ;
        }

    model->setQuery(select);
    model->query().first();
    model->query().next();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_client"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom_client"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("genre_client"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("num_telephone_client"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("email_client"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("cin_client"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("date_naissance_client"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("nationalite_client"));
      return model;




}

QSqlQueryModel * Clients::trier(QString trie,QString ordre)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString select;
    select="select * from CLIENTS order by "+trie+" "+ordre+" ";
     model->setQuery(select);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_client"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom_client"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("genre_client"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("num_telephone_client"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("email_client"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("cin_client"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("date_naissance_client"));
     model->setHeaderData(8, Qt::Horizontal, QObject::tr("nationalite_client"));
       return model;


}

