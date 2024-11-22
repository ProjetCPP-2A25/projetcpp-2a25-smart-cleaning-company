#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection()
{
    bool test=false;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source25");//inserer le nom de la source de données//source25
    db.setUserName("system");//inserer nom de l'utilisateur//system
    db.setPassword("Khotba0704");//inserer mot de passe de cet utilisateur//Khotba0704

    if (db.open()) test=true;
    return  test;
}
void Connection::closeConnection(){
    db.close();
}
