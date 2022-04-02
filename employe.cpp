#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
#include <QDate>
#include <QMessageBox>
#include <QList>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>

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

QSqlQueryModel * Employe::trie_nom_asc()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM employee ORDER BY nom asc");
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
QSqlQueryModel * Employe::trie_cin_asc()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM employee ORDER BY cin asc");
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
QSqlQueryModel * Employe::trie_adr_asc()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM employee ORDER BY adresse asc");
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

QSqlQueryModel * Employe::trie_prenom_asc()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM employee ORDER BY prenom asc");
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

QSqlQueryModel * Employe::trie_nationalite_asc()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM employee ORDER BY nationalite asc");
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

QSqlQueryModel * Employe::trie_nom_desc()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM employee ORDER BY nom desc");
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
QSqlQueryModel * Employe::trie_cin_desc()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM employee ORDER BY cin desc");
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
QSqlQueryModel * Employe::trie_adr_desc()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM employee ORDER BY adresse desc");
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

QSqlQueryModel * Employe::trie_prenom_desc()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM employee ORDER BY prenom desc");
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

QSqlQueryModel * Employe::trie_nationalite_desc()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM employee ORDER BY nationalite desc");
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

void Employe::statistique(QWidget * w)
{
    int tun = 0,sfx=0,sous =0,nbl =0,biz =0,gab =0,gaf =0,jend =0,kai =0,kass =0,keb =0,kef =0,mah =0,man =0,med =0,mon =0;
    int bouz =0,sil =0,tata =0,toz =0,zagh =0,aria =0,bej =0,bnar =0;
        QSqlQuery query("SELECT COUNT(*) FROM employee WHERE adresse='Tunis'");
        while(query.next())
        {
            tun = query.value(0).toInt();
        }
        QSqlQuery query2("SELECT COUNT(*) FROM employee WHERE adresse='Sfax'");
        while(query2.next())
        {
           sfx = query2.value(0).toInt();
        }
        QSqlQuery query3("SELECT COUNT(*) FROM employee WHERE adresse='Sousse'");
        while(query3.next())
        {
           sous = query3.value(0).toInt();
        }
        QSqlQuery query4("SELECT COUNT(*) FROM employee WHERE adresse='Nabeul'");
        while(query4.next())
        {
           nbl = query4.value(0).toInt();
        }
        QSqlQuery query5("SELECT COUNT(*) FROM employee WHERE adresse='Bizerte'");
        while(query5.next())
        {
           biz = query5.value(0).toInt();
        }
        QSqlQuery query6("SELECT COUNT(*) FROM employee WHERE adresse='Gabès'");
        while(query6.next())
        {
           gab = query6.value(0).toInt();
        }
        QSqlQuery query7("SELECT COUNT(*) FROM employee WHERE adresse='Gafsa'");
        while(query7.next())
        {
           gaf = query7.value(0).toInt();
        }
        QSqlQuery query8("SELECT COUNT(*) FROM employee WHERE adresse='Jendouba'");
        while(query8.next())
        {
           jend = query8.value(0).toInt();
        }
        QSqlQuery query9("SELECT COUNT(*) FROM employee WHERE adresse='Kairouan'");
        while(query9.next())
        {
           kai = query9.value(0).toInt();
        }
        QSqlQuery query10("SELECT COUNT(*) FROM employee WHERE adresse='Kasserine'");
        while(query10.next())
        {
           kass = query10.value(0).toInt();
        }
        QSqlQuery query11("SELECT COUNT(*) FROM employee WHERE adresse='Kébili'");
        while(query11.next())
        {
           keb = query11.value(0).toInt();
        }
        QSqlQuery query12("SELECT COUNT(*) FROM employee WHERE adresse='Le Kef'");
        while(query12.next())
        {
           kef = query12.value(0).toInt();
        }
        QSqlQuery query13("SELECT COUNT(*) FROM employee WHERE adresse='Mahdia'");
        while(query13.next())
        {
           mah = query13.value(0).toInt();
        }
        QSqlQuery query14("SELECT COUNT(*) FROM employee WHERE adresse='La Manouba'");
        while(query14.next())
        {
           man = query14.value(0).toInt();
        }
        QSqlQuery query15("SELECT COUNT(*) FROM employee WHERE adresse='Médenine'");
        while(query15.next())
        {
           med = query15.value(0).toInt();
        }
        QSqlQuery query16("SELECT COUNT(*) FROM employee WHERE adresse='Sidi Bouzid'");
        while(query16.next())
        {
           bouz = query16.value(0).toInt();
        }
        QSqlQuery query17("SELECT COUNT(*) FROM employee WHERE adresse='Monastir'");
        while(query17.next())
        {
           mon = query17.value(0).toInt();
        }
        QSqlQuery query18("SELECT COUNT(*) FROM employee WHERE adresse='Siliana'");
        while(query18.next())
        {
           sil = query18.value(0).toInt();
        }
        QSqlQuery query19("SELECT COUNT(*) FROM employee WHERE adresse='Tataouine'");
        while(query19.next())
        {
           tata = query19.value(0).toInt();
        }
        QSqlQuery query20("SELECT COUNT(*) FROM employee WHERE adresse='Tozeur'");
        while(query20.next())
        {
           toz = query20.value(0).toInt();
        }
        QSqlQuery query21("SELECT COUNT(*) FROM employee WHERE adresse='Zaghouan'");
        while(query21.next())
        {
           zagh = query21.value(0).toInt();
        }
        QSqlQuery query22("SELECT COUNT(*) FROM employee WHERE adresse='Ariana'");
        while(query22.next())
        {
           aria = query22.value(0).toInt();
        }
        QSqlQuery query23("SELECT COUNT(*) FROM employee WHERE adresse='Béja'");
        while(query23.next())
        {
           bej = query23.value(0).toInt();
        }
        QSqlQuery query24("SELECT COUNT(*) FROM employee WHERE adresse='Ben Arous'");
        while(query24.next())
        {
           bnar = query24.value(0).toInt();
        }

    int total=(tun+sfx+sous+biz+gab+gaf+jend+kai+kass+keb+kef+mah+man+med+bouz+mon+sil+tata+toz+zagh+aria+bej+bnar+nbl);

    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.28);
    //series->setPieSize(1.0);

    float val=(tun*100)/total;  //calcul du pourcentage
    QString nbre_string = QString::number(val);
