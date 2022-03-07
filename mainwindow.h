#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include <QMainWindow>

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

    void on_pb_supprimer_clicked();

    void on_modifier_clicked();

    void on_recherche_button_clicked();

    void on_annuler_clicked();

    void on_supp_ajout_clicked();


    void on_id_box_currentIndexChanged(const QString &arg1);


    void on_tab_employe_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Employe e;
};
#endif // MAINWINDOW_H
