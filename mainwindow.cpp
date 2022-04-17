#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include "login.h"
#include "chatconnection.h"
#include <QMessageBox>
#include <QString>
#include <QIntValidator>
#include <QSqlQuery>
#include <QSqlError>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QTextStream>
#include <QTextDocument>
#include "QFileDialog"
#include<QSslSocket>
#include <QPrintDialog>
#include"QPainter"
#include"QDesktopServices"
#include"QtPrintSupport/QPrinter"
#include <QPropertyAnimation>
#include<QTextDocument>
#include <QDesktopServices>
#include <QUrl>
#include <QTcpSocket>

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
    QRegExp espace("^[a-zA-Z]+( [a-zA-Z]+)*$");
    QRegExpValidator *val =new QRegExpValidator(exp,this);
    QRegExpValidator *valesp =new QRegExpValidator(espace,this);
            ui->nom->setValidator(val);
            ui->prenom->setValidator(valesp);
            ui->role->setValidator(val);
            ui->adresse->setValidator(val);
            ui->nationalite->setValidator(val);

        QRegExp expEmail("\\b[a-zA-Z0-9.%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,4}\\b");
        QRegExpValidator *valEmail =new QRegExpValidator(expEmail,this);
        ui->email->setValidator(valEmail);

        qDebug()
                    << QSslSocket::supportsSsl() // doit retourner true
                    << QSslSocket::sslLibraryBuildVersionString() // la version utilise pour compiler Qt
                    << QSslSocket::sslLibraryVersionString(); // la version disponible

        //CHAT//
        mSocket=new QTcpSocket(this);
        connect(mSocket, &QTcpSocket::readyRead, [&]() {
           QTextStream T(mSocket);
           auto text = T.readAll();
           ui->textEdit_chat->append(text);
        });



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
 QString adresse=ui->adresse->currentText();
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
        QString adresse=ui->adresse_maj->currentText();
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