series->append("Tunis "+nbre_string+"%  ",tun);
   val=sfx*100/total;  //calcul du pourcentage
   nbre_string = QString::number(val);
series->append("Sfax "+nbre_string+"% ",sfx);
    val=sous*100/total;  //calcul du pourcentage
    nbre_string = QString::number(val);
series->append("Sousse "+nbre_string+"% ",sous);
val=biz*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Bizerte "+nbre_string+"% ",biz);
val=gab*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Gabès "+nbre_string+"% ",gab);
val=gaf*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Gafsa "+nbre_string+"% ",gaf);
val=jend*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Jendouba "+nbre_string+"%",jend);
val=kai*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Kairouan "+nbre_string+"% ",kai);
val=kass*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Kasserine "+nbre_string+"% ",kass);
val=keb*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Kébili "+nbre_string+"% ",keb);
val=kef*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Le Kef "+nbre_string+"% ",kef);
val=mah*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Mahdia "+nbre_string+"% ",mah);
val=man*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("La Manouba "+nbre_string+"% ",man);
val=med*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Médenine "+nbre_string+"% ",med);
val=bouz*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Sidi Bouzid "+nbre_string+"% ",bouz);
val=mon*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Monastir "+nbre_string+"% ",mon);
val=sil*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Siliana "+nbre_string+"% ",sil);
val=tata*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Tataouine "+nbre_string+"% ",tata);
val=toz*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Tozeur "+nbre_string+"% ",toz);
val=zagh*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Zaghouan "+nbre_string+"% ",zagh);
val=aria*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Ariana "+nbre_string+"% ",aria);
val=bej*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Béja "+nbre_string+"% ",bej);
val=bnar*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Ben Arous "+nbre_string+"% ",bnar);
val=nbl*100/total;  //calcul du pourcentage
nbre_string = QString::number(val);
series->append("Nabeul "+nbre_string+"% ",nbl);

