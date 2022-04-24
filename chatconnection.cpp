#include "chatconnection.h"
#include "ui_chatconnection.h"

Chatconnection::Chatconnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chatconnection)
{
    ui->setupUi(this);
}

Chatconnection::~Chatconnection()
{
    delete ui;
}

void Chatconnection::on_accepter_clicked()
{
  mHostname = ui->hostname->text();
  mPort = ui->port->value();
  accept();
}


void Chatconnection::on_annuler_clicked()
{
  reject();
}

