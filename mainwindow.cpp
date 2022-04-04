#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "factures.h"
#include "commande.h"
#include "connection.h"
#include <iostream>
#include <QMessageBox>
#include <QString>
#include <QIntValidator>
#include <QTableWidgetItem>
#include <QPixmap>
#include <QtPrintSupport/QPrintDialog>
#include<QtPrintSupport/QPrinter>
#include<QPropertyAnimation>
#include <QtPrintSupport/QPrinter>
#include<QPdfWriter>
#include <QMediaPlayer>
#include <QList>
#include <QtCharts>

using namespace QtCharts;

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    //ui->tab_facture->setModel(ftmp.afficher());
    connect(this,SIGNAL(aa()),this,SLOT(afficher()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::afficher()
{
    ui->setupUi(this);
    ui->tab_facture->setModel(ftmp.afficher());
    ui->tab_facture_2->setModel(ctmp.afficher());
    ui->idS_3->setVisible(false);
    ui->idS_5->setVisible(false);
    ui->idS->setText("dd");
    ui->idS->setReadOnly(1);

    ui->tab_commande->setVisible(0);
            ui->pushButton->setVisible(0);
            ui->label_10->setVisible(0);
            ui->label_9->setVisible(0);
            ui->label_2->setVisible(0);
            ui->comboBox->setVisible(0);
            ui->montantS_3->setVisible(0);
            ui->montantS->setVisible(0);
            ui->prixProduitQuantite->setVisible(0);
            ui->prixProduit->setVisible(0);
            ui->pb_ajouter_2->setVisible(0);

    //ui->idS->setVisible(false);
    QSqlQuery q ;
    q.prepare("select concat(nom, concat(' ', prenom)) from employee where role like 'responsable financier'");
    q.exec();
    if(q.next())
    {
        QString nomempl=q.value(0).toString();
        ui->nomEmp->setText(nomempl);
        ui->nomEmp->setReadOnly(1);
    }

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit->setReadOnly(1);

    QPixmap image(":/resources/img/labrador.jpg");
    int w=ui->label_image->width();
    int h=ui->label_image->height();
    ui->label_image->setPixmap(image.scaled(w,h, Qt::KeepAspectRatio));

    QPixmap logo(":/resources/img/logo sprint.png");
    int wl=ui->label_logo->width();
    int hl=ui->label_logo->height();
    ui->label_logo->setPixmap(logo.scaled(wl,hl, Qt::KeepAspectRatio));

    QPixmap nuitjour(":/resources/img/Mode-nuit-featured.png");
    int wn=ui->label_nuitjour->width();
    int hn=ui->label_nuitjour->height();
    ui->label_nuitjour->setPixmap(nuitjour.scaled(wn,hn, Qt::KeepAspectRatio));

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
              ui->label_10->setVisible(1);
              ui->label_9->setVisible(1);
              ui->label_2->setVisible(1);
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
void MainWindow::on_pushButton_clicked()
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
    qry->prepare("select concat(nom, concat(' ', prenom)) from employee where role like 'responsable financier' ");
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
    ui->label_10->setVisible(0);
    ui->label_9->setVisible(0);
    ui->label_2->setVisible(0);
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
   /* QPrinter printer;
    QPrintDialog *printDialog = new QPrintDialog(&printer, this);
    printDialog->setWindowTitle("Imprimer Document");
    printDialog->exec();*/
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
                        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
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
    ui->pb_journuit->setStyleSheet("background-color: rgb(128, 128, 128)");
    ui->tabWidget->setStyleSheet("background-color: rgb(128, 128, 128)");


            //styleSheet(background-color: rgb(113, 205, 220))/*setBackgroundRole(QPalette::Dark)*/;
}/*
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

void MainWindow::on_pbimp_2_clicked()
{
    QTableView *table;
              table = ui->tab_facture;

              QString filters("csv files (.xlsx);;All files (.*)");
              QString defaultFilter("All files ("".*)");
              QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                 filters, &defaultFilter);
              QFile file(fileName);

              QAbstractItemModel *model =  table->model();
              if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                  QTextStream data(&file);
                  QStringList strList;
                  for (int i = 0; i < model->columnCount(); i++) {
                      if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                          strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                      else
                          strList.append("");
                  }
                  data << strList.join(";") << "\n";
                  for (int i = 0; i < model->rowCount(); i++) {
                      strList.clear();
                      for (int j = 0; j < model->columnCount(); j++) {

                          if (model->data(model->index(i, j)).toString().length() > 0)
                              strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                          else
                              strList.append("");
                      }
                      data << strList.join(";") + "\n";
                  }
                  file.close();
                  QMessageBox::information(this,"Exporter To Excel","Exporté avec succées ");
              }

}



void MainWindow::on_pbimp_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open File",QString(),"PDF File(*.pdf)");
        QPrinter printer;
        QPrintDialog *dlg = new QPrintDialog(&printer,0);

        if(dlg->exec() == QDialog::Accepted)
        {
            QImage pdf(fileName);
            QPainter painter(&printer);
            painter.drawImage(QPoint(0,0),pdf);
            painter.end();
        }

        delete dlg;
}
