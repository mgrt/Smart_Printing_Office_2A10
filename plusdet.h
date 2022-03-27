#ifndef PLUSDET_H
#define PLUSDET_H

#include <QWidget>

namespace Ui {
class plusdet;
}

class plusdet : public QWidget
{
    Q_OBJECT

public:
    explicit plusdet(QWidget *parent = nullptr);
    ~plusdet();

private:
    Ui::plusdet *ui;
};

#endif // PLUSDET_H
