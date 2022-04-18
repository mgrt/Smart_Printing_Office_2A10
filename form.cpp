#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    Stocks *Stock =new Stocks();
    ui->tableView->setModel(Stock->afficher());
}

Form::~Form()
{
    delete ui;
}
