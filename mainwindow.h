#ifndef MAINWINDOW_H
#define MAINWINDOW_H


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


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initialisation_demarage();
    void update_output_data();
    void warning ();
    void controle_de_saisie();
private slots:
    void on_exit_triggered();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_6_clicked();

    void on_id_machine_affchage_3_currentTextChanged(const QString &arg1);

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_id_maintenance_modif_currentTextChanged(const QString &arg1);

    void on_annuler_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_20_clicked();

    void on_rech_clicked();

private:
    Maintenance M ;
    Machine MM ;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
