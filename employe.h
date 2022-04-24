#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QDialog>
#include <QList>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>

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
    QSqlQueryModel * trie_nom_asc();
    QSqlQueryModel * trie_prenom_asc();
    QSqlQueryModel * trie_adr_asc();
    QSqlQueryModel * trie_nationalite_asc();
    QSqlQueryModel * trie_cin_asc();
    QSqlQueryModel * trie_nom_desc();
    QSqlQueryModel * trie_prenom_desc();
    QSqlQueryModel * trie_adr_desc();
    QSqlQueryModel * trie_nationalite_desc();
    QSqlQueryModel * trie_cin_desc();
    void statistique(QWidget * w);
    QSqlQueryModel *count(QString,QString);
private:
    QString nom, prenom, Email, adresse;
    int CIN, num_telephone;
    QString mdp, role, sexe, nationalite;
    QDate date_naissance;
    QList<Employe> listE;
};

#endif // EMPLOYE_H
