#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QDialog>
#include <QList>

class Employe
{
public:
    Employe();
    Employe(int,QString,QString,QString,QString,QDate,QString,QString,int,QString,QString);
    int getcin();
    QString getnom();
    QString getprenom();
    QString getsexe();
    QString getrole();
    QDate getdate();
    QString getnationalite();
    QString getadresse();
    int getnumtelephone();
    QString getmdp();
    QString getemail();
    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setsexe(QString);
    void setrole(QString);
    void setdate(QDate);
    void setnationalite(QString);
    void setadresse(QString);
    void setnumtelephone(int);
    void setmdp(QString);
    void setemail(QString);
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int);
    bool recherche_id(int);
    bool recherche_cin(int);
    QSqlQueryModel* recherche(QString);
    QSqlQueryModel* combobox_id();

private:
    QString nom, prenom, Email, adresse;
    int CIN, num_telephone;
    QString mdp, role, sexe, nationalite;
    QDate date_naissance;
    QList<Employe> listE;
};

#endif // EMPLOYE_H
