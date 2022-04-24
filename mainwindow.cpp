#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QSqlQueryModel"
#include <QSqlError>
#include "QMessageBox"
#include "QSqlQuery"
#include "smtp.h"
#include "employe.h"
#include "chatconnection.h"
#include<QSslSocket>
#include <QMessageBox>
#include <QSqlRecord>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include<QPainter>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include "QFileDialog"
#include "QTextStream"
#include <QTextDocument>
#include <QPrintDialog>
#include"QPainter"
#include"QDesktopServices"
#include"QtPrintSupport/QPrinter"
#include <QPropertyAnimation>
#include<QTextDocument>
#include <QDesktopServices>
#include <QUrl>
#include <QTcpSocket>
#include "stocks.h"
#include "categorie.h"
#include "qrcode.h"
#include <QDate>
#include <QSystemTrayIcon>
#include <iostream>
//#include <QPrinter>
//#include <QPrintDialog>
#include "connection.h"
#include "stocks.h"
#include "categorie.h"
#include <qmessagebox.h>
#include <QDebug>
#include <QtPrintSupport/QPrintDialog>
#include<QtPrintSupport/QPrinter>
#include<QPropertyAnimation>
#include "smtp.h"
#include <QtPrintSupport/QPrinterInfo>
#include <QtPrintSupport/QPrintDialog>
#include <QFileDialog>
#include <QDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include<QPdfWriter>
#include<QTabWidget>
#include<QTableView>
#include <QInputDialog>
#include <QPrinter>
#include <QMediaPlayer>
#include <QThread>
#include <QUrl>
#include <QSound>
#include <QDebug>
#include "qrcode.h"
#include <QDate>
#include <QSystemTrayIcon>
#include <iostream>
#include "maintenance.h"
#include "machine.h"
using namespace qrcodegen ;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*ui->frame_3->hide();
    ui->frame_5->hide();*/
    ui->mail_sprint_6->hide();
    ui->smtp_gmail_6->hide();
    ui->port_smtp_6->hide();
    ui->mdp_sprint_6->hide();
    ui->code_6->hide();
    ui->newmdp1_6->hide();
    ui->newmdp2_6->hide();
    ui->checkBox_27->hide();
    ui->loginForgot_6->hide();
    ui->tab_widget_employe->hide();
    ui->retour_accueil->hide();
    ui->retour_accueil_2->hide();
    ui->retour_accueil_3->hide();
    ui->retour_accueil_4->hide();
    ui->stackedWidget->setCurrentIndex(0);
    this->setGeometry(0,0,1140,625);
    connect(this, SIGNAL(test()),this, SLOT(aff()));
 //connect(this, SIGNAL(test()),this, SLOT(affich()));

    ////////////employee/////////////////////
    ui->cin_5->setValidator(new QIntValidator(0, 99999999,this));
    ui->num_telephone_5->setValidator(new QIntValidator(0, 99999999,this));
    ui->tab_employe_5->setModel(e.afficher());
    ui->id_box_5->setModel(e.combobox_id());



    QRegExp exp("\\b[a-zA-Z]{2,50}\\b");
    QRegExp espace("^[a-zA-Z]+( [a-zA-Z]+)*$");
    QRegExpValidator *val =new QRegExpValidator(exp,this);
    QRegExpValidator *valesp =new QRegExpValidator(espace,this);
            ui->nom_6->setValidator(val);
            ui->prenom_6->setValidator(valesp);
            ui->role_5->setValidator(val);
            ui->adresse_5->setValidator(val);
            ui->nationalite_5->setValidator(val);

        QRegExp expEmail("\\b[a-zA-Z0-9.%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,4}\\b");
        QRegExpValidator *valEmail =new QRegExpValidator(expEmail,this);
        ui->email_5->setValidator(valEmail);

        qDebug()
                    << QSslSocket::supportsSsl() // doit retourner true
                    << QSslSocket::sslLibraryBuildVersionString() // la version utilise pour compiler Qt
                    << QSslSocket::sslLibraryVersionString(); // la version disponible
  connect(this, SIGNAL(test()),this, SLOT(affich()));
        //CHAT//
        mSocket=new QTcpSocket(this);
        connect(mSocket, &QTcpSocket::readyRead, [&]() {
           QTextStream T(mSocket);
           auto text = T.readAll();
           ui->textEdit_chat_5->append(text);
        });
   ////////////////////////////////////////////////////////////////////


        int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).
         update_output_data();
         controle_de_saisie();
         ui->affichage_maintenance->setSelectionBehavior(QAbstractItemView::SelectRows);
         ui->affichage_maintenance->verticalHeader()->hide();
         ui->affichage_machine->setSelectionBehavior(QAbstractItemView::SelectRows);

         //ui->maps->setSource(QUrl(QStringLiteral("map.qml")));
      //   ui->maps->show();
         ui->papier->setVisible(false);
         ui->nom_papier_L->setVisible(false);
         ui->nom_produit->setVisible(false);
          ui->lcdNumber->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_25_clicked()
{
    if(ui->checkBox_25->isChecked()){
        ui->mdp_cnx->setEchoMode(QLineEdit::Normal);
        ui->checkBox_25->setText("Hide password");
    }else{
        ui->mdp_cnx->setEchoMode(QLineEdit::Password);
        ui->checkBox_25->setText("Show password");
    }
}



void MainWindow::on_mdp_oublie_5_clicked()
{
    /*ui->frame_2->hide();
    ui->frame_3->hide();*/
    ui->stackedWidget->setCurrentIndex(1);
    this->setWindowTitle("Forgot Password");
    //ui->frame_5->show();
}


void MainWindow::on_retourner_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    /*ui->frame_5->hide();
    ui->frame_3->hide();*/
    this->setWindowTitle("Sign in");
    //ui->frame_2->show();
}

// email forgotten nextforgot
QString emailforgot;

void MainWindow::mailSent(QString status)
{
        if(status == "Message sent")
            QMessageBox::information( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::on_forgotNext_6_clicked()
{
    ui->label_29->setText("Enter the \ncode sent to the email in the code field");

    //The entered email database is checked for availability --------
    QString email = ui->email_17->text();
    emailforgot = email;
    QSqlQuery query3;
    query3.prepare("select * from employee where email='"+email+"'");

    int count = 0;
    if(query3.exec()){
        while (query3.next()) {
            count++;
        }
        if(count == 1){
            Smtp* smtp = new Smtp(ui->mail_sprint_6->text(),ui->mdp_sprint_6->text(),ui->smtp_gmail_6->text(),ui->port_smtp_6->text().toUShort());
            connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
            smtp->sendMail(ui->mail_sprint_6->text(),email,"votre code de recuperation","votre code est 95863");
            ui->code_6->show();
            ui->newmdp1_6->show();
            ui->newmdp2_6->show();
            ui->checkBox_27->show();
            ui->loginForgot_6->show();
            ui->email_17->hide();
          //  ui->forgotNext_6->hide();
        }else{
            ui->label_29->setText("There is no such user");
        }
    }
}


void MainWindow::on_loginForgot_6_clicked()
{
    //when resetting the password, the correctness of the code sent and the compatibility of the passwords are checked
    QString mdp_1 = ui->newmdp1_6->text(),
            mdp_2 = ui->newmdp2_6->text(),
            code = ui->code_6->text(),
            emailf = emailforgot;
    if(code == "95863"){
        if(mdp_1 == mdp_2){
            QSqlQueryModel *m=new QSqlQueryModel();
            m->setQuery("UPDATE employee SET mdp='"+ mdp_1 +"' WHERE email='"+ emailf +"'");
             ui->stackedWidget->setCurrentIndex(0);
            this->setWindowTitle("Sign in");


        }else{
            ui->label_29->setText("Is there an error in matching passwords?");
        }
    }else{
        ui->label_29->setText("Error code. ??");
    }
}





void MainWindow::on_checkBox_27_clicked()
{
    if(ui->checkBox_27->isChecked()){
        ui->newmdp1_6->setEchoMode(QLineEdit::Normal);
        ui->checkBox_27->setText("Hide password");
    }else{
        ui->newmdp1_6->setEchoMode(QLineEdit::Password);
        ui->checkBox_27->setText("Show password");
    }
}

void MainWindow::on_signUp_clicked()
{

    QString prenom = ui->prenom->text(),
            nom = ui->nom->text(),
            role = ui->role_login->currentText(),
            cin = ui->cin_login_create->text(),
            email = ui->email_create->text(),
            passwrd1 = ui->mdp_create->text(),
            passwrd2 = ui->mdp_create_verif->text();
    if(prenom == "" || nom == ""  || email == "" || passwrd1 =="" || passwrd2 == "")
    {
        ui->label_42->setText("Fill in the fields");
    }else{
        if(passwrd1 == passwrd2){
            QSqlQuery query;
            query.prepare("select * from employee where email='"+email+"'");

            int count = 0;
            if(query.exec()){
                while (query.next()) {
                    count++;
                }
                if(count < 1){

                    QSqlQuery query2;
                    query2.prepare("INSERT INTO employee(cin, prenom, nom, role, email, mdp) "
                            "VALUES(:cin, :prenom, :nom, :role, :email, :mdp)");
                    query2.bindValue(":cin",cin);
                    query2.bindValue(":prenom",prenom);
                    query2.bindValue(":nom",nom);
                    query2.bindValue(":role",role);
                    query2.bindValue(":email",email);
                    query2.bindValue(":mdp",passwrd1);
                    query2.exec();
                      ui->label_42->setText("Compte crée.");

                }
                if(count ==1){
                    ui->label_42->setText("There is such a user");
                }
            }
        }else{
            ui->label_42->setText("There is an error in the passwords");
        }
    }

}

void MainWindow::on_retourner_signup_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->setWindowTitle("Sign in");
}


void MainWindow::on_connexion_5_clicked()
{
    if(ui->mdp_cnx->text() == "" || ui->email_cnx->text() == "")
    {
        ui->label_26->show();
        ui->label_26->setText("Please fill in the email and password\n fields");
    }
    else{
        QString email = ui->email_cnx->text(),
                password = ui->mdp_cnx->text();
        Employe *emp=new Employe();
        emp->count(email,password);
       ui->email_cnx->setText(emp->getmdp());
       ui->label_195->setText(emp->getnom());
       if(emp->getmdp()!=""&&emp->getemail()!="")
       {   // ui->stackedWidget->setCurrentIndex(1);
           if(emp->getrole()=="Admin")
           {
             ui->stackedWidget->setCurrentIndex(3);
           ui->tab_widget_employe->show();
            ui->retour_accueil->show();
            ui->retour_accueil_2->show();
            }
           if(emp->getrole()=="GProduits")
           {
             ui->stackedWidget->setCurrentIndex(4);
              ui->retour_accueil_2->hide();

            }
           if(emp->getrole()=="GFactures")
           {
               ui->stackedWidget->setCurrentIndex(6);
                ui->retour_accueil_4->hide();
           }
           if(emp->getrole()=="GMaintenances")
           {
                ui->stackedWidget->setCurrentIndex(7);
                 ui->retour_accueil_3->hide();
           }

       }

    }
}


void MainWindow::on_create_acount_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    this->setWindowTitle("Create Account");
}


void MainWindow::on_GClients_button_clicked()
{
    //
}


void MainWindow::on_GProduits_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
     ui->retour_accueil_2->show();

}


void MainWindow::on_GFactures_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
     ui->retour_accueil_4->show();
}



void MainWindow::on_GEmployes_button_clicked()
{  ui->stackedWidget->setCurrentIndex(5);
// ui->tab_widget_employe_2->show();
}