QPieSlice * tun_s = series->slices().at(0);
QPieSlice * sfx_s = series->slices().at(1);
QPieSlice * sous_s = series->slices().at(2);
QPieSlice * biz_s = series->slices().at(3);
QPieSlice * gab_s = series->slices().at(4);
QPieSlice * gaf_s = series->slices().at(5);
QPieSlice * jend_s = series->slices().at(6);
QPieSlice * kai_s = series->slices().at(7);
QPieSlice * kass_s = series->slices().at(8);
QPieSlice * keb_s = series->slices().at(9);
QPieSlice * kef_s = series->slices().at(10);
QPieSlice * mah_s = series->slices().at(11);
QPieSlice * man_s = series->slices().at(12);
QPieSlice * med_s = series->slices().at(13);
QPieSlice * bouz_s = series->slices().at(14);
QPieSlice * mon_s = series->slices().at(15);
QPieSlice * sil_s = series->slices().at(16);
QPieSlice * tata_s = series->slices().at(17);
QPieSlice * toz_s = series->slices().at(18);
QPieSlice * zagh_s = series->slices().at(19);
QPieSlice * aria_s = series->slices().at(20);
QPieSlice * bej_s = series->slices().at(21);
QPieSlice * bnar_s = series->slices().at(22);
QPieSlice * nbl_s = series->slices().at(23);

tun_s->setLabelVisible(true);
sfx_s->setLabelVisible(true);
sous_s->setLabelVisible(true);
biz_s->setLabelVisible(true);
gab_s->setLabelVisible(true);
gaf_s->setLabelVisible(true);
jend_s->setLabelVisible(true);
kai_s->setLabelVisible(true);
kass_s->setLabelVisible(true);
keb_s->setLabelVisible(true);
kef_s->setLabelVisible(true);
mah_s->setLabelVisible(true);
man_s->setLabelVisible(true);
med_s->setLabelVisible(true);
bouz_s->setLabelVisible(true);
mon_s->setLabelVisible(true);
sil_s->setLabelVisible(true);
tata_s->setLabelVisible(true);
toz_s->setLabelVisible(true);
zagh_s->setLabelVisible(true);
aria_s->setLabelVisible(true);
bej_s->setLabelVisible(true);
bnar_s->setLabelVisible(true);
nbl_s->setLabelVisible(true);
    tun_s->setBrush(QColor::fromRgb(85, 31, 31));
    sfx_s->setBrush(QColor::fromRgb(219, 70, 0));
sous_s->setBrush(QColor::fromRgb(160, 205, 120));
biz_s->setBrush(QColor::fromRgb(100, 100, 20));
gab_s->setBrush(QColor::fromRgb(210, 130, 25));
gaf_s->setBrush(QColor::fromRgb(120, 30, 16));
jend_s->setBrush(QColor::fromRgb(0, 0, 116));
kai_s->setBrush(QColor::fromRgb(199, 0, 0));
kass_s->setBrush(QColor::fromRgb(0, 110, 0));
keb_s->setBrush(QColor::fromRgb(0, 110, 120));
kef_s->setBrush(QColor::fromRgb(130, 0, 120));
mah_s->setBrush(QColor::fromRgb(20, 20, 50));
man_s->setBrush(QColor::fromRgb(200, 20, 50));
med_s->setBrush(QColor::fromRgb(255, 255, 0));
bouz_s->setBrush(QColor::fromRgb(25, 160, 100));
mon_s->setBrush(QColor::fromRgb(100, 23, 16));
sil_s->setBrush(QColor::fromRgb(120, 110, 100));
tata_s->setBrush(QColor::fromRgb(100, 100, 205));
toz_s->setBrush(QColor::fromRgb(120, 255, 205));
zagh_s->setBrush(QColor::fromRgb(93, 117, 54));
aria_s->setBrush(QColor::fromRgb(159, 219, 8));
bej_s->setBrush(QColor::fromRgb(255, 87, 51));
bnar_s->setBrush(QColor::fromRgb(150, 148, 40));
nbl_s->setBrush(QColor::fromRgb(87, 87, 87));


    QChart *chart = new QChart();
    chart->addSeries(series);
    //chart->setTitle("Statistique par adresse");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignLeft);
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView * chartview = new QChartView(chart);
    chartview->resize(w->width(),w->height());
    chartview->setParent(w);

}
