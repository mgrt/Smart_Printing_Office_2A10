#ifndef CLIENTS_H
#define CLIENTS_H
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QMainWindow>
#include "QMessageBox"
#include <QTabWidget>
#include <QSqlQueryModel>


class Clients
{

  int id_client;
  QString nom_client;
  QString prenom_client;
  QString genre_client;
  int num_telephone_client;
  QString email_client;
  int cin_client;
  QDate date_naissance_client;
  QString nationalite_client;


public:

  //Constructeurs
    Clients();
    Clients(int,QString,QString,QString,int,QString,int,QDate,QString);

  //Getters
    QString getnom_client(){return nom_client;}
    QString getprenom_client(){return prenom_client;}
    QString getgenre_client(){return genre_client;}
    int getnum_telephone_client(){return num_telephone_client;}
    QString getemail_client(){return email_client;}
    int getcin_client(){return cin_client;}
    QDate getdate_naissance_client(){return date_naissance_client;}
    QString getnationalite_client(){return nationalite_client;}

    //Setters
    void setnom_client(QString n){nom_client=n;}
    void setprenom_client(QString p){prenom_client=p;}
    void setgenre_client(QString g){genre_client=g;}
    void setnum_telephone_client(int nt){num_telephone_client=nt;}
    void setemail_client(QString e){email_client=e;}
    void setcin_client(int c){cin_client=c;}
    void setdate_naissance_client(QDate d){date_naissance_client=d;}
    void setbationalite_client(QString na){nationalite_client=na;}

    //Fonctionnalités
    bool ajouter_client();
    QSqlQueryModel * afficher_client();
    bool supprimer_client(int);
    bool modifier_client(int);
    void recuperer_client(int id,QString &nom,QString &prenom,QString &genre,QString &num,QString &email,QString &cin,QDate &date,QString &nationalite);
    QSqlQueryModel * rechercher(QString );


};

#endif // CLIENTS_H
