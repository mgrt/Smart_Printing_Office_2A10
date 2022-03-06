#include "maintenance.h"

Maintenance::Maintenance()
{
description="";
date = QDate::currentDate() ;
}

Maintenance::Maintenance(int ID_machine ,  QString description , QDate date )
{
    this->description=description;
    this->date=date;
    this->ID_machine=ID_machine;
}

bool Maintenance::ajouter()
{
   QSqlQuery query ;

   query.prepare("insert into MAINTENANCES values (MAINTENANCES_SEQ.nextval , :date_maintenance ,:description_maintenance,:id_machine)");
   query.bindValue(":date_maintenance",date);
   query.bindValue(":description_maintenance",description);
   query.bindValue(":id_machine",ID_machine);

   return query.exec();
}

QSqlQueryModel * Maintenance::afficher()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from MAINTENANCES");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_maintenance"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("date_maintenance"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("description_maintenance"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("id_machine"));

return model;
}

QSqlQueryModel * Maintenance::recherche_par_machine(QString id )
{
    QSqlQueryModel * model=new QSqlQueryModel();


    QString example = id ;
    bool ischar=false ;
    for (int i =0;i<example.size();i++)
    {
        if (example[i].isLetter())
            ischar=true;
    }

    QString select;
    if(ischar)
    {
        select = "select * from MAINTENANCES where regexp_like(description_maintenance ,'"+id+"') or  id_machine in (select id_machine from machines where regexp_like(nom_machine ,'"+id+"') )  ";
    }
    else
    {
        select = "select * from MAINTENANCES where id_machine like "+id+" or id_maintenance like "+id+" " ;
        //qInfo() << id.toInt() ;
    }


    model->query().first();
    model->query().next();
    model->setQuery(select);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_maintenance"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("date_maintenance"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("description_maintenance"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("id_machine"));

    return model;
}

void Maintenance::afficher_une_maintenances(int id,int &id_machine ,QDate &date,QString &desc)
{

    QSqlQuery query ;
    query.prepare("select * from MAINTENANCES where id_maintenance = :id ");
    query.bindValue(":id",id);
    query.exec();
    query.next();



    id_machine = query.value(3).toInt();
    date = query.value(1).toDate();
    desc = query.value(2).toString();

}

    bool Maintenance::modifier_maintenances(int id)
{
    QSqlQuery query ;

    query.prepare("update maintenances set date_maintenance=:date , description_maintenance=:text , id_machine=:id_m where id_maintenance=:id ");
    query.bindValue(":date",date);
    query.bindValue(":text",description);
    query.bindValue(":id_m", ID_machine);
    query.bindValue(":id",id);

    return query.exec();

}


bool Maintenance::supprimer(int id )
{
    QSqlQuery query ;
    query.prepare("Delete from maintenances where ID_maintenance= :id");

    query.bindValue(":id" , id) ;
    return  query.exec();

}
