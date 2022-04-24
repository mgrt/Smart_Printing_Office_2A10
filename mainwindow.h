#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDialog>
#include <QSqlQueryModel>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QMessageBox>
#include <QVector>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
#include <QVector>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QSqlDatabase>
#include <QDebug>
#include <QUrl>
#include <QTcpServer>
#include<QTcpSocket>
#include "employe.h"
#include "stocks.h"
#include "arduino.h"
#include<QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "factures.h"
#include "commande.h"
//fedi

#include <QQuickView>
#include "maintenance.h"
#include "machine.h"
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QMainWindow>
#include "QMessageBox"
#include <QTabWidget>
#include <QSqlQueryModel>
#include<QDebug>
#include <QRegExpValidator>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QFileDialog>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include<QSslSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //|||||| fediiiiiiiiiiiiiiiiii
    void initialisation_demarage();
    void update_output_data();
    void warning ();
    void controle_de_saisie();
    void statistique();

private slots:

  void on_checkBox_25_clicked();
  void on_mdp_oublie_5_clicked();
  void on_retourner_6_clicked();
  void mailSent(QString status);
  void on_forgotNext_6_clicked();
  void on_loginForgot_6_clicked();
  void on_checkBox_27_clicked();
  void on_signUp_clicked();

  void on_retourner_signup_clicked();

  void on_connexion_5_clicked();

  void on_create_acount_10_clicked();

  void on_GClients_button_clicked();

  void on_GProduits_button_clicked();

  void on_GFactures_button_clicked();

  void on_GEmployes_button_clicked();

  void on_GMaintenances_button_clicked();

  void on_pb_ajouter_5_clicked();

  void on_pb_supprimer_5_clicked();

  void on_modifier_5_clicked();

  void on_barre_recherche_5_textChanged(const QString &arg1);

  void on_annuler_5_clicked();

  void on_supp_ajout_5_clicked();


  void on_id_box_5_currentIndexChanged(const QString &arg1);

  void on_tab_employe_5_activated(const QModelIndex &index);

  void on_tri_button_asc_5_clicked();

  void on_tri_button_desc_5_clicked();

  void on_imprimer_button_5_clicked();

  void on_tab_widget_employe_tabBarClicked(int index);

  void on_tab_widget_employe_currentChanged(int index);

  void on_pb_envoyer_5_clicked();

  void on_pb_connecter_5_clicked();
  void serial_read();
  void update_label();
  void on_open_door_arduino_6_clicked();
  void on_close_door_arduino_5_clicked();
  // ||||||||||||||||||||||||||||||||||||||-malek
  int rech(QString tab[],QCharRef c);
  int decod(int a,int b,int dec);
 void aff();

     void on_pushButton_clicked();

    void on_pushButton_2_clicked();

     void on_pushButton_Supprimer_clicked();

     void on_pushButton_3_clicked();

     void on_pushButton_4_clicked();

     void on_trinom_clicked();

     void on_pushButton_ref_clicked();

     void on_nomdec_clicked();

     void on_prix_clicked();

     void on_prixdec_clicked();

     void on_quant_clicked();

     void on_quantdec_clicked();

     void on_ok_clicked();

    // void on_pushButton_2_clicked();

     void on_pushButton_image_clicked();

     void on_Qrcode_2_clicked();

     void on_Ajoutercat_clicked();

     void on_tabWidget_tabBarClicked(int index);



     void on_Supprimercat_clicked();

     void on_Selectcat_clicked();

     void on_Modifiercat_clicked();

     void on_load_clicked();

     void on_pushButton_ref_2_clicked();



     void on_pushButton_plusdet_clicked();

     void on_pushButton_ref_3_clicked();



     void on_code_clicked();

     void on_dcode_clicked();

     void on_pushButton_ref_4_clicked();

     void on_Ajoutercat_2_clicked();

     void on_Ajoutercat_3_clicked();



     void on_code_2_clicked();



     void on_line_rech_returnPressed();



     void on_line_rech_textChanged(const QString &arg1);

     void on_pushButton_ref_5_clicked();




     void on_tri_currentIndexChanged(const QString &arg1);

     void on_pushButton_5_clicked();


     void on_pb_ajouter_6_clicked();



     void on_retour_accueil_clicked();
     // |||||||||||||||||||||||||||||||||||||||||||souhaaaaaaaaaa
     void on_pb_ajouter_clicked();
     void affich();
     void on_pb_supprimer_clicked();

     void on_tab_facture_clicked(const QModelIndex &index);


     //void on_pb_miseajour_clicked();

     //void on_tab_facture_clicked(const QModelIndex &index);

     void on_pb_miseajour_clicked();

     void on_pb_ajouter_2_clicked();

     void on_pb_supprimer_2_clicked();

     void on_tab_facture_2_clicked(const QModelIndex &index);

     void on_pb_miseajour_2_clicked();

     void on_pushButton3_clicked();

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
    /* void on_pbimp_2_clicked();

     void on_pbimp_3_clicked();
 */
     void on_pb_journuit_2_clicked();

   //  void update_label();

    /* void on_pb_on_clicked();

     void on_pb_off_clicked();

     void on_pb_plus_clicked();

     void on_pb_moins_clicked();

*/
// |||||||||||||||||||||||||||fediiiiiiiiiiiiiiiiii
     void on_exit_triggered();

     void on_pushButton_6_clicked();

     void on_pushButton_aj_clicked();

     void on_pushButton_7_clicked();

   //  void on_pushButton_12_clicked();

  //   void on_pushButton_2_clicked();

     void on_pushButton_8_clicked();

     void on_pushButton_9_clicked();

  //   void on_pushButton_11_clicked();

    void on_pushButton_fedi_clicked();

    void on_pushButton_supfedimachin_clicked();

    void on_pushButton_modiffedimachin_clicked();

   //  void on_pushButton_13_clicked();

    // void on_pushButton_18_clicked();

 //    void on_pushButton_16_clicked();

  //   void on_pushButton_17_clicked();

  //   void on_pushButton_19_clicked();

   //  void on_pushButton_6_clicked();

     void on_id_machine_affchage_3_currentTextChanged(const QString &arg1);

     void on_pushButton_14_clicked();

     void on_pushButton_15_clicked();

     void on_id_maintenance_modif_currentTextChanged(const QString &arg1);

     void on_annuler_clicked();

     void on_pushButton_21_clicked();

     void on_pushButton_20_clicked();

     void on_rech_clicked();

     void on_actionImprimmer_triggered();

     void on_comboBox_trifadi_currentIndexChanged(int index);

     void on_Imprimer_clicked();

     void on_tabWidget_3fedi_tabBarClicked(int index);

     void on_recherche_textChanged(const QString &arg1);


     void on_checkBox_toggled(bool checked);

   //  void on_nom_produit_currentTextChanged(const QString &arg1);

  //   void recup();





     void on_retour_accueil_2_clicked();

     void on_retour_accueil_3_clicked();

     void on_retour_accueil_4_clicked();

signals:
   void test();
   void em();

private:
    Ui::MainWindow *ui;
    Employe e;
    QTcpSocket *mSocket;
    QSerialPort *serial;
    QString portname;
    quint16 vendorId;
    quint16 productId;
    bool arduino_available;
    void arduino_init();
    QByteArray data;
    QString serialBuffer;
    Arduino A;
     Stocks *Stock;
     factures ftmp;
     commandes ctmp;
     QString nbf ;
 int trie=-1 ;
 Maintenance M ;
 Machine MM ;

 QQuickView *qmlView;
};
#endif // MAINWINDOW_H
