#include "client.h"
#include <QSqlQuery>
#include <QSqlQueryModel>


Clients::Clients(int idClient, QString nom, QString prenom, QString typeservice, QString typeclient, QString adresse, QString numtel)
{
    this->idClient =idClient;
    this->nom = nom;
    this->prenom = prenom;
    this->typeservice = typeservice;
    this->typeclient = typeclient;
    this->adresse = adresse;
    this->numtel = numtel;
}

bool Clients::ajouter()
{
    QSqlQuery query;
    // Préparation de la requête SQL pour l'insertion
    query.prepare("INSERT INTO FS_CLIENTS (idClient, nom, prenom, typeService, typeClient, adresse, numTel) "
                  "VALUES (:idClient, :nom, :prenom, :typeService, :typeClient, :adresse, :numTel)");

    query.bindValue(":idClient", idClient);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":typeService", typeservice);
    query.bindValue(":typeClient", typeclient);
    query.bindValue(":adresse", adresse);
    query.bindValue(":numTel", numtel);

    // Exécution de la requête
    return query.exec();
}
bool Clients::modifier()
{
    QSqlQuery query;
    // Préparation de la requête SQL pour l'insertion
    query.prepare("UPDATE FS_CLIENTS SET  nom=:nom, prenom=:prenom, typeService=:typeService, typeClient=:typeClient, adresse=:adresse, numTel=:numTel WHERE idClient=:idClient");

    query.bindValue(":idClient", idClient);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":typeService", typeservice);
    query.bindValue(":typeClient", typeclient);
    query.bindValue(":adresse", adresse);
    query.bindValue(":numTel", numtel);

    // Exécution de la requête
    return query.exec();
}
bool Clients::supprimer(int idClient) {

        QSqlQuery query;
        query.prepare("DELETE FROM FS_CLIENTS WHERE idClient = :idClient");
        query.bindValue(":idClient", idClient);

    return query.exec();
    }

QSqlQueryModel* Clients::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FS_CLIENTS");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type de Service"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type de Client"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Numéro de Téléphone"));


    return model;
}


bool Clients::idExists(int id)
{
QSqlQuery query;
query.prepare("SELECT COUNT(*) FROM FS_CLIENTS WHERE IDCLIENT = :id");
query.bindValue(":id", id);

if (query.exec() && query.next()) {
    int count = query.value(0).toInt();
    return count > 0;
}

return false;
}
QSqlQueryModel* Clients::tri(const QString&  column,const QString&  choix)
{
QSqlQueryModel* model = new QSqlQueryModel();
model->setQuery("SELECT * FROM FS_CLIENTS ORDER BY "+column +" "+choix);


return model;
}

QSqlQueryModel* Clients::chercher(QString column,QString text)
{
QSqlQueryModel* model = new QSqlQueryModel();
model->setQuery("SELECT * FROM FS_CLIENTS WHERE "+column+" LIKE '%" + text + "%' ");


return model;
}


int Clients::countService(const QString&service)
{
    int count = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(TYPESERVICE) FROM FS_CLIENTS WHERE TYPESERVICE = :TYPESERVICE");
    query.bindValue(":TYPESERVICE", service);

    if (query.exec() && query.next()) {
        count = query.value(0).toInt();
    }

    return count;
}
