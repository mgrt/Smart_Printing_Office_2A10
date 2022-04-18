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

        ui->maps->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
        ui->maps->show();
        ui->papier->setVisible(false);
        ui->nom_papier_L->setVisible(false);
        ui->nom_produit->setVisible(false);
         ui->lcdNumber->setVisible(false);





        //////////////////////////////////////////////////////////////////////////////////////////
        /// arduio
        int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0) :qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(recup())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).
    /// ////////////////////////////////////////////////////////////////////////////////

}

MainWindow::~MainWindow()
{
    delete ui;
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

////////////////////////////////////
/// \brief MainWindow::on_pushButton_clicked
/// ajouter une maintenance
void MainWindow::on_pushButton_clicked()
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

////////////////
///  MainWindow::on_pushButton_5_clicked
///supprimer une machine

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



void MainWindow::on_comboBox_currentIndexChanged(int index)
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


void MainWindow::on_tabWidget_tabBarClicked(int index)
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
        A.serial_read(nbf) ;
        ui->papier->setVisible(true);
        ui->nom_papier_L->setVisible(true);
        ui->nom_produit->setVisible(true);
        ui->lcdNumber->setVisible(true);
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


void MainWindow::on_nom_produit_currentTextChanged(const QString &arg1)
{
    A.write_to_arduino("333");
     int poids;
     poids=M.poids(arg1);
     for(int i=0 ; i<=poids ; i++)
     {
         A.write_to_arduino("22");
     }

}

 void MainWindow::recup()
 {
     A.serial_read(nbf);
     ui->lcdNumber->display(nbf);
 }

