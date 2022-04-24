#ifndef CHATCONNECTION_H
#define CHATCONNECTION_H

#include <QDialog>

namespace Ui {
class Chatconnection;
}


class Chatconnection : public QDialog
{
    Q_OBJECT

public:
    explicit Chatconnection(QWidget *parent = nullptr);
    ~Chatconnection();
    QString hostname() const;
    quint16 port() const;
private slots:
    void on_accepter_clicked();

    void on_annuler_clicked();

private:
    Ui::Chatconnection *ui;
    QString mHostname;
    quint16 mPort;
};

inline QString Chatconnection::hostname() const
{
   return mHostname;
}
inline quint16 Chatconnection::port() const
{
  return mPort;
}
// end namespace Chatconnection

#endif // CHATCONNECTION_H
