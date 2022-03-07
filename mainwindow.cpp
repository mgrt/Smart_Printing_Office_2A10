#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_client->setModel(Etmp.afficher_client());
    ui->tab_client->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->idmodifc->setModel(Etmp.afficher_client());
    ui->idmodifc->setCurrentIndex(-1);
    ui->genre->setCurrentIndex(-1);
    ui->genre_2->setCurrentIndex(-1);
    ui->num_telephone->setValidator(new QIntValidator(0,99999999, this));
    ui->num_telephone_2->setValidator(new QIntValidator(0,99999999, this));
    ui->cin->setValidator(new QIntValidator(0,99999999, this));
    ui->cin_2->setValidator(new QIntValidator(0,99999999, this));
    QRegExp rxEmail("\\b[a-zA-Z0-9._%+-]+@[esprit]+\\.[tn]{2}\\b");
    QRegExpValidator *valiEmail =new QRegExpValidator(rxEmail,this);
    ui->email->setValidator(valiEmail);
    ui->email_2->setValidator(valiEmail);
    QRegExp rxnom("\\b[a-zA-Z]{2,20}\\b");
    QRegExpValidator *valinom =new QRegExpValidator(rxnom,this);
    ui->nom->setValidator(valinom);
    ui->nom_2->setValidator(valinom);
    ui->prenom->setValidator(valinom);
    ui->prenom_2->setValidator(valinom);


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::warning()
{
    QMessageBox::warning(this,"ERREUR!!!!!" ,"Erreur lors de Connection à la base de donnée");
}



void MainWindow::on_pb_ajouter_clicked()
{
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString email=ui->email->text();
    QString genre=ui->genre->currentText();
    QDate date = ui->date_naissance->date();
    int cin  = ui->cin->text().toUInt();
    QString nationalite=ui->nationalite->text();
    int num_telephone = ui->num_telephone->text().toUInt();


    Clients c(0,nom,prenom,genre,num_telephone,email,cin,date,nationalite);
    bool test= c.ajouter_client();

    if(test)
    {
        ui->tab_client->setModel(Etmp.afficher_client());
        ui->idmodifc->setModel(Etmp.afficher_client());
        QMessageBox::information(nullptr,"Ajout","client ajouté !!");
}
    else
    {
        QMessageBox::warning(nullptr,"Ajout","Probleme d'ajout !!!");
}
}

void MainWindow::on_pb_supprimer_clicked()
{
    QModelIndex ligne ;
            QItemSelectionModel* selectionModel = ui->tab_client->selectionModel();
               QModelIndexList selected = selectionModel->selectedRows();

                for(int i= 0; i< selected.count();i++)
               {
                      ligne = selected.at(i);
               }

                int id= ui->tab_client->model()->data(ligne).toInt();
                 QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "confirmation", "voulez vous  vraiment supprimer ?");

                if (reply == QMessageBox::Yes)
                {
                   bool test=Etmp.supprimer_client(id);
                   ui->tab_client->setModel(Etmp.afficher_client());
                   if(test)
                   {

                       QMessageBox::information(nullptr,"supp","client supprimé !!");
                     }
                   else
                   {
                       QMessageBox::warning(nullptr,"supp","probleme suppression !!");
               }

                }
}

void MainWindow::on_idmodifc_currentTextChanged(const QString &arg1)
{
    int id=arg1.toInt();
    QString nom,prenom,genre,num,email,cin,nationalite;
    QDate date;
    Etmp.recuperer_client(id,nom,prenom,genre,num,email,cin,date,nationalite);
    ui->nom_2->setText(nom);
    ui->prenom_2->setText(prenom);
    ui->cin_2->setText(cin);
    ui->num_telephone_2->setText(num);
    ui->email_2->setText(email);
    ui->nationalite_2->setText(nationalite);
    ui->date_naissance_2->setDate(date);
    ui->genre_2->setCurrentText( genre );

}

void MainWindow::on_pb_miseajour_clicked()
{
    QModelIndex ligne ;
            QItemSelectionModel* selectionModel = ui->tab_client->selectionModel();
               QModelIndexList selected = selectionModel->selectedRows();

                for(int i= 0; i< selected.count();i++)
               {
                      ligne = selected.at(i);
               }

                QString id= ui->tab_client->model()->data(ligne).toString();

                ui->idmodifc->setCurrentText( id );

                on_idmodifc_currentTextChanged(id);

                ui->tabWidget->setCurrentWidget(ui->tab);
}



void MainWindow::on_pb_modifier_2_clicked()
{

    QString nom=ui->nom_2->text();
    QString prenom=ui->prenom_2->text();
    QString email=ui->email_2->text();
    QString genre=ui->genre_2->currentText();
    QDate date = ui->date_naissance_2->date();
    int cin  = ui->cin_2->text().toUInt();
    QString nationalite=ui->nationalite_2->text();
    int num_telephone = ui->num_telephone_2->text().toUInt();
    int id=ui->idmodifc->currentText().toUInt();


    Clients c(0,nom,prenom,genre,num_telephone,email,cin,date,nationalite);


                 QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "confirmation", "voulez vous  vraiment modifier ?");

                if (reply == QMessageBox::Yes)
                {
                   bool test=c.modifier_client(id);
                   ui->tab_client->setModel(Etmp.afficher_client());
                   if(test)
                   {

                       QMessageBox::information(nullptr,"modification","client modifié !!");
                     }
                   else
                   {
                       QMessageBox::warning(nullptr,"modification","probleme de modification !!");
               }

                }
}

void MainWindow::on_pb_recherche_clicked()
{
      QString rech=ui->barre_recherche->text();

      ui->tab_client->setModel(Etmp.rechercher(rech));

}



void MainWindow::on_pb_annuler_clicked()
{
    ui->tab_client->setModel(Etmp.afficher_client());
}
