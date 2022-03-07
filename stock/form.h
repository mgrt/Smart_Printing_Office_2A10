#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include "stocks.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private:
    Ui::Form *ui;
      Stocks *Stock;
};

#endif // FORM_H
