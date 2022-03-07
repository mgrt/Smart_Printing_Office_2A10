#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QString>
#include <QIntValidator>
#include <QSqlQuery>
#include <QSqlError>
#include <QLineEdit>
#include <QRegExpValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cin->setValidator(new QIntValidator(0, 99999999,this));
    ui->num_telephone->setValidator(new QIntValidator(0, 99999999,this));
    ui->tab_employe->setModel(e.afficher());
    ui->id_box->setModel(e.combobox_id());



    QRegExp exp("\\b[a-zA-Z]{2,50}\\b");
    QRegExpValidator *val =new QRegExpValidator(exp,this);
            ui->nom->setValidator(val);
            ui->prenom->setValidator(val);
            ui->role->setValidator(val);
            ui->adresse->setValidator(val);
            ui->nationalite->setValidator(val);

        QRegExp expEmail("\\b[a-zA-Z0-9.%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,4}\\b");
        QRegExpValidator *valEmail =new QRegExpValidator(expEmail,this);
        ui->email->setValidator(valEmail);




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
 int cin=ui->cin->text().toInt();
 QString nom=ui->nom->text();
 QString prenom=ui->prenom->text();
 QString role=ui->role->text();
 QDate date=ui->date_naissance->date();
 QString sexe=ui->sexe->currentText();
 QString nationalite=ui->nationalite->text();
 QString adresse=ui->adresse->text();
 int num_telephone=ui->num_telephone->text().toInt();
 QString mdp=ui->mdp->text();
 QString email=ui->email->text();
 if(email.contains(QRegExp("\\b[a-zA-Z0-9.%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,4}\\b")))
 {
 Employe E(cin,nom,prenom,sexe,role,date,nationalite,adresse,num_telephone,mdp,email);
 bool test=E.ajouter();
 if(test)
  {
   QMessageBox::information(nullptr, QObject::tr("OK"),
   QObject::tr("Ajout effectué.\n"
               "Click Cancel to exit."), QMessageBox::Cancel);
   ui->tab_employe->setModel(e.afficher());
   ui->cin->clear();
   ui->nom->clear();
   ui->prenom->clear();
   ui->role->clear();
   ui->nationalite->clear();
   ui->adresse->clear();
   ui->num_telephone->clear();
   ui->mdp->clear();
   ui->email->clear();
   ui->id_box->setModel(e.combobox_id());
   }
   else
   {QMessageBox::critical(nullptr, QObject::tr("Erreur"),
    QObject::tr("Ajout non effectué.\n"
                "Click Cancel to exit."), QMessageBox::Cancel);
   }
  }
  else
  {
      QMessageBox::critical(nullptr, QObject::tr("Email Erreur"),
                   QObject::tr("format incorrect d'email.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
  }




}

void MainWindow::on_pb_supprimer_clicked()
{
    int cin=ui->cin_supp->text().toInt();


        bool test=e.supprimer(cin);


     if (test)
     {
      QMessageBox::information(nullptr, QObject::tr("OK"),
      QObject::tr("Suppression effectué.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_employe->setModel(e.afficher());
      ui->cin_supp->clear();
      ui->id_box->setModel(e.combobox_id());
      }
      else
      {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
       QObject::tr("Echec de suppression.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);
      }

     }






void MainWindow::on_modifier_clicked()
{
    int id=ui->id_box->currentText().toInt();
    if(id != 0)
    {
        int cin=ui->cin_maj->text().toInt();
        QString nom=ui->nom_maj->text();
        QString prenom=ui->prenom_maj->text();
        QString role=ui->role_maj->text();
        QDate date=ui->date_naissance_maj->date();
        QString sexe=ui->sexe_maj->currentText();
        QString nationalite=ui->nationalite_maj->text();
        QString adresse=ui->adresse_maj->text();
        int num_telephone=ui->num_telephone_maj->text().toInt();
        QString mdp=ui->mdp_maj->text();
        QString email=ui->email_maj->text();
        Employe E(cin,nom,prenom,sexe,role,date,nationalite,adresse,num_telephone,mdp,email);



    bool test=E.modifier(id);
    if(test)
    {
                QMessageBox::information(nullptr, QObject::tr("database is open"),
                            QObject::tr("modification effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_employe->setModel(e.afficher());
    ui->id_box->clear();
    ui->cin_maj->clear();
    ui->nom_maj->clear();
    ui->prenom_maj->clear();
    ui->role_maj->clear();
    ui->nationalite_maj->clear();
    ui->adresse_maj->clear();
    ui->num_telephone_maj->clear();
    ui->mdp_maj->clear();
    ui->email_maj->clear();
    }
    else
    {
       QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("modification non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }



    }
    else
       {
        QMessageBox::critical(nullptr,QObject::tr("Error update"),
                                 QObject::tr("le champ id est vide \n cliquer ici pour continuer"),
                                 QMessageBox::Cancel);

    }
}



void MainWindow::on_recherche_button_clicked()
{
    Employe E;
    QString mot=ui->barre_recherche->text();
    if (mot != "")
    {
    ui->tab_employe->setModel(E.recherche(mot));
    ui->id_box->setModel(e.combobox_id());
    }
    else
       {
        QMessageBox::information(nullptr,QObject::tr("recherche erroné"),
                                 QObject::tr("le champ id est vide \n cliquer ici pour continuer"),
                                 QMessageBox::Cancel);

    }
}

void MainWindow::on_annuler_clicked()
{
    ui->id_box->clear();
    ui->cin_maj->clear();
    ui->nom_maj->clear();
    ui->prenom_maj->clear();
    ui->role_maj->clear();
    ui->nationalite_maj->clear();
    ui->adresse_maj->clear();
    ui->num_telephone_maj->clear();
    ui->mdp_maj->clear();
    ui->email_maj->clear();
}

void MainWindow::on_supp_ajout_clicked()
{
    ui->cin->clear();
    ui->nom->clear();
    ui->prenom->clear();
    ui->role->clear();
    ui->nationalite->clear();
    ui->adresse->clear();
    ui->num_telephone->clear();
    ui->mdp->clear();
    ui->email->clear();
}




void MainWindow::on_id_box_currentIndexChanged(const QString &arg1)
{
    QString id=ui->id_box->currentText();

    QSqlQuery query;
    query.prepare("select * from employee where id_employe='"+id+"'");

    if(query.exec())
    {
        while(query.next())
        {
           ui->cin_maj->setText(query.value(0).toString());
           ui->nom_maj->setText(query.value(1).toString());
           ui->prenom_maj->setText(query.value(2).toString());
           ui->num_telephone_maj->setText(query.value(3).toString());
           ui->email_maj->setText(query.value(4).toString());
           ui->mdp_maj->setText(query.value(5).toString());
           ui->role_maj->setText(query.value(6).toString());

           ui->nationalite_maj->setText(query.value(8).toString());
           ui->adresse_maj->setText(query.value(9).toString());

        }
    }
    else
    {
      QMessageBox::critical(this,tr("error::"),query.lastError().text());
    }
}





void MainWindow::on_tab_employe_activated(const QModelIndex &index)
{
    int val=ui->tab_employe->model()->data(index).toInt();
    QString cin_string= QString::number(val);
        QSqlQuery qry;
        qry.prepare("select * from employee where cin=:cin");
        qry.bindValue(":cin",cin_string);
        if(qry.exec())
        {
        while(qry.next())
        {
            ui->cin_supp->setText((qry.value(0).toString()));
        }
        }
}
