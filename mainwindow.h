#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "connection.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include "stocks.h"
#include "arduino.h"
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
    void update_label();
 int rech(QString tab[],QCharRef c);
 int decod(int a,int b,int dec);
void aff();

    void on_pushButton_clicked();

   // void on_pushButton_2_clicked();

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

    void on_pushButton_2_clicked();

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

    void on_pushButton_ref_6_clicked();



    void on_tri_currentIndexChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_on_clicked();

    void on_off_clicked();

    void on_plus_clicked();

    void on_mins_clicked();

signals:
   void test();

private:
    Ui::MainWindow *ui;
    Stocks *Stock;
    void sendMail();
    void mailSent(QString);
    QByteArray data;
    Arduino A;
public:
    bool pls=false;
 // QStandardItemModel *model;
};
#endif // MAINWINDOW_H
