#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <clients.h>
#include <reclamation.h>
#include <QMainWindow>
#include "QMessageBox"
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QTabWidget>
#include <QSqlQueryModel>
#include <QIntValidator>
#include <QRegExpValidator>
#include <iostream>
//PDF
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QTextStream>
#include <QPainter>
//Stat
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void warning();
    QString langue;


private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_idmodifc_currentTextChanged(const QString &arg1);

    void on_pb_miseajour_clicked();

    void on_pb_modifier_2_clicked();

    void on_pb_recherche_clicked();



    void on_pb_annuler_clicked();

    void on_pb_trier_id_clicked();

    void on_pb_trier_nom_clicked();

    void on_pb_trier_prenom_clicked();

    void on_pb_trier_date_clicked();

    void on_pb_trier_id_2_clicked();

    void on_pb_trier_nom_2_clicked();

    void on_pb_trier_prenom_2_clicked();

    void on_pb_trier_date_2_clicked();

    void on_pb_PDF_clicked();

    void on_pb_stat_genre_clicked();

    void on_pb_stat_age_clicked();

    void on_pb_ajouter_2_clicked();
    void update();
    void on_pb_miseajour_2_clicked();

    void on_id_rec_currentTextChanged(const QString &arg1);

    void on_pb_supprimer_2_clicked();



    void on_pb_modifier_3_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Clients Etmp;
    reclamations rec;
};
#endif // MAINWINDOW_H