/*void MainWindow::on_recherche_button_clicked()
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
}*/
void MainWindow::on_barre_recherche_textChanged(const QString &arg1)
{
    Employe e;
    ui->tab_employe->setModel( e.recherche(arg1));
}
void MainWindow::on_annuler_clicked()
{
    ui->id_box->clear();
    ui->cin_maj->clear();
    ui->nom_maj->clear();
    ui->prenom_maj->clear();
    ui->role_maj->clear();
    ui->nationalite_maj->clear();
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
           ui->sexe_maj->setCurrentText(query.value(7).toString());
           ui->nationalite_maj->setText(query.value(8).toString());
           ui->adresse_maj->setCurrentText(query.value(9).toString());

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

void MainWindow::on_tri_button_asc_clicked()
{
    Employe E;
        QString choix=ui->tri_comboBox->currentText();
        if (choix=="par nom")
        {
            ui->tab_employe->setModel(E.trie_nom_asc());
            ui->tab_employe->setModel(E.afficher());
            bool test=E.trie_nom_asc();
            if (test)
            {

                ui->tab_employe->setModel(E.trie_nom_asc());
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
            ui->tab_employe->setModel(E.trie_adr_asc());
            ui->tab_employe->setModel(E.afficher());
            bool test=E.trie_adr_asc();
            if (test)
            {

                ui->tab_employe->setModel(E.trie_adr_asc());
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
            ui->tab_employe->setModel(E.trie_cin_asc());
            ui->tab_employe->setModel(E.afficher());
            bool test=E.trie_cin_asc();
            if (test)
            {

                ui->tab_employe->setModel(E.trie_cin_asc());
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
            ui->tab_employe->setModel(E.trie_nationalite_asc());
            ui->tab_employe->setModel(E.afficher());
            bool test=E.trie_nationalite_asc();
            if (test)
            {

                ui->tab_employe->setModel(E.trie_nationalite_asc());
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
            ui->tab_employe->setModel(E.trie_prenom_asc());
            ui->tab_employe->setModel(E.afficher());
            bool test=E.trie_prenom_asc();
            if (test)
            {

                ui->tab_employe->setModel(E.trie_prenom_asc());
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

void MainWindow::on_tri_button_desc_clicked()
{
    Employe E;
        QString choix=ui->tri_comboBox->currentText();
        if (choix=="par nom")
        {
            ui->tab_employe->setModel(E.trie_nom_desc());
            ui->tab_employe->setModel(E.afficher());
            bool test=E.trie_nom_desc();
            if (test)
            {

                ui->tab_employe->setModel(E.trie_nom_desc());
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
            ui->tab_employe->setModel(E.trie_adr_desc());
            ui->tab_employe->setModel(E.afficher());
            bool test=E.trie_adr_desc();
            if (test)
            {

                ui->tab_employe->setModel(E.trie_adr_desc());
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
            ui->tab_employe->setModel(E.trie_cin_desc());
            ui->tab_employe->setModel(E.afficher());
            bool test=E.trie_cin_desc();
            if (test)
            {

                ui->tab_employe->setModel(E.trie_cin_desc());
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
            ui->tab_employe->setModel(E.trie_nationalite_desc());
            ui->tab_employe->setModel(E.afficher());
            bool test=E.trie_nationalite_desc();
            if (test)
            {

                ui->tab_employe->setModel(E.trie_nationalite_desc());
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
            ui->tab_employe->setModel(E.trie_prenom_desc());
            ui->tab_employe->setModel(E.afficher());
            bool test=E.trie_prenom_desc();
            if (test)
            {

                ui->tab_employe->setModel(E.trie_prenom_desc());
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


void MainWindow::on_imprimer_button_clicked()
{
    /*QString strStream;
        QTextStream out(&strStream);

        const int rowCount = ui->tab_employe->model()->rowCount();
        const int columnCount = ui->tab_employe->model()->columnCount();
        QString TT = QDateTime::currentDateTime().toString();
        out <<"<html>\n"
              "<head>\n"
               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            << "<title>ERP - liste des employes - <title>\n "
            << "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"
            "<h1 style=\"text-align: center;\"><strong> ******LISTE DES  EMPLOYES ******"+TT+" </strong></h1>"
               +"<img src=C://Users//Islem//Documents//Employee//img//logo sprint />"
            "<table style=\"width:100px; text-align: center; font-size: 20px;\" border=1>\n "
              "</br> </br>";
        // headers
        out << "<thead><tr bgcolor=#d6e5ff>";
        for (int column = 0; column < columnCount; column++)
            if (!ui->tab_employe->isColumnHidden(column))
                out << QString("<th>%1</th>").arg(ui->tab_employe->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++) {
            out << "<tr>";
            for (int column = 0; column < columnCount; column++) {
                if (!ui->tab_employe->isColumnHidden(column)) {
                    QString data =ui->tab_employe->model()->data(ui->tab_employe->model()->index(row, column)).toString().simplified();
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

        QPrinter printer;

        QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
        if (dialog->exec() == QDialog::Accepted) {
            document->print(&printer);
        }

        delete document;*/
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




void MainWindow::on_statistiques_widget_tabBarClicked(int index)
{
 e.statistique(ui->widget);
}


void MainWindow::on_statistiques_widget_currentChanged(int index)
{
e.statistique(ui->widget);
}


void MainWindow::on_mdp_oublie_clicked()
{
  login l;
  l.exec();
  ui->tab_employe->setModel(e.afficher());
}



void MainWindow::on_pb_envoyer_clicked()
{
 QTextStream T(mSocket);
 T << ui->le_nickname->text() << ":" << ui->le_message->text();
 mSocket->flush();
 ui->le_message->clear();
}


void MainWindow::on_pb_connecter_clicked()
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
        ui->etat_porte->setText("Ouvert");
       query.prepare("select * from employee where carte_id like '"+serialBuffer+"%'");

       if(query.exec())
       {
           while(query.next())
           {
              ui->cin_arduino->setText(query.value(0).toString());
              ui->nom_arduino->setText(query.value(1).toString());
              ui->prenom_arduino->setText(query.value(2).toString());
              ui->tel_arduino->setText(query.value(3).toString());
              ui->sexe_arduino->setCurrentText(query.value(7).toString());
              ui->adresse_arduino->setCurrentText(query.value(9).toString());

           }
       }
       //A.write_to_arduino(ui->prenom_arduino->text());

     }
   else if (data=="0" || data=="3")
         {
        ui->etat_porte->setText("Fermée");  // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher fermee

        ui->cin_arduino->clear();
        ui->nom_arduino->clear();
        ui->prenom_arduino->clear();
        ui->tel_arduino->clear();




    }
   else{
      ui->etat_porte->setText("Ouvert");
      ui->cin_arduino->clear();
      ui->nom_arduino->clear();
      ui->prenom_arduino->clear();
      ui->tel_arduino->clear();

    }
}


void MainWindow::on_open_door_arduino_2_clicked()
{
    A.write_to_arduino("2");
}


void MainWindow::on_close_door_arduino_clicked()
{
   A.write_to_arduino("3");
}

