#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "machine.h"
#include "maintenance.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

        ui->setupUi(this);

        update_output_data();
        controle_de_saisie();
        ui->affichage_maintenance->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->affichage_maintenance->verticalHeader()->hide();
        ui->affichage_machine->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->affichage_machine->verticalHeader()->hide();
        ui->annuler->setStyleSheet("border-image:url(C:/Users/fedi1/Documents/Gestion_de_maintenance/Croix_Mundolsheim.png);");
}

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

    ui->affichage_maintenance->setModel( M.afficher() );
    ui->affichage_machine->setModel( MM.afficher() );
    ui->ID_machine_ajout->setModel( MM.afficher_nom() );
    ui->id_maintenance_modif->setModel( M.afficher() );
    ui->id_machine_affchage_3->setModel( MM.afficher_nom() );
    ui->id_machine_modif->setModel(MM.afficher_nom());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_triggered()
{
    QApplication::quit();
}

///////////////////////////////////////////////////////////////////////////////////
//les bouttons du tableau de bord


void MainWindow::on_pushButton_4_clicked()
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





void MainWindow::initialisation_demarage()
{
    on_pushButton_7_clicked();
    on_pushButton_9_clicked();
            on_pushButton_21_clicked();
            on_pushButton_20_clicked();
    ui->tabWidget->setCurrentWidget(ui->tab_1);

}

void MainWindow::on_pushButton_clicked()
{
    if(ui->description_machine_ajout->toPlainText().isEmpty() || ui->ID_machine_ajout->currentText().isEmpty() )
    {
        QMessageBox::warning(this,"ATTENTION!!!" , "Veuillez remplir toutes les cases !");
    }
    else {
        if (ui->description_machine_ajout->toPlainText().length() > 100)
        {
            QMessageBox::critical(this,
                                  "Error",
                                  "Veuiller saisir au maximaum 100 charactères!! ");
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



void MainWindow::on_pushButton_9_clicked()
{
    ui->nom_ajout_machine->setText("");
}




void MainWindow::on_pushButton_3_clicked()
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



void MainWindow::on_pushButton_5_clicked()
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



void MainWindow::on_pushButton_10_clicked()
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
        if (ui->desc_modif->toPlainText().length() > 100 )
                {
                    QMessageBox::critical(this,
                                          "Error",
                                          "Veuiller saisir au maximaum 100 charactères!! ");
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
   ui->affichage_maintenance->setModel( M.afficher() );
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