void MainWindow::on_GMaintenances_button_clicked()
{
      ui->stackedWidget->setCurrentIndex(7);
 ui->retour_accueil_3->show();
}


void MainWindow::on_pb_ajouter_5_clicked()
{
    int cin=ui->cin_5->text().toInt();
    QString nom=ui->nom_6->text();
    QString prenom=ui->prenom_6->text();
    QString role=ui->role_5->currentText();
    QDate date=ui->date_naissance_5->date();
    QString sexe=ui->sexe_5->currentText();
    QString nationalite=ui->nationalite_5->text();
    QString adresse=ui->adresse_5->currentText();
    int num_telephone=ui->num_telephone_5->text().toInt();
    QString mdp=ui->mdp_5->text();
    QString email=ui->email_5->text();

    if(email.contains(QRegExp("\\b[a-zA-Z0-9.%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,4}\\b")))
    {
    Employe E(cin,nom,prenom,sexe,role,date,nationalite,adresse,num_telephone,mdp,email);
    bool test=E.ajouter();
    if(test)
     {
      QMessageBox::information(nullptr, QObject::tr("OK"),
      QObject::tr("Ajout effectué.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_employe_5->setModel(e.afficher());
      ui->cin_5->clear();
      ui->nom_6->clear();
      ui->prenom_6->clear();
      ui->role_5->clear();
      ui->nationalite_5->clear();
      ui->num_telephone_5->clear();
      ui->mdp_5->clear();
      ui->email_5->clear();
      ui->id_box_5->setModel(e.combobox_id());
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


void MainWindow::on_pb_supprimer_5_clicked()
{
    int cin=ui->cin_supp_5->text().toInt();


        bool test=e.supprimer(cin);


     if (test)
     {
      QMessageBox::information(nullptr, QObject::tr("OK"),
      QObject::tr("Suppression effectué.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_employe_5->setModel(e.afficher());
      ui->cin_supp_5->clear();
      ui->id_box_5->setModel(e.combobox_id());
      }
      else
      {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
       QObject::tr("Echec de suppression.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);
      }
}


void MainWindow::on_modifier_5_clicked()
{
    int id=ui->id_box_5->currentText().toInt();
    if(id != 0)
    {
        int cin=ui->cin_maj_5->text().toInt();
        QString nom=ui->nom_maj_5->text();
        QString prenom=ui->prenom_maj_5->text();
        QString role=ui->role_maj_5->text();
        QDate date=ui->date_naissance_maj_5->date();
        QString sexe=ui->sexe_maj_5->currentText();
        QString nationalite=ui->nationalite_maj_5->text();
        QString adresse=ui->adresse_maj_5->currentText();
        int num_telephone=ui->num_telephone_maj_5->text().toInt();
        QString mdp=ui->mdp_maj_5->text();
        QString email=ui->email_maj_5->text();
        Employe E(cin,nom,prenom,sexe,role,date,nationalite,adresse,num_telephone,mdp,email);



    bool test=E.modifier(id);
    if(test)
    {
                QMessageBox::information(nullptr, QObject::tr("database is open"),
                            QObject::tr("modification effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_employe_5->setModel(e.afficher());
    ui->id_box_5->clear();
    ui->cin_maj_5->clear();
    ui->nom_maj_5->clear();
    ui->prenom_maj_5->clear();
    ui->role_maj_5->clear();
    ui->nationalite_maj_5->clear();
    ui->num_telephone_maj_5->clear();
    ui->mdp_maj_5->clear();
    ui->email_maj_5->clear();
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


void MainWindow::on_barre_recherche_5_textChanged(const QString &arg1)
{
    Employe e;
    ui->tab_employe_5->setModel( e.recherche(arg1));
}


void MainWindow::on_annuler_5_clicked()
{
    ui->id_box_5->clear();
    ui->cin_maj_5->clear();
    ui->nom_maj_5->clear();
    ui->prenom_maj_5->clear();
    ui->role_maj_5->clear();
    ui->nationalite_maj_5->clear();
    ui->num_telephone_maj_5->clear();
    ui->mdp_maj_5->clear();
    ui->email_maj_5->clear();
}


void MainWindow::on_supp_ajout_5_clicked()
{
    ui->cin_5->clear();
    ui->nom_6->clear();
    ui->prenom_6->clear();
    ui->role_5->clear();
    ui->nationalite_5->clear();
    ui->num_telephone_5->clear();
    ui->mdp_5->clear();
    ui->email_5->clear();
}





void MainWindow::on_id_box_5_currentIndexChanged(const QString &arg1)
{
    QString id=ui->id_box_5->currentText();

    QSqlQuery query;
    query.prepare("select * from employee where id_employe='"+id+"'");

    if(query.exec())
    {
        while(query.next())
        {
           ui->cin_maj_5->setText(query.value(0).toString());
           ui->nom_maj_5->setText(query.value(1).toString());
           ui->prenom_maj_5->setText(query.value(2).toString());
           ui->num_telephone_maj_5->setText(query.value(3).toString());
           ui->email_maj_5->setText(query.value(4).toString());
           ui->mdp_maj_5->setText(query.value(5).toString());
           ui->role_maj_5->setText(query.value(6).toString());
           ui->sexe_maj_5->setCurrentText(query.value(7).toString());
           ui->nationalite_maj_5->setText(query.value(8).toString());
           ui->adresse_maj_5->setCurrentText(query.value(9).toString());

        }
    }
    else
    {
      QMessageBox::critical(this,tr("error::"),query.lastError().text());
    }
}


void MainWindow::on_tab_employe_5_activated(const QModelIndex &index)
{
    int val=ui->tab_employe_5->model()->data(index).toInt();
    QString cin_string= QString::number(val);
        QSqlQuery qry;
        qry.prepare("select * from employee where cin=:cin");
        qry.bindValue(":cin",cin_string);
        if(qry.exec())
        {
        while(qry.next())
        {
            ui->cin_supp_5->setText((qry.value(0).toString()));
        }
        }
}


void MainWindow::on_tri_button_asc_5_clicked()
{
    Employe E;
        QString choix=ui->tri_comboBox_5->currentText();
        if (choix=="par nom")
        {
            ui->tab_employe_5->setModel(E.trie_nom_asc());
            ui->tab_employe_5->setModel(E.afficher());
            bool test=E.trie_nom_asc();
            if (test)
            {

                ui->tab_employe_5->setModel(E.trie_nom_asc());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri nom effectué \n"
                                                     "Click Cancel to exist ."),QMessageBox::Cancel);

            }
            else
                  QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("tri non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        }
        if (choix=="par adresse")
        {
            ui->tab_employe_5->setModel(E.trie_adr_asc());
            ui->tab_employe_5->setModel(E.afficher());
            bool test=E.trie_adr_asc();
            if (test)
            {

                ui->tab_employe_5->setModel(E.trie_adr_asc());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri adresse effectué \n"
                                                     "Click Cancel to exist ."),QMessageBox::Cancel);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                            QObject::tr("tri non effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
        }
        if (choix=="par cin")
        {
            ui->tab_employe_5->setModel(E.trie_cin_asc());
            ui->tab_employe_5->setModel(E.afficher());
            bool test=E.trie_cin_asc();
            if (test)
            {

                ui->tab_employe_5->setModel(E.trie_cin_asc());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri cin effectué \n"
                                                     "Click Cancel to exist ."),QMessageBox::Cancel);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                            QObject::tr("tri non effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
        }

        if (choix=="par nationalite")
        {
            ui->tab_employe_5->setModel(E.trie_nationalite_asc());
            ui->tab_employe_5->setModel(E.afficher());
            bool test=E.trie_nationalite_asc();
            if (test)
            {

                ui->tab_employe_5->setModel(E.trie_nationalite_asc());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri nationalite effectué \n"
                                                     "Click Cancel to exist ."),QMessageBox::Cancel);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                            QObject::tr("tri non effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
        }

        if (choix=="par prenom")
        {
            ui->tab_employe_5->setModel(E.trie_prenom_asc());
            ui->tab_employe_5->setModel(E.afficher());
            bool test=E.trie_prenom_asc();
            if (test)
            {

                ui->tab_employe_5->setModel(E.trie_prenom_asc());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri prenom effectué \n"
                                                     "Click Cancel to exist ."),QMessageBox::Cancel);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                            QObject::tr("tri non effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
        }
}


void MainWindow::on_tri_button_desc_5_clicked()
{
    Employe E;
        QString choix=ui->tri_comboBox_5->currentText();
        if (choix=="par nom")
        {
            ui->tab_employe_5->setModel(E.trie_nom_desc());
            ui->tab_employe_5->setModel(E.afficher());
            bool test=E.trie_nom_desc();
            if (test)
            {

                ui->tab_employe_5->setModel(E.trie_nom_desc());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri nom effectué \n"
                                                     "Click Cancel to exist ."),QMessageBox::Cancel);

            }
            else
                  QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("tri non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        }
        if (choix=="par adresse")
        {
            ui->tab_employe_5->setModel(E.trie_adr_desc());
            ui->tab_employe_5->setModel(E.afficher());
            bool test=E.trie_adr_desc();
            if (test)
            {

                ui->tab_employe_5->setModel(E.trie_adr_desc());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri adresse effectué \n"
                                                     "Click Cancel to exist ."),QMessageBox::Cancel);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                            QObject::tr("tri non effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
        }
        if (choix=="par cin")
        {
            ui->tab_employe_5->setModel(E.trie_cin_desc());
            ui->tab_employe_5->setModel(E.afficher());
            bool test=E.trie_cin_desc();
            if (test)
            {

                ui->tab_employe_5->setModel(E.trie_cin_desc());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri cin effectué \n"
                                                     "Click Cancel to exist ."),QMessageBox::Cancel);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                            QObject::tr("tri non effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
        }

        if (choix=="par nationalite")
        {
            ui->tab_employe_5->setModel(E.trie_nationalite_desc());
            ui->tab_employe_5->setModel(E.afficher());
            bool test=E.trie_nationalite_desc();
            if (test)
            {

                ui->tab_employe_5->setModel(E.trie_nationalite_desc());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri nationalite effectué \n"
                                                     "Click Cancel to exist ."),QMessageBox::Cancel);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                            QObject::tr("tri non effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
        }

        if (choix=="par prenom")
        {
            ui->tab_employe_5->setModel(E.trie_prenom_desc());
            ui->tab_employe_5->setModel(E.afficher());
            bool test=E.trie_prenom_desc();
            if (test)
            {

                ui->tab_employe_5->setModel(E.trie_prenom_desc());
                QMessageBox::information(nullptr,QObject::tr("ok"),
                                         QObject::tr("tri prenom effectué \n"
                                                     "Click Cancel to exist ."),QMessageBox::Cancel);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                            QObject::tr("tri non effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
        }
}


void MainWindow::on_imprimer_button_5_clicked()
{
    QSqlDatabase db;
                   QTableView table_menu;
                   QSqlQueryModel * Modal=new  QSqlQueryModel();
                   QSqlQuery qry;
                    qry.prepare("SELECT * FROM employee");
                    qry.exec();
                    Modal->setQuery(qry);
                    table_menu.setModel(Modal);
                    db.close();
                    QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = table_menu.model()->rowCount();
                    const int columnCount =  table_menu.model()->columnCount();
                    const QString strTitle ="Document";
 out <<  "<html>\n"
 "<img src='C:/Users/Islem/Documents/GestionEmploye/img/logo sprint.png' height='120' width='120'/>"
 "<head>\n"
 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
  <<  QString("<title>%1</title>\n").arg(strTitle)
  <<  "</head>\n"
   "<body bgcolor=#ffffff link=#5000A0>\n"
  << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("LISTE DES EMPLOYES")
  <<"<br>"

 <<"<table border=1 cellspacing=0 cellpadding=2 width=\"100%\">\n";
  out << "<thead><tr bgcolor=#f0f0f0>";
  for (int column = 0; column < columnCount; column++)
   if (!table_menu.isColumnHidden(column))
  out << QString("<th>%1</th>").arg(table_menu.model()->headerData(column, Qt::Horizontal).toString());
  out << "</tr></thead>\n";

  for (int row = 0; row < rowCount; row++) {
  out << "<tr>";
  for (int column = 0; column < columnCount; column++) {
  if (!table_menu.isColumnHidden(column)) {
    QString data = table_menu.model()->data(table_menu.model()->index(row, column)).toString().simplified();
  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
   }
   }
  out << "</tr>\n";
   }
  out <<  "</table>\n"
   "<br><br>"
     <<"<br>"
   <<"<table border=1 cellspacing=0 cellpadding=2>\n";
   out << "<thead><tr bgcolor=#f0f0f0>";
   out <<  "</table>\n"
   "</body>\n"
   "</html>\n";

   QTextDocument *document = new QTextDocument();
      document->setHtml(strStream);
      QPrinter printer(QPrinter::PrinterResolution);
        QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
          if (dialog->exec() == QDialog::Accepted)
          {
           document->print(&printer);
        }

        delete document;


   QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
   if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

   printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setPaperSize(QPrinter::A4);
   printer.setOutputFileName(fileName);
   printer.setPageMargins(QMarginsF(15, 15, 15, 15));

   QTextDocument doc;
   doc.setHtml(strStream);
   doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
   doc.print(&printer);
}


void MainWindow::on_tab_widget_employe_tabBarClicked(int index)
{
  //  e.statistique(ui->widget_10);
}


void MainWindow::on_tab_widget_employe_currentChanged(int index)
{
   //e.statistique(ui->widget_10);
}


void MainWindow::on_pb_envoyer_5_clicked()
{
    QTextStream T(mSocket);
    T << ui->le_nickname_5->text() << ":" << ui->le_message_5->text();
    mSocket->flush();
    ui->le_message_5->clear();
}


void MainWindow::on_pb_connecter_5_clicked()
{
    Chatconnection CH(this);
    if (CH.exec() == QDialog::Rejected){
        return;
    }
    mSocket->connectToHost(CH.hostname(),CH.port());
}

void MainWindow::serial_read()
{
    if(serial->isReadable()&&arduino_available)
    {

     data = serial->readAll();
     serialBuffer +=QString::fromStdString(data.toStdString());
        qDebug()<<serialBuffer;

    }
}

void MainWindow::update_label()
{
    data=A.read_from_arduino();

QSqlQuery query;

    if(data=="1")
   {
        ui->etat_porte_5->setText("Ouvert");
       query.prepare("select * from employee where carte_id like '"+serialBuffer+"%'");

       if(query.exec())
       {
           while(query.next())
           {
              ui->cin_arduino_5->setText(query.value(0).toString());
              ui->nom_arduino_5->setText(query.value(1).toString());
              ui->prenom_arduino_5->setText(query.value(2).toString());
              ui->tel_arduino_5->setText(query.value(3).toString());
              ui->sexe_arduino_5->setCurrentText(query.value(7).toString());
              ui->adresse_arduino_5->setCurrentText(query.value(9).toString());

           }
       }
       //A.write_to_arduino(ui->prenom_arduino->text());

     }
   else if (data=="0" || data=="3")
         {
        ui->etat_porte_5->setText("Fermée");  // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher fermee

        ui->cin_arduino_5->clear();
        ui->nom_arduino_5->clear();
        ui->prenom_arduino_5->clear();
        ui->tel_arduino_5->clear();




    }
   else{
      ui->etat_porte_5->setText("Ouvert");
      ui->cin_arduino_5->clear();
      ui->nom_arduino_5->clear();
      ui->prenom_arduino_5->clear();
      ui->tel_arduino_5->clear();

    }
}


void MainWindow::on_open_door_arduino_6_clicked()
{
    A.write_to_arduino("2");
}


void MainWindow::on_close_door_arduino_5_clicked()
{
   A.write_to_arduino("3");
}
// ||||||||||||||||||||||||||||||||||malek

void MainWindow::on_pushButton_clicked()
{  if(ui->line_prix->text().toInt()>10&&ui->line_quant->text().toInt()>0)
    {
    Stocks *Stock =new Stocks(ui->line_id->text().toInt(),ui->line_nom->text(),ui->line_idcat->currentText().toInt(),ui->line_prix->text().toInt(),ui->line_quant->text().toInt(),ui->line_image->text());


   Stock->ajouter();
 //  Stocks *Stock =new Stocks();
    ui->tableView->setModel(Stock->Tri("select *from Stocks "));
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();


       notifyIcon->showMessage("Ajouter ","Ajouter succèses",QSystemTrayIcon::Information,15000);
    ui->line_nom->clear();
    ui->line_idcat->clear();
     ui->line_prix->clear();
      ui->line_quant->clear();
       ui->line_id->clear();
       ui->line_image->clear();
    }
    else
    {
       QMessageBox::information(this, "Controle de saisir"," prix >10 et quantiter >0");
    }


}



void MainWindow::aff()
{
    Stocks *Stock =new Stocks();
    ui->tableView->setModel(Stock->Tri("select *from Stocks "));
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->customPlot->setBackground(QBrush(gradient));

    // create empty bar chart objects:
    QCPBars *regen = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *nuclear = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *fossil = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    regen->setAntialiased(false); // gives more crisp, pixel aligned bar borders
    nuclear->setAntialiased(false);
    fossil->setAntialiased(false);
    regen->setStackingGap(1);
    nuclear->setStackingGap(1);
    fossil->setStackingGap(1);
    // set names and colors:
    fossil->setName("Quantiter /10");
    fossil->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    fossil->setBrush(QColor(111, 9, 176));

    nuclear->setPen(QPen(QColor(250, 170, 20).lighter(150)));
    nuclear->setBrush(QColor(250, 170, 20));

    regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    regen->setBrush(QColor(0, 168, 140));
    // stack bars on top of each other:
    nuclear->moveAbove(fossil);
    regen->moveAbove(nuclear);

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels,test;

   Stocks *aa =new Stocks();
     aa->count("select count(*) from stocks");
    // nbr=Stock->get_prix();
     for(int i=1;i<=aa->get_stat();i++)
     {
       ticks.push_back(i);
     }

    QSqlQuery query1("SELECT nom_produit FROM stocks ");
            while(query1.next())
            {
                labels.push_back(query1.value(0).toString());
            }





  //ticks << 1 << 2 << 3 ;
   // labels << "USA" << "Japan" << "Germany" << "France" << "UK" ;
    //labels.push_back("teeeeeeeeeeeest");
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->setRange(0, 8);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, 12.1);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> fossilData, nuclearData, regenData;
    QSqlQuery query("SELECT quantite FROM stocks ");
            while(query.next())
            {
                fossilData.push_back(query.value(0).toDouble()/10);
            }




              fossil->setData(ticks,fossilData);
//fossilData<<55<<44<<55;

   // nuclear->setData(ticks, nuclearData);
 //   regen->setData(ticks, regenData);

    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}








/*
void MainWindow::on_pushButton_2_clicked()
{ Stocks *Stock =new Stocks();
    ui->tableView->setModel(Stock->afficher());
}
*/
void MainWindow::on_pushButton_Supprimer_clicked()
{  Stocks *Stock =new Stocks();
    QItemSelectionModel *selection = ui->tableView->selectionModel();

    QModelIndex indexElementSelectionne = selection->currentIndex();
    if(selection->isSelected(indexElementSelectionne))
    {
    QVariant elementSelectionne = Stock->afficher()->data(indexElementSelectionne, Qt::DisplayRole);
  //  QMessageBox::information(this, "Elément sélectionné", elementSelectionne.toString());
    Stock->Supprimer(elementSelectionne.toInt());
    ui->tableView->setModel(Stock->Tri("select *from Stocks "));
    }
    else
     {  QMessageBox::warning(this,"Warning","select ID");}

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
     //  notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/charte graphique/icon.gif"));
      notifyIcon->showMessage("succèses ","Supprimer succèses",QSystemTrayIcon::Information,15000);
       // rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
      QLinearGradient gradient(0, 0, 0, 400);
      gradient.setColorAt(0, QColor(90, 90, 90));
      gradient.setColorAt(0.38, QColor(105, 105, 105));
      gradient.setColorAt(1, QColor(70, 70, 70));
     // ui->customPlot->setBackground(QBrush(gradient));

      // create empty bar chart objects:
    //  QCPBars *regen = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    //  QCPBars *nuclear = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    //  QCPBars *fossil = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    //  regen->setAntialiased(false); // gives more crisp, pixel aligned bar borders
    //  nuclear->setAntialiased(false);
    //  fossil->setAntialiased(false);
    //  regen->setStackingGap(1);
    //  nuclear->setStackingGap(1);
     // fossil->setStackingGap(1);
      // set names and colors:
     /* fossil->setName("Quantiter /10");
      fossil->setPen(QPen(QColor(111, 9, 176).lighter(170)));
      fossil->setBrush(QColor(111, 9, 176));

      nuclear->setPen(QPen(QColor(250, 170, 20).lighter(150)));
      nuclear->setBrush(QColor(250, 170, 20));

      regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
      regen->setBrush(QColor(0, 168, 140));
      // stack bars on top of each other:
      nuclear->moveAbove(fossil);
      regen->moveAbove(nuclear);

      // prepare x axis with country labels:
      QVector<double> ticks;
      QVector<QString> labels,test;

     Stocks *aa =new Stocks();
       aa->count("select count(*) from stocks");
      // nbr=Stock->get_prix();
       for(int i=1;i<=aa->get_stat();i++)
       {
         ticks.push_back(i);
       }

      QSqlQuery query1("SELECT nom_produit FROM stocks ");
              while(query1.next())
              {
                  labels.push_back(query1.value(0).toString());
              }





    //ticks << 1 << 2 << 3 ;
     // labels << "USA" << "Japan" << "Germany" << "France" << "UK" ;
      //labels.push_back("teeeeeeeeeeeest");
      QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
      textTicker->addTicks(ticks, labels);
      ui->customPlot->xAxis->setTicker(textTicker);
      ui->customPlot->xAxis->setTickLabelRotation(60);
      ui->customPlot->xAxis->setSubTicks(false);
      ui->customPlot->xAxis->setTickLength(0, 4);
      ui->customPlot->xAxis->setRange(0, 8);
      ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
      ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
      ui->customPlot->xAxis->grid()->setVisible(true);
      ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
      ui->customPlot->xAxis->setTickLabelColor(Qt::white);
      ui->customPlot->xAxis->setLabelColor(Qt::white);

      // prepare y axis:
      ui->customPlot->yAxis->setRange(0, 12.1);
      ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
      ui->customPlot->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
      ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
      ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
      ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
      ui->customPlot->yAxis->grid()->setSubGridVisible(true);
      ui->customPlot->yAxis->setTickLabelColor(Qt::white);
      ui->customPlot->yAxis->setLabelColor(Qt::white);
      ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
      ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

      // Add data:
      QVector<double> fossilData, nuclearData, regenData;
      QSqlQuery query("SELECT quantite FROM stocks ");
              while(query.next())
              {
                  fossilData.push_back(query.value(0).toDouble()/10);
              }

  /*
      QSqlQuery query1("SELECT quantite FROM stocks");
              while(query1.next())
              {
                  test.push_back(query.value(0).toString());
              }
  */




                //fossil->setData(ticks,fossilData);
  //fossilData<<55<<44<<55;

     // nuclear->setData(ticks, nuclearData);
   //   regen->setData(ticks, regenData);

      // setup legend:
                /*
      ui->customPlot->legend->setVisible(true);
      ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
      ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
      ui->customPlot->legend->setBorderPen(Qt::NoPen);
      QFont legendFont = font();
      legendFont.setPointSize(10);
      ui->customPlot->legend->setFont(legendFont);
      ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);*/
}

void MainWindow::on_pushButton_3_clicked()
{
    Stocks *Stock =new Stocks(ui->line_nom->text(),ui->line_idcat->currentText().toInt(),ui->line_prix->text().toInt(),ui->line_quant->text().toInt());
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    if(ui->line_quant->text().toInt()<=5)
    {
        Stock->set_vide(0);
    }
    else
    {
         Stock->set_vide(1);
    }
    if(selection->hasSelection())
    {
     QModelIndexList listeSelections = selection->selectedIndexes();

    QString elementsSelectionnes;
    QString id= Stock->afficher()->data(listeSelections[0], Qt::DisplayRole).toString();
    ui->line_id->setText(id);
    QString nom= Stock->afficher()->data(listeSelections[1], Qt::DisplayRole).toString();
    ui->line_nom->setText(nom);

    QString id_c= Stock->afficher()->data(listeSelections[2], Qt::DisplayRole).toString();
  //  ui->line_idcat->setText(id_c);
    QString prix= Stock->afficher()->data(listeSelections[3], Qt::DisplayRole).toString();
    ui->line_prix->setText(prix);

    QString quant= Stock->afficher()->data(listeSelections[4], Qt::DisplayRole).toString();
    ui->line_quant->setText(quant);


    Stock->Modifier(id.toInt());
     ui->tableView->setModel(Stock->Tri("select *from Stocks "));
     QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
         notifyIcon->show();


        notifyIcon->showMessage("Modifier ","Modifier succèses",QSystemTrayIcon::Information,15000);
     ui->line_nom->clear();
     ui->line_idcat->clear();
      ui->line_prix->clear();
       ui->line_quant->clear();
        ui->line_id->clear();

}
    else
        QMessageBox::warning(this,"Warning","select tous les champs");


}

void MainWindow::on_pushButton_4_clicked()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();
    if(selection->hasSelection())
    {
    QString elementsSelectionnes;


    QString id= Stock->afficher()->data(listeSelections[0], Qt::DisplayRole).toString();
    ui->line_id->setText(id);
    QString nom= Stock->afficher()->data(listeSelections[1], Qt::DisplayRole).toString();
    ui->line_nom->setText(nom);

    QString id_c= Stock->afficher()->data(listeSelections[2], Qt::DisplayRole).toString();
  //  ui->line_idcat->setText(id_c);
    QString prix= Stock->afficher()->data(listeSelections[3], Qt::DisplayRole).toString();
    ui->line_prix->setText(prix);

    QString quant= Stock->afficher()->data(listeSelections[4], Qt::DisplayRole).toString();
    ui->line_quant->setText(quant);

}
    else
        QMessageBox::warning(this,"Warning","select tous les champs");


    // ui->columnView->setModel(Stock->afficherseul(elementSelectionne.toString())->Ite));
// ui->line_id->setText(ui->tableView_2->showColumn()));


}

void MainWindow::on_trinom_clicked()
{
    Stocks *Stock =new Stocks();

    ui->tableView->setModel(Stock->Tri("select *from Stocks order by NOM_PRODUIT"));
}

void MainWindow::on_pushButton_ref_clicked()
{
    Stocks *Stock =new Stocks();

    ui->tableView->setModel(Stock->Tri("select *from Stocks "));
}

void MainWindow::on_nomdec_clicked()
{
    Stocks *Stock =new Stocks();

    ui->tableView->setModel(Stock->Tri("select *from Stocks order by NOM_PRODUIT DESC"));
}

void MainWindow::on_prix_clicked()
{
    Stocks *Stock =new Stocks();

    ui->tableView->setModel(Stock->Tri("select *from Stocks order by PRIX"));
}

void MainWindow::on_prixdec_clicked()
{
    Stocks *Stock =new Stocks();

    ui->tableView->setModel(Stock->Tri("select *from Stocks order by PRIX DESC"));
}

void MainWindow::on_quant_clicked()
{
    Stocks *Stock =new Stocks();

    ui->tableView->setModel(Stock->Tri("select *from Stocks order by QUANTITE "));

   Stock->test("110");
      QString i_d= QString::number(Stock->get_prix());
   ui->line_prix->setText(i_d);



}

void MainWindow::on_quantdec_clicked()
{
    Stocks *Stock =new Stocks();

    ui->tableView->setModel(Stock->Tri("select *from Stocks order by QUANTITE DESC "));

}

void MainWindow::on_ok_clicked()
{
    Stocks *Stock =new Stocks();
        ui->tableView->setModel(Stock->Rech(ui->line_rech->text()));

}

void MainWindow::on_pushButton_2_clicked()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir unfichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    ui->line_nom->setText(fichier);
  //  QMessageBox::information(this, "Fichier", "Vous avez sélectionné:\n" + fichier);
}

void MainWindow::on_pushButton_image_clicked()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();

    QModelIndex indexElementSelectionne = selection->currentIndex();
    if(selection->isSelected(indexElementSelectionne))
    {
    QVariant elementSelectionne = Stock->afficher()->data(indexElementSelectionne, Qt::DisplayRole);
    ui->label_8->setPixmap(QPixmap( elementSelectionne.toString()));

    }
    else
  QMessageBox::warning(this, "Elément sélectionné", "select nom de l'image");

}

void MainWindow::on_Qrcode_2_clicked()
{

    int tabeq=ui->tableView->currentIndex().row();
    QVariant idd=ui->tableView->model()->data(ui->tableView->model()->index(tabeq,0));
    QString numero= idd.toString();
    QSqlQuery qry;
    qry.prepare("select * from stocks where ID=:id");
    qry.bindValue(":id",numero);
    qry.exec();
    QString  Nom_produit,id_categorie,Prix,Quantiter;

    while(qry.next())
    {
        numero=qry.value(0).toString();
        Nom_produit=qry.value(1).toString();
        id_categorie=qry.value(2).toString();
        Prix=qry.value(3).toString();
          Quantiter=qry.value(4).toString();
    }
    numero=QString(numero);
    numero="ID:"+numero+"nom_produit:"+Nom_produit+"id_categorie:"+id_categorie+"Prix:"+Prix+"Quantiter:"+Quantiter;
    QrCode qr = QrCode::encodeText(numero.toUtf8().constData(), QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++)
    {
    for (int x = 0; x < qr.getSize(); x++)
    {
    int color = qr.getModule(x, y);  // 0 for white, 1 for black

    // You need to modify this part
    if(color==0)
       im.setPixel(x, y,qRgb(254, 254, 254));
    else
       im.setPixel(x, y,qRgb(0, 0, 0));
    }
    }
    im=im.scaled(200,200);
    ui->Qrcode->setPixmap(QPixmap::fromImage(im));

}

void MainWindow::on_Ajoutercat_clicked()
{
    Categorie *cate =new Categorie(ui->line_idcat_2->text().toInt(),ui->line_nomcateg->text());
      cate->ajouter();
    //  Stocks *Stock =new Stocks();
       ui->tableView->setModel(cate->afficher("select *from categorie "));
       ui->line_idcat_2->clear();
      ui->line_nomcateg->clear();


}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    Categorie *cate =new Categorie();
    ui->tableView->setModel(cate->afficher("select *from categorie "));

}


void MainWindow::on_Supprimercat_clicked()
{
     Categorie *cate =new Categorie();
        QItemSelectionModel *selection = ui->tableView->selectionModel();

        QModelIndex indexElementSelectionne = selection->currentIndex();
        if(selection->isSelected(indexElementSelectionne))
        {
        QVariant elementSelectionne = cate->afficher("select *from categorie ")->data(indexElementSelectionne, Qt::DisplayRole);
      //  QMessageBox::information(this, "Elément sélectionné", elementSelectionne.toString());
        cate->Supprimer(elementSelectionne.toInt());
       ui->tableView->setModel(cate->afficher("select *from categorie "));
        }
        else
           QMessageBox::warning(this,"Warning","select ID");
}

void MainWindow::on_Selectcat_clicked()
{    Categorie *cate =new Categorie(ui->line_idcat_2->text().toInt(),ui->line_nomcateg->text());

    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();
    if(selection->hasSelection())
    {
    QString elementsSelectionnes;


    QString id= cate->afficher("select *from categorie ")->data(listeSelections[0], Qt::DisplayRole).toString();
    ui->line_idcat_2->setText(id);
    QString nom=cate->afficher("select *from categorie ")->data(listeSelections[1], Qt::DisplayRole).toString();
   ui->line_nomcateg->setText(nom);
}
    else
        QMessageBox::warning(this,"Warning","select tous les champs");
}

void MainWindow::on_Modifiercat_clicked()
{
    Categorie *cate =new Categorie(ui->line_idcat_2->text().toInt(),ui->line_nomcateg->text());

      QItemSelectionModel *selection = ui->tableView->selectionModel();
      QModelIndexList listeSelections = selection->selectedIndexes();
      if(selection->hasSelection())
      {
      QString elementsSelectionnes;


      QString id= cate->afficher("select *from categorie ")->data(listeSelections[0], Qt::DisplayRole).toString();
      ui->line_idcat_2->setText(id);
      QString nom=cate->afficher("select *from categorie ")->data(listeSelections[1], Qt::DisplayRole).toString();
     ui->line_nomcateg->setText(nom);

    cate->Modifier(id.toInt());
     ui->tableView->setModel(cate->afficher("select *from categorie "));
    ui->line_idcat_2->clear();
   ui->line_nomcateg->clear();

}
    else
        QMessageBox::warning(this,"Warning","select tous les champs");


}

void MainWindow::on_load_clicked()
{
    Categorie *cate =new Categorie();
  ui->line_idcat->setModel(cate->afficher("select ID_CATEGORIE from categorie "));

}

void MainWindow::on_pushButton_ref_2_clicked()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir unfichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    ui->line_image->setText(fichier);
}



void MainWindow::on_pushButton_plusdet_clicked()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();
    if(selection->hasSelection())
    {
    QString elementsSelectionnes;


    QString id= Stock->afficher()->data(listeSelections[0], Qt::DisplayRole).toString();
 ui->label_id->setText(id);
    QString nom= Stock->afficher()->data(listeSelections[1], Qt::DisplayRole).toString();
    ui->label_nom->setText(nom);

    QString id_c= Stock->afficher()->data(listeSelections[2], Qt::DisplayRole).toString();
   ui->label_idgat->setText(id_c);
    QString prix= Stock->afficher()->data(listeSelections[3], Qt::DisplayRole).toString();
    ui->labelprix->setText(prix);

    QString quant= Stock->afficher()->data(listeSelections[4], Qt::DisplayRole).toString();
    ui->label_quan->setText(quant);
       QString image= Stock->afficher()->data(listeSelections[5], Qt::DisplayRole).toString();


        ui->label_21->setPixmap(QPixmap( image));

}
    else
        QMessageBox::warning(this,"Warning","select tous les champs");
}

void MainWindow::on_pushButton_ref_3_clicked()
{
    Stocks *Stock =new Stocks();

    ui->tableView->setModel(Stock->Tri("select *from Stocks "));
}

int MainWindow::rech(QString tab[],QCharRef c)
{
    for(int i=0;i<26;i++)
    {
        if(tab[i]==c)
            return i;
    }

}
void MainWindow::on_code_clicked()
{  QString tab[26];
    tab[0]='a';
      tab[1]='b';
      tab[2]='c';
      tab[3]='d';
      tab[4]='e';
      tab[5]='f';
      tab[6]='g';
      tab[7]='h';
      tab[8]='i';
      tab[9]='j';
      tab[10]='k';
       tab[11]='l';
        tab[12]='m';
         tab[13]='n';
          tab[14]='o';
            tab[15]='p';
              tab[16]='q';
                tab[17]='r';
                  tab[18]='s';
                    tab[19]='t';
                     tab[20]='u';
                      tab[21]='v';
                       tab[22]='w';
                          tab[23]='x';
                             tab[24]='y';
                                tab[25]='z';
                               // int a=rech(tab,ui->line_nom_2->text());
                                        //   QString i_d= QString::number((2*a+3)%26);

QString code;
                               //      ui->line_nom_3->setText(tab[((((ui->a->text().toInt())*a)+ui->b->text().toInt())%26)]);
                                     for(int i=0;i<ui->line_nom_2->text().size();i++)
                                     {
                                     int z=rech(tab,ui->line_nom_2->text()[i]);
                                     code+=tab[((((ui->a->text().toInt())*z)+ui->b->text().toInt())%26)];
                                 }
                                    ui->line_nom_3->setText(code);

}
 int MainWindow::decod(int a,int b,int dec)
 {
     for(int i=0;i<26;i++)
     {
         if(((a*i)%26)==(dec-b))
         {
             return i;
         }
         else if((((a*i)%26)-26)==(dec-b)) {
            return i;
         }

     }
 }
void MainWindow::on_dcode_clicked()
{ QString tab[26];
    tab[0]='a';
      tab[1]='b';
      tab[2]='c';
      tab[3]='d';
      tab[4]='e';
      tab[5]='f';
      tab[6]='g';
      tab[7]='h';
      tab[8]='i';
      tab[9]='j';
      tab[10]='k';
       tab[11]='l';
        tab[12]='m';
         tab[13]='n';
          tab[14]='o';
            tab[15]='p';
              tab[16]='q';
                tab[17]='r';
                  tab[18]='s';
                    tab[19]='t';
                     tab[20]='u';
                      tab[21]='v';
                       tab[22]='w';
                          tab[23]='x';
                             tab[24]='y';
                                tab[25]='z';
                            //    int dec=rech(tab,ui->line_nom_3->text());
QString decode;

//ui->line_nom_2->setText(tab[decod(ui->a->text().toInt(),ui->b->text().toInt(),dec)]);
for(int i=0;i<ui->line_nom_3->text().size();i++)
{
   int dec=rech(tab,ui->line_nom_3->text()[i]);
   decode+=tab[decod(ui->a->text().toInt(),ui->b->text().toInt(),dec)];

}
ui->line_nom_2->setText(decode);
}

void MainWindow::on_pushButton_ref_4_clicked()
{
    QString strStream;
                        QTextStream out(&strStream);

                        const int rowCount = ui->tableView->model()->rowCount();
                        const int columnCount = ui->tableView->model()->columnCount();

                        out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("strTitle")
                            <<  "</head>\n"
                            "<body bgcolor=#ffffff link=#5000A0>\n"

                           //     "<align='right'> " << datefich << "</align>"
                            "<center> <H1>Liste des commandes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                        // headers
                        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tableView->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";

                        // data table
                        for (int row = 0; row < rowCount; row++) {
                            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                            for (int column = 0 ; column < columnCount; column++) {
                                if (!ui->tableView->isColumnHidden(column)) {
                                    QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                }
                            }
                            out << "</tr>\n";
                        }
                        out <<  "</table> </center>\n"
                            "</body>\n"
                            "</html>\n";

                  QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                   QPrinter printer (QPrinter::PrinterResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setPaperSize(QPrinter::A4);
                  printer.setOutputFileName(fileName);

                   QTextDocument doc;
                    doc.setHtml(strStream);
                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                    doc.print(&printer);
}

void MainWindow::on_Ajoutercat_2_clicked()
{
    Categorie *cate =new Categorie();
  ui->tableView->setModel(cate->afficher("select * from categorie  order by  NOM_CATEGORIE"));
}

void MainWindow::on_Ajoutercat_3_clicked()
{
    Categorie *cate =new Categorie();
  ui->tableView->setModel(cate->afficher("select * from categorie  order by  NOM_CATEGORIE desc"));
}


void MainWindow::on_code_2_clicked()
{int z=ui->line_nom_2->text().size();
      QString f= QString::number(z);
   ui->line_nom_3->setText(f);
}



void MainWindow::on_line_rech_returnPressed()
{
    Stocks *Stock =new Stocks();
        ui->tableView->setModel(Stock->Rech(ui->line_rech->text()));
}



void MainWindow::on_line_rech_textChanged(const QString &arg1)
{
    Stocks *Stock =new Stocks();
        ui->tableView->setModel(Stock->Rech(ui->line_rech->text()));
}

void MainWindow::on_pushButton_ref_5_clicked()
{

   /* Stocks *Stock =new Stocks();
    ui->tableView->setModel(Stock->Tri("select *from Stocks "));

    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->customPlot->setBackground(QBrush(gradient));

    // create empty bar chart objects:
    QCPBars *regen = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *nuclear = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *fossil = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    regen->setAntialiased(false); // gives more crisp, pixel aligned bar borders
    nuclear->setAntialiased(false);
    fossil->setAntialiased(false);
    regen->setStackingGap(1);
    nuclear->setStackingGap(1);
    fossil->setStackingGap(1);
    // set names and colors:
    fossil->setName("Quantiter /10");
    fossil->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    fossil->setBrush(QColor(111, 9, 176));

    nuclear->setPen(QPen(QColor(250, 170, 20).lighter(150)));
    nuclear->setBrush(QColor(250, 170, 20));

    regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    regen->setBrush(QColor(0, 168, 140));
    // stack bars on top of each other:
    nuclear->moveAbove(fossil);
    regen->moveAbove(nuclear);

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels,test;

   Stocks *aa =new Stocks();
     aa->count("select count(*) from stocks");
    // nbr=Stock->get_prix();
     for(int i=1;i<=aa->get_stat();i++)
     {
       ticks.push_back(i);
     }

    QSqlQuery query1("SELECT nom_produit FROM stocks ");
            while(query1.next())
            {
                labels.push_back(query1.value(0).toString());
            }



*/

  //ticks << 1 << 2 << 3 ;
   // labels << "USA" << "Japan" << "Germany" << "France" << "UK" ;
    //labels.push_back("teeeeeeeeeeeest");
   /* QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->setRange(0, 8);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, 12.1);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> fossilData, nuclearData, regenData;
    QSqlQuery query("SELECT quantite FROM stocks ");
            while(query.next())
            {
                fossilData.push_back(query.value(0).toDouble()/10);
            }




              fossil->setData(ticks,fossilData);
//fossilData<<55<<44<<55;

   // nuclear->setData(ticks, nuclearData);
 //   regen->setData(ticks, regenData);

    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    */
 }





void MainWindow::on_tri_currentIndexChanged(const QString &arg1)
{
    Stocks *Stock =new Stocks();


        if(ui->tri->currentText()=="Nom")
        {
              ui->tableView->setModel(Stock->Tri("select *from Stocks order by NOM_PRODUIT"));
        }
      if(ui->tri->currentText()=="Nom dec")
        {
          ui->tableView->setModel(Stock->Tri("select *from Stocks order by NOM_PRODUIT desc"));
      }
      if(ui->tri->currentText()=="Prix")
        {
          ui->tableView->setModel(Stock->Tri("select *from Stocks order by PRIX"));
      }
      if(ui->tri->currentText()=="Prix dec")
        {
          ui->tableView->setModel(Stock->Tri("select *from Stocks order by PRIX DESC"));
      }
      if(ui->tri->currentText()=="Quantiter")
        {
          ui->tableView->setModel(Stock->Tri("select *from Stocks order by QUANTITE"));
      }
      if(ui->tri->currentText()=="Quantiter dec")
        {
          ui->tableView->setModel(Stock->Tri("select *from Stocks order by QUANTITE DESC"));
      }
}

void MainWindow::on_pushButton_5_clicked()
{Stocks *Stock =new Stocks();
    Stocks *a =new Stocks();
      ui->tableView->setModel(Stock->Tri("select *from Stocks where vide like 0"));
      Stock->count("select count(*) from Stocks where vide like 0");
      if(Stock->get_stat()!=0)
      {
          A.write_to_arduino("1");
      }
       a->count("select id from Stocks where vide like 0");
           QByteArray vid= QByteArray::number(a->get_stat());
        //   ui->line_prix->setText(vid);
       A.write_to_arduino(vid);
}



/*
void MainWindow::on_on_clicked()
{
       A.write_to_arduino("1");
}


void MainWindow::on_off_clicked()
{
       A.write_to_arduino("0");
}

void MainWindow::on_plus_clicked()
{
       A.write_to_arduino("2");
}

void MainWindow::on_mins_clicked()
{
       A.write_to_arduino("3");
}

*/

void MainWindow::on_pb_ajouter_6_clicked()
{

}


void MainWindow::on_retour_accueil_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}
// |||||||||||||||||||||||||||||-souhaaa
void MainWindow::affich()
{

  //  ui->setupUi(this);
    ui->tab_facture->setModel(ftmp.afficher());
    ui->tab_facture_2->setModel(ctmp.afficher());
    ui->idS_3->setVisible(false);
    ui->idS_5->setVisible(false);
    //ui->idS->setText("dd");
    //ui->idS->setReadOnly(1);
    ui->idS->setVisible(0);

    ui->tab_commande->setVisible(0);
            ui->pushButton->setVisible(0);
            ui->label_38->setVisible(0);
            ui->label_39->setVisible(0);
            ui->label_37->setVisible(0);
            ui->comboBox->setVisible(0);
            ui->montantS_3->setVisible(0);
            ui->montantS->setVisible(0);
            ui->prixProduitQuantite->setVisible(0);
            ui->prixProduit->setVisible(0);
            ui->pb_ajouter_2->setVisible(0);

    //ui->idS->setVisible(false);
    QSqlQuery q ;
    q.prepare("select concat(nom, concat(' ', prenom)) from employee where role like 'GFactures'");
    q.exec();
    if(q.next())
    {
        QString nomempl=q.value(0).toString();
        ui->nomEmp->setText(nomempl);
        ui->nomEmp->setReadOnly(1);
    }

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit->setReadOnly(1);
/*
    QPixmap image(":/resources/img/labrador.jpg");
    int w=ui->label_image->width();
    int h=ui->label_image->height();
    ui->label_image->setPixmap(image.scaled(w,h, Qt::KeepAspectRatio));
*/
    QPixmap logo(":/resources/img/logo sprint.png");
  /*  int wl=ui->label_logo->width();
    int hl=ui->label_logo->height();
    ui->label_logo->setPixmap(logo.scaled(wl,hl, Qt::KeepAspectRatio));*/
/*
    QPixmap nuitjour(":/resources/img/Mode-nuit-featured.png");
    int wn=ui->label_nuitjour->width();
    int hn=ui->label_nuitjour->height();
    ui->label_nuitjour->setPixmap(nuitjour.scaled(wn,hn, Qt::KeepAspectRatio));
*/
    QSqlQuery qr;
    qr.prepare("SELECT Sum(Factures.montant) AS SommeDemontant, extract(month from Factures.date_facture) FROM Clients INNER JOIN Factures ON Clients.Id_Client = Factures.Id_Client GROUP BY  extract(month from Factures.date_facture) order by extract(month from Factures.date_facture)");
    qr.exec();
    QBarSet *set0 = new QBarSet("chiffre d affaire par mois");
    while(qr.next() )
    {
        set0->append(qr.value(0).toInt());
    }
    QBarSeries *series = new QBarSeries();
        series->append(set0);
        QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Simple barchart example");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            QStringList categories;
                categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun"<<"JUL"<<"Aug"<<"sept"<<"Oct"<<"Nov"<<"Dec";
                QBarCategoryAxis *axisX = new QBarCategoryAxis();
                axisX->append(categories);
                chart->addAxis(axisX, Qt::AlignBottom);
                series->attachAxis(axisX);

                QValueAxis *axisY = new QValueAxis();
                axisY->setRange(0,20000);
                chart->addAxis(axisY, Qt::AlignLeft);
                series->attachAxis(axisY);
                chart->legend()->setVisible(true);
                chart->legend()->setAlignment(Qt::AlignBottom);
                QChartView *chartView = new QChartView(chart);
                chartView->setParent(ui->frame);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(700, 400);


              /*  QList<QWidget *> widgets = this->findChildren<QWidget *>();

                 QFile styleSheetFile(":/resources/img/Integrid.qss")    ;
                 styleSheetFile.open(QFile::ReadOnly) ;
                 QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
                   widgets.at(0)->setStyleSheet(styleSheet);*/
}

void MainWindow::on_pb_ajouter_clicked()
{
    //if(ui->montantS->text().toFloat()>10)
    //{
    //QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
    QDateTime date_facture= QDateTime::currentDateTime();

    int id_facture=ui->idS->text().toInt();
    //float montant=ui->montantS->text().toFloat();
    float montant=0;
    QString mode_paiement=ui->modeS->currentText();
    QString nom_employe=ui->nomEmp->text();
    QString nom_client=ui->comboBox_2->currentText();

    QSqlQuery query;
    query.prepare("select id_employe from employee where concat(nom, concat(' ', prenom)) like '"+nom_employe+"'");
    query.exec();

    QSqlQuery query2;
    query2.prepare("select id_client from clients where concat(NOM_CLIENT, concat(' ', PRENOM_CLIENT)) like '"+nom_client+"'");
    query2.exec();

    if (query.next() && query2.next())
   {

        int id_employe=query.value(0).toInt();
        int id_client=query2.value(0).toInt();



    factures f(id_facture, montant, mode_paiement, date_facture, id_employe, id_client);
    bool test=f.ajouter();


    if(test)
     {
      QMessageBox::information(nullptr, QObject::tr("OK"),
      QObject::tr("Ajout effectué.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
      ui->pb_ajouter->setVisible(0);
      ui->comboBox_2->setEnabled(0);
      ui->modeS->setEnabled(0);
      ui->tab_commande->setVisible(1);
              ui->pushButton->setVisible(1);
              ui->label_38->setVisible(1);
              ui->label_39->setVisible(1);
              ui->label_37->setVisible(1);
              ui->comboBox->setVisible(1);
              ui->montantS_3->setVisible(1);
              ui->montantS->setVisible(1);
              ui->prixProduitQuantite->setVisible(1);
              ui->prixProduit->setVisible(1);
              ui->pb_ajouter_2->setVisible(1);

      ui->tab_facture->setModel(ftmp.afficher());
     }
      else
      {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
       QObject::tr("Ajout non effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);
      }
    }
    //}
    else
    {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
     QObject::tr("Montant doit être superieur à 10.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_supprimer_clicked()
{
    int id=ui->idsupp->text().toInt();
    QModelIndexList indexes =  ui->tab_facture->selectionModel()->selectedRows();
    bool test=ftmp.supprimer(id);
    if(test)
     {
      QMessageBox::information(nullptr, QObject::tr("OK"),
      QObject::tr("Suppression effectué.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_facture->setModel(ftmp.afficher());
     }
      else
      {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
       QObject::tr("Suppression non effectuée.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);
      }
}

void MainWindow::on_tab_facture_clicked(const QModelIndex &index)
{
    QString val = ui->tab_facture->model()->data(index).toString();

    //int row =index.row();
    //int col=index.column();
    QTableWidgetItem item(0, 0) ;
    //cout << item << endl;
    if(index.column()==0)
    {
        ftmp.test(val);
        QString i_d= QString::number(ftmp.getMontant());
        ui->montantS_2->setText(i_d);
        ui->modeS_2->setCurrentText(ftmp.getMode_paiement());
        ui->dateS_2->setDateTime(ftmp.getDate_facture());
        ui->idS_2->setText(val);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
               QObject::tr("Cliquez sur la colonne id.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_miseajour_clicked()
{
    int id_facture=ui->idS_2->text().toInt();
    float montant=ui->montantS_2->text().toFloat();
    QString mode_paiement=ui->modeS_2->currentText();
    QDateTime date_facture=ui->dateS_2->dateTime();
    int id_employe=ui->comboBox_3->currentText().toInt();
    int id_client=ui->comboBox_4->currentText().toInt();

    factures f(id_facture, montant, mode_paiement, date_facture, id_employe, id_client);
    bool test=f.modifier(id_facture);
    if(test)
     {
      QMessageBox::information(nullptr, QObject::tr("OK"),
      QObject::tr("modification effectuée.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_facture->setModel(f.afficher());
     }
      else
      {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
       QObject::tr("modification non effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);
      }
}
//////////commandes//////////////////////////////////////////////////////////////////////////////////////////////////


void MainWindow::on_pb_ajouter_2_clicked()
{
    if(ui->montantS_3->text().toInt()>0)
    {
        int id_commande=ui->idS_3->text().toInt();
        int quantite=ui->montantS_3->text().toInt();
        QString nom_produit=ui->comboBox->currentText();
        QSqlQuery r;
        r.prepare("select id_facture from factures where id_facture like (select max(id_facture) from factures)");
        r.exec();
        if(r.next())
        {
            int id_facture=r.value(0).toInt();

            QSqlQuery query;
            query.prepare("select id_produit from stocks where nom_produit like '"+nom_produit+"' ");
            query.exec();

            if (query.next())
           {
                int id_produit=query.value(0).toInt();

                QString idprodstr=QString::number(id_produit);
                commandes c(id_commande, quantite, id_produit,id_facture );
                bool test=c.ajouter();

                if(test)
                {


                     QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
                     //int *prix= new int (ui->prixProduit->text().toInt());
                     //*prix+=*prix;
                     int id_facture1=ui->idS_2->text().toInt();
                     float montant=ui->montantS->text().toFloat();
                     QString mode_paiement=ui->modeS_2->currentText();
                     QDateTime date_facture=ui->dateS_2->dateTime();
                     int id_employe=ui->comboBox_3->currentText().toInt();
                     int id_client=ui->comboBox_4->currentText().toInt();

                     factures f(id_facture1, montant, mode_paiement, date_facture, id_employe, id_client);
                     //cout<<ui->montantS->text().toStdString()<<"hhh";
                     bool test=f.calcul(ui->prixProduitQuantite->text());
                     if(test)
                         ui->tab_facture->setModel(f.afficher());
                     QString id_facturestr=QString::number(id_facture);
                     QSqlQuery qr;
                     qr.prepare("select montant from factures where id_facture like '"+id_facturestr+"'");
                     qr.exec();
                     if(qr.next())
                        ui->montantS->setText(qr.value(0).toString());
                     ui->montantS_3->clear();
                     ui->prixProduit->clear();
                     ui->prixProduitQuantite->clear();

                     ui->tab_commande->setModel(ctmp.afficheractif(id_facturestr));
                     ui->tab_facture_2->setModel(ctmp.afficher());


                }
                else
                {
                    QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Ajout non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
                }
           }
        }
    }

    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
        QObject::tr("La quantite de doit être superieur à 0.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_supprimer_2_clicked()
{

    int id=ui->idsupp_2->text().toInt();
    bool test=ctmp.supprimer(id);
    if(test)
     {
      QMessageBox::information(nullptr, QObject::tr("OK"),
      QObject::tr("Suppression effectué.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_facture_2->setModel(ctmp.afficher());
     }
      else
      {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
       QObject::tr("Suppression non effectuée.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);
      }
}

void MainWindow::on_tab_facture_2_clicked(const QModelIndex &index)
{
    QString val = ui->tab_facture_2->model()->data(index).toString();
    if(index.column()==0)
    {
        ctmp.test(val);
        QString i_d= QString::number(ctmp.getQuantite());
        ui->montantS_4->setText(i_d);
        ui->idS_4->setText(val);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
               QObject::tr("Cliquez sur la colonne id.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_miseajour_2_clicked()
{
    int id_commande=ui->idS_4->text().toInt();
    int quantite=ui->montantS_4->text().toInt();
    int id_produit=ui->comboBox->currentText().toInt();
    int id_facture=ui->comboBox_4->currentText().toInt();

    commandes c(id_commande, quantite, id_produit,id_facture );
    bool test=c.modifier(id_commande);
    if(test)
     {
      QMessageBox::information(nullptr, QObject::tr("OK"),
      QObject::tr("modification effectuée.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_facture_2->setModel(c.afficher());
     }
      else
      {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
       QObject::tr("modification non effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);
      }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////commandes
void MainWindow::on_pushButton3_clicked()
{
    QSqlQueryModel * modal= new QSqlQueryModel();
    Connection c;

    QSqlQuery* qry =new QSqlQuery(c.db);
    qry->prepare("select nom_produit,id_produit from stocks");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox->setModel(modal);
}

void MainWindow::on_pushButton_10_clicked()
{
    QSqlQueryModel * modal= new QSqlQueryModel();
    Connection c;

    QSqlQuery* qry =new QSqlQuery(c.db);
    qry->prepare("select id_facture from factures");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox_4->setModel(modal);
}
////factures
/// /// je dois la modifier mettre systematiquement le nom de l employe connecte
void MainWindow::on_pushButton_employe_clicked()
{
    QSqlQueryModel * modal= new QSqlQueryModel();
    Connection c;

    QSqlQuery* qry =new QSqlQuery(c.db);
    qry->prepare("select concat(nom, concat(' ', prenom)) from employee where role like 'GFactures' ");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox_3->setModel(modal);

}

void MainWindow::on_pushButton_client_clicked()
{
    QSqlQueryModel * modal= new QSqlQueryModel();
    Connection c;

    QSqlQuery* qry =new QSqlQuery(c.db);
    qry->prepare("select concat(NOM_CLIENT, concat(' ', PRENOM_CLIENT)) from clients ");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox_2->setModel(modal);
}



void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index>=0)
    {
        QString nom_produit=ui->comboBox->currentText();
        //std::cout<<nom_produit.toStdString();
        QSqlQuery requete;
        requete.prepare("select prix from stocks where nom_produit like '"+nom_produit+"' ");
        requete.exec();

        if(requete.next())
        {
            QString prix_unit=requete.value(0).toString();
            ui->prixProduit->setText(prix_unit);
            ui->prixProduitQuantite->setText(prix_unit);
            ui->prixProduit->setReadOnly(1);
            ui->prixProduitQuantite->setReadOnly(1);
            ui->montantS_3->setText("1");
        }
    }
}



void MainWindow::on_montantS_3_textChanged(const QString &arg1)
{
    QString nom_produit=ui->comboBox->currentText();
    QSqlQuery query;
    query.prepare("select prix from stocks where nom_produit like '"+nom_produit+"' ");
    query.exec();
    if(query.next())
    {
        float prix_unit=query.value(0).toFloat();
        int quantite=arg1.toInt();
        QString multiplication= QString::number(prix_unit*quantite);
        ui->prixProduitQuantite->setText(multiplication);
    }
}
/*
QString id_produit1=query.value(0).toString();
QPushButton *bouton = new QPushButton (id_produit1, this);
ui->horizontalLayout->addWidget(bouton);
*/

/*
QString imgPath = "C:\\Souha\\HTML\\labrador.jpg";
QImage *img = new QImage(imgPath);

QTableWidget     *thumbnailsWidget = new QTableWidget;
QTableWidgetItem *thumbnail = new QTableWidgetItem;
thumbnail->setData(Qt::DecorationRole, QPixmap::fromImage(*img));

thumbnailsWidget->setColumnCount(5);
thumbnailsWidget->setRowCount(3);
thumbnailsWidget->setItem(0, 0, thumbnail);

setCentralWidget(thumbnailsWidget);
*/

//std::cout<<requete.toStdString();

/*
 * QSqlQuery r;
    r.prepare("select id_facture from factures where num like (select max(num) from factures)");
    r.exec();
    if(r.next())
    {
        int id_factureee=r.value(0).toInt();
        dernieridfact=&id_factureee;
        cout<<*dernieridfact<<" ajout facture "<<endl;
    }

                    //int nouvellequantite=qu;
                    QString quantitestr=QString::number(quantite);
                    QSqlQuery q;
                    q.prepare("update stocks set quantite=:quantite-'"+quantitestr+"' where id_produit like '"+idprodstr+"'");
                    q.exec();
                    if(q.next())
                        cout<<"cc";
*/


/*


*/

void MainWindow::on_pb_terminer_clicked()
{


    ui->tab_commande->setVisible(0);
    ui->pushButton->setVisible(0);
    ui->label_38->setVisible(0);
    ui->label_39->setVisible(0);
    ui->label_37->setVisible(0);
    ui->comboBox->setVisible(0);
    ui->montantS_3->setVisible(0);
    ui->montantS->setVisible(0);
    ui->prixProduitQuantite->setVisible(0);
    ui->prixProduit->setVisible(0);
    ui->pb_ajouter_2->setVisible(0);
    ui->pb_ajouter->setVisible(1);
    ui->comboBox_2->setEnabled(1);
    ui->modeS->setEnabled(1);


}

void MainWindow::on_pb_tri_id_clicked()
{

    ui->tab_facture->setModel(ftmp.tridate());
}

void MainWindow::on_pbimp_clicked()
{

    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tab_facture->model()->rowCount();
    const int columnCount = ui->tab_facture->model()->columnCount();

    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"

            //     "<align='right'> " << datefich << "</align>"
            "<center> <H1>Liste des commandes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

            // headers
     out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
            for (int column = 0; column < columnCount; column++)
                 if (!ui->tab_facture->isColumnHidden(column))
                     out << QString("<th>%1</th>").arg(ui->tab_facture->model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                            // data table
                            for (int row = 0; row < rowCount; row++) {
                                out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                for (int column = 0 ; column < columnCount; column++) {
                                    if (!ui->tab_facture->isColumnHidden(column)) {
                                        QString data = ui->tab_facture->model()->data(ui->tab_facture->model()->index(row, column)).toString().simplified();
                                        out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                    }
                                }
                                out << "</tr>\n";
                            }
                            out <<  "</table> </center>\n"
                                "</body>\n"
                                "</html>\n";

                       QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                       if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                       QPrinter printer (QPrinter::PrinterResolution);
                       printer.setOutputFormat(QPrinter::PdfFormat);
                       printer.setPaperSize(QPrinter::A4);
                       printer.setOutputFileName(fileName);

                       QTextDocument doc;
                       doc.setHtml(strStream);
                       doc.setPageSize(printer.pageRect().size());
                       doc.print(&printer);
}

void MainWindow::on_pushButton_client_2_clicked()
{
    QSqlQueryModel * modal= new QSqlQueryModel();
    Connection c;

    QSqlQuery* qry =new QSqlQuery(c.db);
    qry->prepare("select concat(NOM_CLIENT, concat(' ', PRENOM_CLIENT)) from clients ");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox_5->setModel(modal);
}

void MainWindow::on_barre_recherche_2_textChanged(const QString &arg1)
{
    if(ui->barre_recherche_2->text().isEmpty())
        ui->tab_facture_2->setModel(ctmp.afficher());
    else
      ui->tab_facture_2->setModel(ctmp.recherche(arg1));
}

void MainWindow::on_barre_recherche_textChanged(const QString &arg1)
{
    if(ui->barre_recherche->text().isEmpty())
        ui->tab_facture->setModel(ftmp.afficher());
    else
      ui->tab_facture->setModel(ftmp.recherche(arg1));
}

void MainWindow::on_pb_tri_quantite_clicked()
{
    ui->tab_facture_2->setModel(ctmp.triquantite());
}

void MainWindow::on_pb_journuit_clicked()
{

   /*     QList<QWidget *> widgets = this->findChildren<QWidget *>();

         QFile styleSheetFile(":/resources/img/Darkeum.qss")    ;
         styleSheetFile.open(QFile::ReadOnly) ;
         QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
           widgets.at(0)->setStyleSheet(styleSheet);



   ui->pb_journuit->setStyleSheet("background-color: rgb(128, 128, 128)");

   ui->tabWidget->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pb_tri_id->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pbimp->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pbimp_2->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pbimp_3->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pb_ajouter->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pushButton->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pb_terminer->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pb_ajouter_2->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pb_miseajour->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pb_supp_form->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pb_supprimer->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pushButton_4->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pushButton_5->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pushButton_6->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pushButton_7->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pushButton_8->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pushButton_10->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pb_miseajour_2->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pb_supp_form_2->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pb_supprimer_2->setStyleSheet("background-color: rgb(128, 128, 128)");
   ui->pb_tri_quantite->setStyleSheet("background-color: rgb(128, 128, 128)");

*/
}

void MainWindow::on_pb_journuit_2_clicked()
{
    /*QList<QWidget *> widgets = this->findChildren<QWidget *>();

     QFile styleSheetFile(":/resources/img/Integrid.qss")    ;
     styleSheetFile.open(QFile::ReadOnly) ;
     QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
     widgets.at(0)->setStyleSheet(styleSheet);*/
}

/*
void MainWindow::creeraction()
{
    QAction *a_modeNuit = new QAction(QIcon("image/modenuit.png"), "&Mode nuit", this);
    a_modeNuit->setShortcut(QKeySequence(Qt::Key_F3));
    connect(a_modeNuit, SIGNAL(triggered()), this, SLOT(paintEvent(QPaintEvent *event)));
}
void MainWindow::paintevent(QPaintEvent *event)
{
    paintEvent(event);
        if (invert)
            {
                 QPainter p(this);
                 p.setCompositionMode(QPainter::CompositionMode_Difference);
                 p.fillRect(event->rect(), Qt::white);
                 p.end();
            }
}*/
// feddddiiii ||||||||||||||||||||||||||||||||||||||||||||||||
void MainWindow::controle_de_saisie()
{
    QRegularExpression rx("^\\S*$" , QRegularExpression::CaseInsensitiveOption);
    ui->nom_ajout_machine->setValidator(new QRegularExpressionValidator(rx, this));
    ui->nom_machine_modif->setValidator(new QRegularExpressionValidator(rx, this));
    ui->date_modif->setMaximumDate( QDate::currentDate() );
    ui->date_machine_ajout->setMaximumDate( QDate::currentDate() );
}

void MainWindow::update_output_data()
{

    ui->affichage_maintenance->setModel( M.afficher(trie) );
    ui->affichage_machine->setModel( MM.afficher() );
    ui->ID_machine_ajout->setModel( MM.afficher_nom() );
    ui->id_maintenance_modif->setModel(M.afficher(trie) );
    ui->id_machine_affchage_3->setModel( MM.afficher_nom() );
    ui->id_machine_modif->setModel(MM.afficher_nom());
    ui->nom_produit->setModel(M.afficher_nom_produit());

}

////////////////////////////////////////////////////////////////////////
/// statistique
///


void MainWindow::statistique()
{

    QString   nom_machines ;
    int count ,id_machine;
    QPieSeries *series = new QPieSeries();


    QSqlQuery query,nom_mach ;
    query.prepare("select count(id_maintenance),id_machine from maintenances group by id_machine order by count(id_maintenance) desc ");
    query.exec();

    while(query.next())
    {
        count = query.value(0).toInt();
        id_machine =query.value(1).toInt();
        nom_mach.prepare("select nom_machine from machines where id_machine = :id");
        nom_mach.bindValue(":id",id_machine);
        nom_mach.exec();
        nom_mach.next();
        nom_machines=nom_mach.value(0).toString();
        series->append(nom_machines, count);
    }

    //series->setLabelsVisible();
/*    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
*/
    for(auto slice : series->slices())
    {
        QString nom=slice->label();
        slice->setLabel(QString(nom+"\n%1%").arg(100*slice->percentage(), 0, 'f', 1));
    }


    QPieSlice *slice = series->slices().at(0);
    //QString nom=slice->label();
    //slice->setLabel(QString(nom+"\n%1%").arg(100*slice->percentage(), 0, 'f', 1));
    //qInfo() << slice->percentage();
    slice->setLabelVisible(true);
    slice->setExploded(true);
    slice->setPen(QPen(Qt::darkGreen, 2));
    slice->setBrush(Qt::green);


    QChart *chart = new QChart();
    chart->addSeries(series);
    //chart->legend()->setVisible(false);
    chart->setTitle("Taux De Maintenance Par Machine ");
    chart->setAnimationOptions(QChart::AllAnimations);


    QChartView *chartview = new QChartView(chart);
    chartview->setParent(ui->statistique);
}



void MainWindow::on_exit_triggered()
{
    QApplication::quit();
}

///////////////////////////////////////////////////////////////////////////////////
//les bouttons du tableau de bord

/*
void MainWindow::on_pushButton_6_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_3);
}
void MainWindow::on_pushButton_12_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_4);
}
void MainWindow::on_pushButton_2_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_2);
}
void MainWindow::on_pushButton_11_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_3);
}
void MainWindow::on_pushButton_13_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_3);
}
void MainWindow::on_pushButton_18_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_7);
}
void MainWindow::on_pushButton_16_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_5);
}
void MainWindow::on_pushButton_17_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_6);
}
void MainWindow::on_pushButton_19_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_6);
}

/////////////////////////////////////////////////////////////////////////////////////////

*/



void MainWindow::initialisation_demarage()
{
    on_pushButton_7_clicked();
    on_pushButton_9_clicked();
    on_pushButton_21_clicked();
    on_pushButton_20_clicked();
   // ui->tabWidget_3fedi->setCurrentWidget(ui->tab_1);
}

////////////////////////////////////
/// \brief MainWindow::on_pushButton_clicked
/// ajouter une maintenance
void MainWindow::on_pushButton_aj_clicked()
{
    if(ui->description_machine_ajout->toPlainText().isEmpty() || ui->ID_machine_ajout->currentText().isEmpty() )
    {
        QMessageBox::warning(this,"ATTENTION!!!" , "Veuillez remplir toutes les cases !");
    }
    else {
        if (ui->description_machine_ajout->toPlainText().length() > 200)
        {
            QMessageBox::critical(this,
                                  "Error",
                                  "Veuiller saisir au maximaum 200 charactères!! ");
        }
        else
        {

        QString description = ui->description_machine_ajout->toPlainText() ;
        QDate date = ui->date_machine_ajout->date() ;
        int ID = ui->ID_machine_ajout->currentText().toInt() ;

        Maintenance ajout( ID , description , date );

        bool test = ajout.ajouter();

        if(test)
        {
            on_pushButton_7_clicked();
            update_output_data();
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectue."), QMessageBox::Ok);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("OK"), QObject::tr("Ajout non effectue\n" "Veuillez réessayer."), QMessageBox::Ok);
        }
        }
    }
}
////////
/// \brief MainWindow::on_pushButton_7_clicked
///bouton initialisation
void MainWindow::on_pushButton_7_clicked()
{
    ui->description_machine_ajout->setText("");
    ui->date_machine_ajout->setDate( QDate::currentDate() ) ;
    ui->ID_machine_ajout->setCurrentIndex(-1);
}



void MainWindow::warning ()
{
    QMessageBox::warning(this,"ERREUR!!!!!" ,"Erreur lors de Connection à la base de donnée");
}

////////////////////
///
/// ajouter une machine
void MainWindow::on_pushButton_8_clicked()
{
    if(ui->nom_ajout_machine->text().isEmpty() )
    {
        QMessageBox::warning(this,"ATTENTION!!!" , "Veuillez remplir toutes les cases !!!");
    }
    else {

        QString nom = ui->nom_ajout_machine->text() ;


        Machine ajout( nom);

        bool test = ajout.ajouter();

        if(test)
        {
            on_pushButton_9_clicked();
            update_output_data();
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectue."), QMessageBox::Ok);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("OK"), QObject::tr("Ajout non effectue\n" "Veuillez réessayer."), QMessageBox::Ok);
        }
    }
}


////////
///
///bouton initialisation
void MainWindow::on_pushButton_9_clicked()
{
    ui->nom_ajout_machine->setText("");
}


////////////////////
/// \brief MainWindow::on_pushButton_3_clicked
///supprimer une maintenance

void MainWindow::on_pushButton_fedi_clicked()
{

    if(ui->affichage_maintenance->selectionModel()->hasSelection() ) //check if has selection
    {
            QModelIndex ligne ;
        QItemSelectionModel* selectionModel = ui->affichage_maintenance->selectionModel();
           QModelIndexList selected = selectionModel->selectedRows();

            for(int i= 0; i< selected.count();i++)
           {
                  ligne = selected.at(i);
           }
            int id= ui->affichage_maintenance->model()->data(ligne).toInt();

             QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "confirmation", "voulez vous  vraiment supprimer ?");

            if (reply == QMessageBox::Yes) {

                bool test = M.supprimer(id);
                if(test)
                {
                   update_output_data();
                    QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectue."), QMessageBox::Ok);
                }
                else {
                    QMessageBox::critical(nullptr, QObject::tr("OK"), QObject::tr("Suppression non effectue\n" "Veuillez réessayer."), QMessageBox::Ok);
                }
              }
    }
}

////////////////
///  MainWindow::on_pushButton_5_clicked
///supprimer une machine

void MainWindow::on_pushButton_supfedimachin_clicked()
{
    if(ui->affichage_machine->selectionModel()->hasSelection() ) //check if has selection
    {
            QModelIndex ligne ;
        QItemSelectionModel* selectionModel = ui->affichage_machine->selectionModel();
           QModelIndexList selected = selectionModel->selectedRows();

            for(int i= 0; i< selected.count();i++)
           {
                  ligne = selected.at(i);
           }

            int id= ui->affichage_machine->model()->data(ligne).toInt();
             QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "confirmation", "voulez vous  vraiment supprimer ?");

            if (reply == QMessageBox::Yes) {

                bool test = MM.supprimer(id);
                if(test)
                {
                    update_output_data();
                    QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectue."), QMessageBox::Ok);
                }
                else {
                    QMessageBox::critical(nullptr, QObject::tr("OK"), QObject::tr("Suppression non effectue\n" "Veuillez réessayer."), QMessageBox::Ok);
                }
              }
    }
}


void MainWindow::on_id_maintenance_modif_currentTextChanged(const QString &arg1)
{


    ///////////////////////////////
    int id   = arg1.toInt() ;
    int id_machine ;
    QDate date;
    QString desc;
    /////////////////////////////////////

    M.afficher_une_maintenances(id , id_machine , date , desc);
    QString id_M = QString::number(id_machine);

    ui->id_machine_modif->setCurrentText( id_M );
    ui->desc_modif->setText(desc);
    ui->date_modif->setDate(date);


}


void MainWindow::on_pushButton_6_clicked()
{

    if(ui->affichage_maintenance->selectionModel()->hasSelection() ) //check if has selection
    {

    QModelIndex ligne ;
    QItemSelectionModel* selectionModel = ui->affichage_maintenance->selectionModel();
    QModelIndexList selected = selectionModel->selectedRows();

    for(int i= 0; i< selected.count();i++)
   {
          ligne = selected.at(i);
   }
    QString id= ui->affichage_maintenance->model()->data(ligne).toString();

    //qInfo() << id ;

    ui->id_maintenance_modif->setCurrentText( id );

    on_id_maintenance_modif_currentTextChanged(id);

    ui->tabWidget->setCurrentWidget(ui->tab_4);

   }
}



void MainWindow::on_id_machine_affchage_3_currentTextChanged(const QString &arg1)
{
    ///////////////////////////////
    int id = arg1.toInt() ;
    QString name;
    /////////////////////////////////////

    MM.afficher_une_machines(id , name);
    ui->nom_machine_modif->setText(name);
}



void MainWindow::on_pushButton_modiffedimachin_clicked()
{
    if(ui->affichage_machine->selectionModel()->hasSelection() ) //check if has selection
    {
            QModelIndex ligne ;
        QItemSelectionModel* selectionModel = ui->affichage_machine->selectionModel();
           QModelIndexList selected = selectionModel->selectedRows();

            for(int i= 0; i< selected.count();i++)
           {
                  ligne = selected.at(i);
           }

            QString id= ui->affichage_machine->model()->data(ligne).toString();

            ui->id_machine_affchage_3->setCurrentText( id );

            on_id_machine_affchage_3_currentTextChanged(id);

            ui->tabWidget->setCurrentWidget(ui->tab_7);
    }
}


void MainWindow::on_pushButton_14_clicked()
{
    if(ui->desc_modif->toPlainText().isEmpty() )
    {
        QMessageBox::warning(this,"ATTENTION!!!" , "Veuillez remplir toutes les cases !");
    }
    else {
        if (ui->desc_modif->toPlainText().length() > 200 )
                {
                    QMessageBox::critical(this,
                                          "Error",
                                          "Veuiller saisir au maximaum 200 charactères!! ");
                }
                else
                {

        QString description = ui->desc_modif->toPlainText() ;
        QDate date = ui->date_modif->date() ;
        int ID_M = ui->id_machine_modif->currentText().toInt() ;
        int ID = ui->id_maintenance_modif->currentText().toInt() ;

        Maintenance modif( ID_M , description , date );

        bool test = modif.modifier_maintenances(ID);

        if(test)
        {
            update_output_data();
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Modification effectue."), QMessageBox::Ok);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("OK"), QObject::tr("Modification non effectue\n" "Veuillez réessayer."), QMessageBox::Ok);
        }
        }
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    if(ui->nom_machine_modif->text().isEmpty() )
    {
        QMessageBox::warning(this,"ATTENTION!!!" , "Veuillez remplir toutes les cases !");
    }
    else {

        QString nom = ui->nom_machine_modif->text();
        int ID = ui->id_machine_affchage_3->currentText().toInt() ;

        Machine modif(  nom );

        bool test = modif.modifier_machine(ID);

        if(test)
        {
            update_output_data();
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Modification effectue."), QMessageBox::Ok);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("OK"), QObject::tr("Modification non effectue\n" "Veuillez réessayer."), QMessageBox::Ok);
        }
    }
}

void MainWindow::on_annuler_clicked()
{
    trie=-1;
    ui->comboBox->setCurrentIndex(-1);
   ui->affichage_maintenance->setModel( M.afficher(trie) );
   ui->recherche->setText("");
}


void MainWindow::on_pushButton_21_clicked()
{
     ui->id_machine_affchage_3->setCurrentIndex(-1);
    ui->nom_machine_modif->setText("")  ;
}

void MainWindow::on_pushButton_20_clicked()
{
    ui->desc_modif->setText("")  ;
     ui->id_maintenance_modif->setCurrentIndex(-1);
    ui->date_modif->setDate( QDate::currentDate() ) ;
}

void MainWindow::on_rech_clicked()
{
    QString recherche = ui->recherche->text();
    ui->affichage_maintenance->setModel( M.recherche_par_machine(recherche));
}

void MainWindow::on_actionImprimmer_triggered()
{
    QPrinter printer;
    //printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    //printer.setPaperSize(QPrinter::A4);

    QString path =QFileDialog::getSaveFileName(NULL,"Emplacement du fichier","C:/Users/fedi1/Documents/Gestion_de_maintenance/PDF/","PDF(*.pdf)");
    if(path.isEmpty()) return;

    printer.setOutputFileName(path);


    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->affichage_maintenance->model()->rowCount();
    const int columnCount = ui->affichage_maintenance->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
            "<center><p><H1>SPRINT </H1></p></center>"
            "</center><p><H1>TABLEAU DES MAINTENANCES : </H1></p></center>"
        "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->affichage_maintenance->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->affichage_maintenance->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->affichage_maintenance->isColumnHidden(column)) {
                QString data = ui->affichage_maintenance->model()->data(ui->affichage_maintenance->model()->index(row, column)).toString();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);
    document->print(&printer);




}



void MainWindow::on_comboBox_trifadi_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0 :
        trie = index;
        break;
    case 1 :
        trie = index;
        break;
    case 2 :
        trie = index;
        break;
    }
    update_output_data();
}


void MainWindow::on_Imprimer_clicked()
{
    on_actionImprimmer_triggered();
}


void MainWindow::on_tabWidget_3fedi_tabBarClicked(int index)
{

    if(index==3)
            statistique();
}


void MainWindow::on_recherche_textChanged(const QString &arg1)
{
    //QString recherche = ui->recherche->text();
    if(arg1.isEmpty())
    {
        on_annuler_clicked();
    }
    else
    ui->affichage_maintenance->setModel( M.recherche_par_machine(arg1));
}

void MainWindow::on_checkBox_toggled(bool checked)
{

    if(checked)
    {
       // A.serial_read(nbf) ;
        ui->nom_papier_L->setVisible(true);
        ui->nom_produit->setVisible(true);
        ui->nom_produit->setCurrentIndex(-1);
        A.write_to_arduino("1");
    }
    else{
        A.write_to_arduino("0");
        A.write_to_arduino("0");
        ui->papier->setVisible(false);

        ui->nom_papier_L->setVisible(false);
        ui->nom_produit->setVisible(false);
        ui->lcdNumber->setVisible(false);
    }
}
/*

void MainWindow::on_nom_produit_currentTextChanged(const QString &arg1)
{
    if(ui->checkBox->isChecked() && ui->nom_produit->currentIndex()!= -1)
    {
            ui->papier->setVisible(true);
            ui->lcdNumber->setVisible(true);
    }
            A.write_to_arduino("333");
     int poids;
     poids=M.poids(arg1);
     for(int i=0 ; i<=poids ; i++)
     {
         A.write_to_arduino("22");
     }

}*/

 /*void MainWindow::recup()
 {
     A.serial_read(nbf);
     ui->lcdNumber->display(nbf);
 }
*/







void MainWindow::on_retour_accueil_2_clicked()
{
  ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_retour_accueil_3_clicked()
{
  ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_retour_accueil_4_clicked()
{

             ui->stackedWidget->setCurrentIndex(3);
}
