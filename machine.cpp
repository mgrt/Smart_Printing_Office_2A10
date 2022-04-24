#include "machine.h"

Machine::Machine()
{
    nom="";
}
Machine::Machine( QString nom)
{
    this->nom=nom;
}


bool Machine::ajouter()
{
   QSqlQuery query ;

   query.prepare("insert into MACHINES values (MACHINES_SEQ.nextval , :nom)");
   query.bindValue(":nom",nom);

   return query.exec();
}


QSqlQueryModel * Machine::afficher()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from MACHINES");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_machine"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom_machine"));

return model;

}


 QSqlQueryModel * Machine::afficher_nom()
 {

     QSqlQueryModel * model=new QSqlQueryModel();

     model->setQuery("select id_machine from MACHINES");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_machine"));

     return model;
 }

 void Machine::afficher_une_machines(int id,QString &name )
 {
     QSqlQuery query ;

     query.prepare("select * from machines where id_machine = :id ");
     query.bindValue(":id",id);
     query.exec();
     query.next();

    name = query.value(1).toString();

 }

 bool Machine::modifier_machine(int id )
 {
     QSqlQuery query ;

     query.prepare("update machines set nom_machine=:nom where id_machine=:id ");
     query.bindValue(":nom",nom);
     query.bindValue(":id",id);

     return query.exec();
 }

 bool Machine::supprimer(int id)
 {
     QSqlQuery query ;
     query.prepare("Delete from machines where ID_machine= :id");
     query.bindValue(":id" , id) ;
     return  query.exec();
 }
