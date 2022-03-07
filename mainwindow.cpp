#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "factures.h"
#include "commande.h"
#include <iostream>
#include <QMessageBox>
#include <QString>
#include <QIntValidator>
#include <QTableWidgetItem>
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
}

void MainWindow::on_pb_ajouter_clicked()
{
    if(ui->montantS->text().toFloat()>10)
    {
    int id_facture=ui->idS->text().toInt();
    float montant=ui->montantS->text().toFloat();
    QString mode_paiement=ui->modeS->currentText();
    QDate date_facture=ui->dateS->date();

    factures f(id_facture, montant, mode_paiement, date_facture);
    bool test=f.ajouter();


    if(test)
     {
      QMessageBox::information(nullptr, QObject::tr("OK"),
      QObject::tr("Ajout effectué.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_facture->setModel(ftmp.afficher());
     }
      else
      {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
       QObject::tr("Ajout non effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);
      }
    }
    else
    {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
     QObject::tr("Montant doit etre superieur à 10.\n"
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
    if(index.column()==0)
    {
        ftmp.test(val);
        QString i_d= QString::number(ftmp.getMontant());
        ui->montantS_2->setText(i_d);
        ui->modeS_2->setCurrentText(ftmp.getMode_paiement());
        ui->dateS_2->setDate(ftmp.getDate_facture());
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
    QDate date_facture=ui->dateS_2->date();

    factures f(id_facture, montant, mode_paiement, date_facture);
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

    commandes c(id_commande, quantite);
    bool test=c.ajouter();

    if(test)
     {
      QMessageBox::information(nullptr, QObject::tr("OK"),
      QObject::tr("Ajout effectué.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_facture_2->setModel(ctmp.afficher());
     }
      else
      {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
       QObject::tr("Ajout non effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);
      }
    }
    else
    {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
     QObject::tr("Montant doit etre superieur à 10.\n"
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


    commandes c(id_commande, quantite);
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
