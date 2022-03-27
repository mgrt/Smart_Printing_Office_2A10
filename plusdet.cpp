#include "plusdet.h"
#include "ui_plusdet.h"

plusdet::plusdet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plusdet)
{
    ui->setupUi(this);
}

plusdet::~plusdet()
{
    delete ui;
}
