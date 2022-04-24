#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet");
db.setUserName("malek");//inserer nom de l'utilisateur
db.setPassword("esprit1477");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

return  test;
}

void Connection::closeConnection(){db.close();}





