#include "connection.h"

Connection::Connection()
{

}

bool Connection::ouvrirConnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet");//inserer le nom de la source de données ODBC
db.setUserName("malek");//inserer nom de l'utilisateur
db.setPassword("esprit1477");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
else
    throw QString("Erreur Paramétres"+test);

return  test;
}

void Connection::fermerConnection(){
    db.close();
}
