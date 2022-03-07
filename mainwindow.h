#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "factures.h"
#include "commande.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();
    void afficher();
    void on_pb_supprimer_clicked();

    void on_tab_facture_clicked(const QModelIndex &index);


    //void on_pb_miseajour_clicked();

    //void on_tab_facture_clicked(const QModelIndex &index);

    void on_pb_miseajour_clicked();

    void on_pb_ajouter_2_clicked();

    void on_pb_supprimer_2_clicked();

    void on_tab_facture_2_clicked(const QModelIndex &index);

    void on_pb_miseajour_2_clicked();

signals:
   void aa();

private:
    Ui::MainWindow *ui;
    factures ftmp;
    commandes ctmp;
};
#endif // MAINWINDOW_H
