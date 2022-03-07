#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
#include <QDate>
#include <QMessageBox>
#include <QList>

Employe::Employe()
{    

}

Employe::Employe(int CIN,QString nom,QString prenom,QString sexe,QString role,QDate date_naissance,QString nationalite,QString adresse,int num_telephone,QString mdp,QString Email)
{
 this->CIN=CIN;
 this->nom=nom;
 this->prenom=prenom;
 this->sexe=sexe;
 this->role=role;
 this->date_naissance=date_naissance;
 this->nationalite=nationalite;
 this->adresse=adresse;
 this->num_telephone=num_telephone;
 this->mdp=mdp;
 this->Email=Email;


}


int Employe::getcin(){return CIN;}
QString Employe::getnom(){return nom;}
QString Employe::getprenom(){return prenom;}
QString Employe::getsexe(){return sexe;}
QString Employe::getrole(){return role;}
QDate Employe::getdate(){return date_naissance;}
QString Employe::getnationalite(){return nationalite;}
QString Employe::getadresse(){return adresse;}
int Employe::getnumtelephone(){return num_telephone;}
QString Employe::getmdp(){return mdp;}
QString Employe::getemail(){return Email;}
void Employe::setcin(int CIN){this->CIN=CIN;}
void Employe::setnom(QString nom){this->nom=nom;}
void Employe::setprenom(QString prenom){this->prenom=prenom;}
void Employe::setsexe(QString sexe){this->sexe=sexe;}
void Employe::setrole(QString role){this->role=role;}
void Employe::setdate(QDate date_naissance){this->date_naissance=date_naissance;}
void Employe::setnationalite(QString nationalite){this->nationalite=nationalite;}
void Employe::setadresse(QString adresse){this->adresse=adresse;}
void Employe::setnumtelephone(int num_telephone){this->num_telephone=num_telephone;}
void Employe::setmdp(QString mdp){this->mdp=mdp;}
void Employe::setemail(QString Email){this->Email=Email;}
bool Employe::ajouter()
{

    QSqlQuery query;

    QString cin_string=QString::number(CIN);
    QString num_telephone_string=QString::number(num_telephone);
      query.prepare("INSERT INTO employee (id_employe,cin,nom,prenom,num_telephone,email,mdp,role,sexe,nationalite,adresse,date_naissance) "
                    "VALUES (EMPLOYEE_SEQ.nextval,:cin,:nom,:prenom,:num_telephone,:email,:mdp,:role,:sexe,:nationalite,:adresse,:date_naissance)");
      query.bindValue(":cin", cin_string);
      query.bindValue(":nom", nom);
      query.bindValue(":prenom", prenom);
      query.bindValue(":num_telephone", num_telephone_string);
      query.bindValue(":email", Email);
      query.bindValue(":mdp", mdp);
      query.bindValue(":role", role);
      query.bindValue(":sexe", sexe);
      query.bindValue(":nationalite", nationalite);
      query.bindValue(":adresse", adresse);
      query.bindValue(":date_naissance", date_naissance);
      return query.exec();

}
QSqlQueryModel* Employe::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM employee");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num Telephone"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("Mot de Passe"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("Role"));
  model->setHeaderData(7, Qt::Horizontal, QObject::tr("Sexe"));
  model->setHeaderData(8, Qt::Horizontal, QObject::tr("Nationalite"));
  model->setHeaderData(9, Qt::Horizontal, QObject::tr("Adresse"));
  model->setHeaderData(10, Qt::Horizontal, QObject::tr("Date de naissance"));

  return model;


}
QSqlQueryModel* Employe::combobox_id()
{
 QSqlQuery *query= new QSqlQuery();
 QSqlQueryModel* model=new QSqlQueryModel();
 query->prepare("select id_employe from employee");
 query->exec();

model->setQuery(*query);

    return model;

}
bool Employe::supprimer(int cin)
{
    QSqlQuery query;

      query.prepare("Delete from employee where cin=:cin");
      query.bindValue(":cin", cin);

      return query.exec();

}

bool Employe::modifier(int id)
{
QSqlQuery query;
QString cin_string= QString::number(CIN);
QString num_telephone_string=QString::number(num_telephone);
query.prepare("update employee set cin=:cin, nom=:nom, prenom=:prenom, num_telephone=:num_telephone, email=:email, mdp=:mdp, role=:role, sexe=:sexe, nationalite=:nationalite, adresse=:adresse, date_naissance=:date_naissance where id_employe=:id ");
query.bindValue(":id",id);
query.bindValue(":cin", cin_string);
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom );
query.bindValue(":num_telephone", num_telephone_string);
query.bindValue(":email", Email);
query.bindValue(":mdp", mdp);
query.bindValue(":role", role);
query.bindValue(":sexe", sexe);
query.bindValue(":nationalite", nationalite);
query.bindValue(":adresse", adresse);
query.bindValue(":date_naissance", date_naissance);

return query.exec();
}

bool Employe::recherche_id(int x)
{
    QSqlQuery query;
    QString id_string= QString::number(x);
    return query.exec("SELECT id_employe FROM employee WHERE id_employe='"+id_string+"'");
}

bool Employe::recherche_cin(int x)
{
    QSqlQuery query;
    QString cin_string= QString::number(x);
    query.prepare("SELECT * FROM employee WHERE cin=:cin_supp");
    query.bindValue(":cin_supp",cin_string);
    return query.exec();

}


QSqlQueryModel* Employe::recherche(QString mot)
 {

    QSqlQuery *query= new QSqlQuery();
     QSqlQueryModel* model = new QSqlQueryModel();

      query->prepare("SELECT* FROM employee WHERE cin=:cin or nom=:nom or prenom=:prenom or role=:role or adresse=:adresse or num_telephone=:num_telephone or nationalite=:nationalite or mdp=:mdp or email=:email");
      query->bindValue(":cin",mot);
      query->bindValue(":nom",mot);
      query->bindValue(":prenom",mot);
      query->bindValue(":role",mot);
      query->bindValue(":adresse",mot);
      query->bindValue(":num_telephone",mot);
      query->bindValue(":nationalite",mot);
      query->bindValue(":mdp",mot);
      query->bindValue(":email",mot);
      query->exec();

      model->setQuery(*query);
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num Telephone"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("Mot de Passe"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("Role"));
      model->setHeaderData(7, Qt::Horizontal, QObject::tr("Sexe"));
      model->setHeaderData(8, Qt::Horizontal, QObject::tr("Nationalite"));
      model->setHeaderData(9, Qt::Horizontal, QObject::tr("Adresse"));
      model->setHeaderData(10, Qt::Horizontal, QObject::tr("Date de naissance"));

    return model;
 }


