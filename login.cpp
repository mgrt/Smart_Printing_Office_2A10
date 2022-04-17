#include "login.h"
#include "ui_login.h"
#include "QFileDialog"
#include "QSqlQueryModel"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QSqlError>
#include "QMessageBox"
#include "QSqlQuery"
#include "employe.h"
#include "smtp.h"
#include<QSslSocket>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->frame_3->hide();
    ui->frame_5->hide();
    ui->mail_sprint->hide();
    ui->smtp_gmail->hide();
    ui->port_smtp->hide();
    ui->mdp_sprint->hide();
    ui->code->hide();
    ui->newmdp1->hide();
    ui->newmdp2->hide();
    ui->checkBox_3->hide();
    ui->loginForgot->hide();

    this->setGeometry(20,200,800,800);
}

login::~login()
{
    delete ui;
}

void login::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked()){
        ui->password->setEchoMode(QLineEdit::Normal);
        ui->checkBox->setText("Hide password");
    }else{
        ui->password->setEchoMode(QLineEdit::Password);
        ui->checkBox->setText("Show password");
    }
}



void login::on_mdp_oublie_clicked()
{
    ui->frame_2->hide();
    ui->frame_3->hide();
    this->setWindowTitle("Forgot Password");
    ui->frame_5->show();
}


void login::on_retourner_clicked()
{

    ui->frame_5->hide();
    ui->frame_3->hide();
    this->setWindowTitle("Sign in");
    ui->frame_2->show();
}

// email forgotten nextforgot
QString emailforgot;

void login::mailSent(QString status)
{
        if(status == "Message sent")
            QMessageBox::information( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void login::on_forgotNext_clicked()
{
    ui->label_3->setText("Enter the \ncode sent to the email in the code field");

    //The entered email database is checked for availability --------
    QString email = ui->email_2->text();
    emailforgot = email;
    QSqlQuery query3;
    query3.prepare("select * from employee where email='"+email+"'");

    int count = 0;
    if(query3.exec()){
        while (query3.next()) {
            count++;
        }
        if(count == 1){
            Smtp* smtp = new Smtp(ui->mail_sprint->text(),ui->mdp_sprint->text(),ui->smtp_gmail->text(),ui->port_smtp->text().toUShort());
            connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
            smtp->sendMail(ui->mail_sprint->text(),email,"votre code de recuperation","votre code est 95863");
            ui->code->show();
            ui->newmdp1->show();
            ui->newmdp2->show();
            ui->checkBox_3->show();
            ui->loginForgot->show();
            ui->email_2->hide();
            ui->forgotNext->hide(); 
        }else{
            ui->label_3->setText("There is no such user");
        }
    }
}


void login::on_loginForgot_clicked()
{
    //when resetting the password, the correctness of the code sent and the compatibility of the passwords are checked
    QString mdp_1 = ui->newmdp1->text(),
            mdp_2 = ui->newmdp2->text(),
            code = ui->code->text(),
            emailf = emailforgot;
    if(code == "95863"){
        if(mdp_1 == mdp_2){
            QSqlQueryModel *m=new QSqlQueryModel();
            m->setQuery("UPDATE employee SET mdp='"+ mdp_1 +"' WHERE email='"+ emailf +"'");
            //kod yangi qoyildi va sign in ga otildi
            ui->frame_5->hide();
            ui->frame_3->hide();
            this->setWindowTitle("Sign in");
            ui->frame_2->show();

        }else{
            ui->label_3->setText("Is there an error in matching passwords?");
        }
    }else{
        ui->label_3->setText("Error code. ??");
    }
}





void login::on_checkBox_3_clicked()
{
    if(ui->checkBox_3->isChecked()){
        ui->newmdp1->setEchoMode(QLineEdit::Normal);
        ui->checkBox_3->setText("Hide password");
    }else{
        ui->newmdp1->setEchoMode(QLineEdit::Password);
        ui->checkBox_3->setText("Show password");
    }
}

