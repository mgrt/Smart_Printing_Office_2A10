#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPieSlice>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    update();
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
void MainWindow::update()
{
    ui->tab_client->setModel(Etmp.afficher_client());
    ui->tab_client->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_client_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->idmodifc->setModel(Etmp.afficher_client());
    ui->client->setModel(Etmp.afficher_client());
    ui->client_2->setModel(Etmp.afficher_client());
    ui->id_rec->setModel(rec.afficher_reclamation());
    ui->facture->setModel(rec.afficher_facture());
    ui->facture_2->setModel(rec.afficher_facture());
    ui->employe->setModel(rec.afficher_employe());
    ui->employe_2->setModel(rec.afficher_employe());
    ui->idmodifc->setCurrentIndex(-1);
    ui->genre->setCurrentIndex(-1);
    ui->genre_2->setCurrentIndex(-1);
    ui->tab_client_2->setModel(rec.afficher_reclamation());
    ui->comboBox->setCurrentIndex(1);


    }
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::warning()
{
    QMessageBox::warning(this,tr("ERREUR!!!!!") ,tr("Erreur lors de Connection à la base de donnée"));
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
      update();
        QMessageBox::information(nullptr,tr("Ajout"),tr("client ajouté !!"));
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
                reply = QMessageBox::question(this, tr("confirmation"), tr("voulez vous  vraiment supprimer ?"));

                if (reply == QMessageBox::Yes)
                {
                   bool test=Etmp.supprimer_client(id);
                  update();
                   if(test)
                   {

                       QMessageBox::information(nullptr,tr("supp"),tr("client supprimé !!"));
                     }
                   else
                   {
                       QMessageBox::warning(nullptr,tr("supp"),tr("probleme suppression !!"));
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
                reply = QMessageBox::question(this, tr("confirmation"), tr("voulez vous  vraiment modifier ?"));

                if (reply == QMessageBox::Yes)
                {
                   bool test=c.modifier_client(id);
                   update();
                   if(test)
                   {

                       QMessageBox::information(nullptr,tr("modification"),tr("client modifié !!"));
                     }
                   else
                   {
                       QMessageBox::warning(nullptr,tr("modification"),tr("probleme de modification !!"));
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

void MainWindow::on_pb_trier_id_clicked()
{
    QString trie="id_client";
    QString ordre="ASC";
     ui->tab_client->setModel(Etmp.trier(trie,ordre));

}

void MainWindow::on_pb_trier_nom_clicked()
{
    QString trie="nom_client";
    QString ordre="ASC";
     ui->tab_client->setModel(Etmp.trier(trie,ordre));
}

void MainWindow::on_pb_trier_prenom_clicked()
{
    QString trie="prenom_client";
    QString ordre="ASC";
     ui->tab_client->setModel(Etmp.trier(trie,ordre));
}

void MainWindow::on_pb_trier_date_clicked()
{
    QString trie="date_naissance_client";
    QString ordre="ASC";
     ui->tab_client->setModel(Etmp.trier(trie,ordre));
}

void MainWindow::on_pb_trier_id_2_clicked()
{
    QString trie="id_client";
    QString ordre="DESC";
     ui->tab_client->setModel(Etmp.trier(trie,ordre));
}

void MainWindow::on_pb_trier_nom_2_clicked()
{
    QString trie="nom_client";
    QString ordre="DESC";
     ui->tab_client->setModel(Etmp.trier(trie,ordre));
}

void MainWindow::on_pb_trier_prenom_2_clicked()
{
    QString trie="prenom_client";
    QString ordre="DESC";
     ui->tab_client->setModel(Etmp.trier(trie,ordre));
}

void MainWindow::on_pb_trier_date_2_clicked()
{
    QString trie="date_naissance_client";
    QString ordre="DESC";
     ui->tab_client->setModel(Etmp.trier(trie,ordre));
}

void MainWindow::on_pb_PDF_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

                           const int rowCount = ui->tab_client->model()->rowCount();
                           const int columnCount = ui->tab_client->model()->columnCount();
                          out <<  "<html>\n"
                          "<head>\n"
                                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                           <<  QString("<title>%1</title>\n").arg("strTitle")
                                           <<  "</head>\n"
                                           "<body bgcolor=#ffffff link=#5000A0>\n"

                                          //     "<align='right'> " << datefich << "</align>"
                                           "<center> <H1>Liste des Clients</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                       // headers
                                       out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                       out<<"<cellspacing=10 cellpadding=3>";
                                       for (int column = 0; column < columnCount; column++)
                                           if (!ui->tab_client->isColumnHidden(column))
                                               out << QString("<th>%1</th>").arg(ui->tab_client->model()->headerData(column, Qt::Horizontal).toString());
                                       out << "</tr></thead>\n";

                                       // data table
                                       for (int row = 0; row < rowCount; row++) {
                                           out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                           for (int column = 0; column < columnCount; column++) {
                                               if (!ui->tab_client->isColumnHidden(column)) {
                                                   QString data = ui->tab_client->model()->data(ui->tab_client->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_pb_stat_genre_clicked()
{

    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from Clients where genre_client ='Homme'");
    float age2040=model->rowCount();
    model->setQuery("select * from Clients where genre_client ='Femme' ");
    float age0020=model->rowCount();
    float total=age2040+age0020;
    QString a=QString("Homme : "+QString::number((age2040*100)/total,'f',2)+"%" );
    QString b=QString("Femme :  "+QString::number((age0020*100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,age2040);
    series->append(b,age0020);
    if (age2040!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( age0020!=0)
    {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
    }

    QChart *chart = new QChart();
    // Add data to chart with title and hide legend
    chart->addSeries(series);
    chart->setTitle("proportions du genre des clients  ");
    chart->legend()->hide();
    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();
}

void MainWindow::on_pb_stat_age_clicked()
{
      // QString datemtn="select sysdate from dual";
      // QString datenaiss="select date_naissance_client from Clients";
       //QString age="SELECT FLOOR(DATEDIFF(DAY,sysdate, date_naissance_client) / 365.25) from Clients, dual";
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from Clients where extract(year from date_naissance_client)<'2002' and extract(year from date_naissance_client)>'1982' ");
    float age2040=model->rowCount();
    model->setQuery("select * from Clients where extract(year from date_naissance_client)>='2002' ");
    float age0020=model->rowCount();
    model->setQuery("select * from Clients where extract(year from date_naissance_client)<='1982' ");
    float age40=model->rowCount();
    float total=age2040+age0020+age40;
    QString a=QString("entre 20 et 40 : "+QString::number((age2040*100)/total,'f',2)+"%" );
    QString b=QString("Moins que 20 :  "+QString::number((age0020*100)/total,'f',2)+"%" );
    QString c=QString("Plus que 40 :  "+QString::number((age40*100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,age2040);
    series->append(b,age0020);
    series->append(c,age40);
    if (age2040!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( age0020!=0)
    {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
    }
    if ( age40!=0)
    {
        QPieSlice *slice2 = series->slices().at(2);
        slice2->setLabelVisible();
    }

    QChart *chart = new QChart();
    // Add data to chart with title and hide legend
    chart->addSeries(series);
    chart->setTitle("proportions de l'age des clients  ");
    chart->legend()->hide();
    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();
}

void MainWindow::on_pb_ajouter_2_clicked()
{
    int client=ui->client->currentText().toInt();
    int facture=ui->facture->currentText().toInt();
    int employe=ui->employe->currentText().toInt();


    QString reclamation=ui->reclamation->toPlainText();



    reclamations r(0,client,facture,employe,reclamation);
    bool test= r.ajouter_reclamation();

    if(test)
    {
        //ui->tab_4->setModel(rec.afficher_reclamation());
        //ui->idmodifc->setModel(rec.afficher_reclamation());
        update();
        QMessageBox::information(nullptr,tr("Ajout"),tr("reclamation ajoutée !!"));
}
    else
    {
        QMessageBox::warning(nullptr,tr("Ajout"),tr("Probleme d'ajout !!!"));
}
}

void MainWindow::on_pb_miseajour_2_clicked()
{
    QModelIndex ligne ;
            QItemSelectionModel* selectionModel = ui->tab_client_2->selectionModel();
               QModelIndexList selected = selectionModel->selectedRows();

                for(int i= 0; i< selected.count();i++)
               {
                      ligne = selected.at(i);
               }

                QString id= ui->tab_client_2->model()->data(ligne).toString();

                ui->id_rec->setCurrentText( id );

                on_id_rec_currentTextChanged(id);

                ui->tabWidget->setCurrentWidget(ui->tab_5);
}

void MainWindow::on_id_rec_currentTextChanged(const QString &arg1)
{
    int client,facture,employe,id=arg1.toInt();
    QString reclamation;
    rec.recuperer_reclamation(id,client,facture,employe,reclamation);
    QString c = QString::number(client);
    QString e = QString::number(employe);
    QString f = QString::number(facture);
    ui->client_2->setCurrentText(c);
    ui->employe_2->setCurrentText(e);
    ui->facture_2->setCurrentText(f);
    ui->reclamation_2->setText(reclamation);

}

void MainWindow::on_pb_supprimer_2_clicked()
{
    QModelIndex ligne ;
            QItemSelectionModel* selectionModel = ui->tab_client_2->selectionModel();
               QModelIndexList selected = selectionModel->selectedRows();

                for(int i= 0; i< selected.count();i++)
               {
                      ligne = selected.at(i);
               }

                int id= ui->tab_client_2->model()->data(ligne).toInt();
                 QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, tr("confirmation"), tr("voulez vous  vraiment supprimer ?"));

                if (reply == QMessageBox::Yes)
                {
                   bool test=rec.supprimer_reclamation(id);
                  update();
                   if(test)
                   {

                       QMessageBox::information(nullptr,tr("supp"),tr("reclamation supprimé !!"));
                     }
                   else
                   {
                       QMessageBox::warning(nullptr,tr("supp"),tr("probleme suppression !!"));
               }

                }
}

void MainWindow::on_pb_modifier_3_clicked()
{
    int id1=ui->id_rec->currentText().toUInt();
    int client1=ui->client_2->currentText().toInt();
    int employe1=ui->employe_2->currentText().toInt();
    int facture1=ui->facture_2->currentText().toInt();
    QString reclamation1=ui->reclamation_2->toPlainText();



    reclamations r (0,client1,facture1,employe1,reclamation1);

                 QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, tr("confirmation"), tr("voulez vous  vraiment modifier ?"));

                if (reply == QMessageBox::Yes)
                {
                   bool test=r.modifier_reclamation(id1);

                   if(test)
                   { update();

                       QMessageBox::information(nullptr,tr("modification"),tr("reclamation modifié !!"));
                     }
                   else
                   {
                       QMessageBox::warning(nullptr,tr("modification"),tr("probleme de modification !!"));
                    }

                }
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1=="English")
    {
        ui->tabWidget->setTabText(0,"add customer");
        ui->tabWidget->setTabText(1,"show customers");
        ui->tabWidget->setTabText(2,"Modify customer");
        ui->tabWidget->setTabText(3,"add complaint");
        ui->tabWidget->setTabText(4,"show complaint");
        ui->tabWidget->setTabText(5,"Modify complaint");



        ui->label->setText("CIN");
        ui->label_2->setText("Name");
        ui->label_3->setText("First Name");
        ui->label_4->setText("Phone number");
        ui->label_5->setText("Date of birth");
        ui->label_6->setText("Nationality");
        ui->label_8->setText("Gender");
        ui->label_10->setText("E-mail");
        ui->label_12->setText("Enter new customer information ");
        ui->pb_ajouter->setText("Add Customer");
        ui->pushButton_4->setText("customer management");

        ui->pb_recherche->setText("search");
        ui->pb_annuler->setText("Cancel");
        ui->label_15->setText("sort by id");
        ui->label_25->setText("sort by name");
        ui->label_26->setText("sort by first name");
        ui->label_27->setText("Sort by date");
        ui->label_14->setText("customer list");
        ui->pb_miseajour->setText("update customer");
        ui->pb_supprimer->setText("delete customer");
        ui->pb_stat_age->setText("age stats");
        ui->pb_stat_genre->setText("gender stats");
        ui->label_24->setText("update customer");
        ui->label_23->setText("id_customer");
        ui->label_7->setText("name");
        ui->label_9->setText("first name");
        ui->label_11->setText("gender");
        ui->label_19->setText("E-mail");
        ui->label_21->setText("CIN");
        ui->label_22->setText("Nationality");
        ui->label_20->setText("Date of birth");
        ui->label_13->setText("Phone number");
        ui->pb_modifier_2->setText("update customer");
        ui->label_28->setText("add the information of the new complaint");
        ui->label_29->setText("id customer");
        ui->label_30->setText("id invoice");
        ui->label_31->setText("id employee");
        ui->label_32->setText("complaint");
        ui->pb_ajouter_2->setText("Add complaint");
        ui->label_33->setText("complaints list");
        ui->pb_miseajour_2->setText("update complaint");
        ui->pb_supprimer_2->setText("delete complaint");
        ui->label_38->setText("complaint id");
        ui->label_34->setText("id customer");
        ui->label_36->setText("id invoice");
        ui->label_35->setText("id employee");
        ui->label_37->setText("complaint");
        ui->pb_modifier_3->setText("update complaint");




    }
    if(arg1=="French")
    {
        ui->tabWidget->setTabText(0,"ajouter client");
        ui->tabWidget->setTabText(1,"afficher clients");
        ui->tabWidget->setTabText(2,"Modifiier client");
        ui->tabWidget->setTabText(3,"Ajouter reclamation");
        ui->tabWidget->setTabText(4,"afficher reclamations");
        ui->tabWidget->setTabText(5,"Modifier reclamation");

        ui->label->setText("CIN");
               ui->label_2->setText("nom");
               ui->label_3->setText("prenom");
               ui->label_4->setText("num telephone");
               ui->label_5->setText("date de naissance");
               ui->label_6->setText("Nationalite");
               ui->label_8->setText("genre");
               ui->label_10->setText("E-mail");
               ui->label_12->setText("Entrer les informations du client ");
               ui->pb_ajouter->setText("ajouter client");
               ui->pushButton_4->setText("gestion client");

               ui->pb_recherche->setText("rechercher");
               ui->pb_annuler->setText("annuler");
               ui->label_15->setText("trier par id");
               ui->label_25->setText("trier par nom");
               ui->label_26->setText("trier par prenom");
               ui->label_27->setText("trier par date");
               ui->label_14->setText("liste des clients");
               ui->pb_miseajour->setText("modifier clier");
               ui->pb_supprimer->setText("supprimer client");
               ui->pb_stat_age->setText("age stats");
               ui->pb_stat_genre->setText("genre stats");
               ui->label_24->setText("modifier client");
               ui->label_23->setText("id client");
               ui->label_7->setText("nom");
               ui->label_9->setText("prenom");
               ui->label_11->setText("genre");
               ui->label_19->setText("E-mail");
               ui->label_21->setText("CIN");
               ui->label_22->setText("Nationalite");
               ui->label_20->setText("date de naissance");
               ui->label_13->setText("num telephone");
               ui->pb_modifier_2->setText("modifier client");
               ui->label_28->setText("ajouter information sur reclamation");
               ui->label_29->setText("id client");
               ui->label_30->setText("id facture");
               ui->label_31->setText("id employe");
               ui->label_32->setText("reclamation");
               ui->pb_ajouter_2->setText("ajouter reclamation");
               ui->label_33->setText("reclamation liste");
               ui->pb_miseajour_2->setText("modifier reclamation");
               ui->pb_supprimer_2->setText("supprimer reclamation");
               ui->label_38->setText("id reclamation");
               ui->label_34->setText("id client");
               ui->label_36->setText("id facture");
               ui->label_35->setText("id employe");
               ui->label_37->setText("reclamation");
               ui->pb_modifier_3->setText("modifier reclamation");



    }
    if(arg1=="Arabic")
    {
        ui->tabWidget->setTabText(0,"ادارة الزبائن");
        ui->tabWidget->setTabText(1,"عرض الزبائن");
        ui->tabWidget->setTabText(2,"تحرير الزبون");
        ui->tabWidget->setTabText(3,"أضف شكوى");
        ui->tabWidget->setTabText(4,"عرض الشكاوى");
        ui->tabWidget->setTabText(5,"تعديل الشكوى");

        ui->label->setText("رقم بطاقة الهوية");
               ui->label_2->setText("اسم");
               ui->label_3->setText("الاسم الأول");
               ui->label_4->setText("رقم الهاتف");
               ui->label_5->setText("تاريخ الميلاد");
               ui->label_6->setText("جنسية");
               ui->label_8->setText("الجنس");
               ui->label_10->setText("بريد الالكتروني");
               ui->label_12->setText("أدخل معلومات الزبون الجديد ");
               ui->pb_ajouter->setText("إضافة زبون");
               ui->pushButton_4->setText("ادارة الزبائن");

               ui->pb_recherche->setText("للبحث");
               ui->pb_annuler->setText("لالغاء");
               ui->label_15->setText("فرز حسب المعرف");
               ui->label_25->setText("الترتيب حسب الاسم");
               ui->label_26->setText("فرز حسب الاسم الأول");
               ui->label_27->setText("رتب حسب التاريخ");
               ui->label_14->setText("قائمة الزبائن");
               ui->pb_miseajour->setText("تحرير الزبون");
               ui->pb_supprimer->setText("حذف الزبون");
               ui->pb_stat_age->setText("احصائيات العمر");
               ui->pb_stat_genre->setText("احصائيات الجنس");
               ui->label_24->setText("تحرير الزبون");
               ui->label_23->setText("معرف الزبون");
               ui->label_7->setText("اسم");
               ui->label_9->setText("الاسم الأول");
               ui->label_11->setText("الجنس");
               ui->label_19->setText("بريد الالكتروني");
               ui->label_21->setText("رقم بطاقة الهوية");
               ui->label_22->setText("جنسية");
               ui->label_20->setText("تاريخ الميلاد");
               ui->label_13->setText("رقم الهاتف");
               ui->pb_modifier_2->setText("تحرير الزبون");
               ui->label_28->setText("أدخل معلومات شكوى جديدة");
               ui->label_29->setText("معرف الزبون");
               ui->label_30->setText("معرف الفاتورة");
               ui->label_31->setText("معرف الموظف");
               ui->label_32->setText("شكوى");
               ui->pb_ajouter_2->setText("أضف شكوى");
               ui->label_33->setText("قائمة الشكاوى");
               ui->pb_miseajour_2->setText("تعديل الشكوى");
               ui->pb_supprimer_2->setText("حذف الشكوى");
               ui->label_38->setText("معرف المطالبة");
               ui->label_34->setText("معرف الزبون");
               ui->label_36->setText("معرف الفاتورة");
               ui->label_35->setText("هوية الموظف");
               ui->label_37->setText("شكوى");
               ui->pb_modifier_3->setText("تعديل الشكوى");



    }
}
