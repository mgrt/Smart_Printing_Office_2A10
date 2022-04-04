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
    int *i;

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

    void on_pushButton_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_employe_clicked();

    void on_pushButton_client_clicked();

    void on_comboBox_currentIndexChanged(int index);


    void on_montantS_3_textChanged(const QString &arg1);


    void on_pb_terminer_clicked();

    void on_pb_tri_id_clicked();

    void on_barre_recherche_textChanged(const QString &arg1);

    void on_pbimp_clicked();

    void on_pushButton_client_2_clicked();

    void on_barre_recherche_2_textChanged(const QString &arg1);

    void on_pb_tri_quantite_clicked();

    void on_pb_journuit_clicked();
/*
    void creeraction();

    void paintevent(QPaintEvent *event);*/
    void on_pbimp_2_clicked();

    void on_pbimp_3_clicked();

signals:
   void aa();

private:
    Ui::MainWindow *ui;
    factures ftmp;
    commandes ctmp;
};
#endif // MAINWINDOW_H
