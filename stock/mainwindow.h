#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "connection.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include "stocks.h"
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
 int rech(QString tab[],QString c);
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

signals:
   void test();

private:
    Ui::MainWindow *ui;
    Stocks *Stock;
public:
    bool pls=false;
 // QStandardItemModel *model;
};
#endif // MAINWINDOW_H
