#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include "arduino.h"
#include <QMainWindow>
#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QUrl>
#include <QTcpServer>
#include<QTcpSocket>

#include<QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTcpSocket;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:



    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_modifier_clicked();

    /*void on_recherche_button_clicked();*/

    void on_annuler_clicked();

    void on_supp_ajout_clicked();


    void on_id_box_currentIndexChanged(const QString &arg1);


    void on_tab_employe_activated(const QModelIndex &index);

    void on_tri_button_asc_clicked();

    void on_tri_button_desc_clicked();

    void on_imprimer_button_clicked();


    void on_statistiques_widget_tabBarClicked(int index);

    void on_statistiques_widget_currentChanged(int index);

    void on_mdp_oublie_clicked();




    void on_pb_envoyer_clicked();

    void on_pb_connecter_clicked();



    void on_barre_recherche_textChanged(const QString &arg1);
    void serial_read();
    void update_label();
    void on_open_door_arduino_2_clicked();

    void on_close_door_arduino_clicked();

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
};
#endif // MAINWINDOW_H
