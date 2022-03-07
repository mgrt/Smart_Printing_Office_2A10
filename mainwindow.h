#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <clients.h>
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


private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_idmodifc_currentTextChanged(const QString &arg1);

    void on_pb_miseajour_clicked();

    void on_pb_modifier_2_clicked();

    void on_pb_recherche_clicked();



    void on_pb_annuler_clicked();

private:
    Ui::MainWindow *ui;
    Clients Etmp;
};
#endif // MAINWINDOW_H
