#ifndef LOGIN_H
#define LOGIN_H
#include "employe.h"
#include "smtp.h"
#include <QDebug>
#include <QUrl>
#include <QSqlDatabase>
#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_checkBox_clicked();

    void on_mdp_oublie_clicked();

    void on_retourner_clicked();

    void mailSent(QString status);

    void on_forgotNext_clicked();

    void on_loginForgot_clicked();


    void on_checkBox_3_clicked();

private:
    Ui::login *ui;

};

#endif // LOGIN_H
