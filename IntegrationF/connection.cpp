#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

Connection::Connection() {}

bool Connection::createconnect() {
    // Créer une connexion à la base de données
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("CPP_Project"); // Nom de la base de données
    db.setUserName("maryem");
    db.setPassword("oracle");

    // Essayer d'ouvrir la base de données
    if (!db.open()) {
        return false; // Connexion échouée
    }


    return true; // Connexion réussie
}
