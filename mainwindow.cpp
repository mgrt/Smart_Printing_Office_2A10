#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "stocks.h"
#include "categorie.h"
#include <qmessagebox.h>
#include <QDebug>
#include <QtPrintSupport/QPrintDialog>
#include<QtPrintSupport/QPrinter>
#include<QPropertyAnimation>

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
//#include <QPrinter>
//#include <QPrintDialog>

using namespace qrcodegen ;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    connect(this, SIGNAL(test()),this, SLOT(aff()));






}

MainWindow::~MainWindow()
{
    delete ui;

}
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

/*
    QSqlQuery query1("SELECT quantite FROM stocks");
            while(query1.next())
            {
                test.push_back(query.value(0).toString());
            }
*/



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

  /*
      QSqlQuery query1("SELECT quantite FROM stocks");
              while(query1.next())
              {
                  test.push_back(query.value(0).toString());
              }
  */




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

void MainWindow::on_pushButton_3_clicked()
{
    Stocks *Stock =new Stocks(ui->line_nom->text(),ui->line_idcat->currentText().toInt(),ui->line_prix->text().toInt(),ui->line_quant->text().toInt());
    QItemSelectionModel *selection = ui->tableView->selectionModel();
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

 }
