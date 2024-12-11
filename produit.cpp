#include "produit.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
PRODUIT::PRODUIT(int id,  QString nom,  int prix, QString disponibilite,  QString image,  QDate DATE_DE_VALIDITE,  QString TYPE_DE_PRODUIT,int ID_F) {
 this->id=id;
 this->nom=nom;
 this->prix=prix;
 this->disponibilite=disponibilite;
 this->image=image;
 this->DATE_DE_VALIDITE=DATE_DE_VALIDITE;
 this->TYPE_DE_PRODUIT=TYPE_DE_PRODUIT;
    this->ID_F=ID_F;
}

PRODUIT::PRODUIT()
    {
      id=0;
      nom="";
      prix=0;
      disponibilite=("");
      DATE_DE_VALIDITE=QDate::currentDate();
      image="0";
      TYPE_DE_PRODUIT="";
      ID_F=0;
}

int PRODUIT::getId()  {
    return id;
}

QString PRODUIT::getNom()  {
    return nom;
}

int PRODUIT::getprix()  {
    return prix;
}

QString PRODUIT::getdisponibilite()  {
    return disponibilite;
}

QString PRODUIT::getimage()  {
    return image;
}

QDate PRODUIT::getDATE_DE_VALIDITE()  {
    return DATE_DE_VALIDITE;
}

QString PRODUIT::getTYPE_DE_PRODUIT()  {
    return TYPE_DE_PRODUIT;
}
int PRODUIT::getID_F()  {
    return ID_F;
}


void PRODUIT::setID( int id) {
    this->id = id;
}
void PRODUIT::setNom( QString nom) {
    this->nom = nom;
}

void PRODUIT::setprix( int prix) {
    this->prix = prix;
}

void PRODUIT::setdisponibilite( QString disponibilite) {
    this->disponibilite = disponibilite;
}

void PRODUIT::setimage(QString image) {
    this->image = image;
}



void PRODUIT::setDATE_DE_VALIDITE( QDate DATE_DE_VALIDITE) {
    this->DATE_DE_VALIDITE = DATE_DE_VALIDITE;
}

void PRODUIT::setTYPE_DE_PRODUIT(QString TYPE_DE_PRODUIT)
 {
    this->TYPE_DE_PRODUIT = TYPE_DE_PRODUIT;
}

void PRODUIT::setID_F( int ID_F) {
    this->ID_F = ID_F;
}


bool PRODUIT::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO PRODUITS (ID_P, NOM_P, PRIX, DISPONIBILITE, IMAGES, DATE_DE_VALIDITE, TYPE_DE_PRODUIT,ID_F) "
                  "VALUES (:ID, :NOM, :PRIX, :disponibilite,:image, :VALIDITE, :TYPE_DE_PRODUIT,:ID_F)");

    query.bindValue(":ID", id);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRIX", prix);
    query.bindValue(":disponibilite", disponibilite);
    query.bindValue(":image", image);
    query.bindValue(":VALIDITE", DATE_DE_VALIDITE);
    query.bindValue(":TYPE_DE_PRODUIT", TYPE_DE_PRODUIT);
    query.bindValue(":ID_F", ID_F);

    return query.exec();
}


QSqlQueryModel* PRODUIT::afficher()  {
    QSqlQueryModel* model = new QSqlQueryModel();
    // Exécutez la requête
    model->setQuery("SELECT * FROM PRODUITS");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRIX"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("DISPONIBILITE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("IMAGES"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_DE_VALIDITE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("TYPE_DE_PRODUIT"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("ID_F"));

    return model;
}

bool PRODUIT::produitExists(int id)  {
    QSqlQuery query;
    query.prepare("SELECT ID_P FROM PRODUITS WHERE ID_P = :ID");
    query.bindValue(":ID", id);
    if(query.exec() && query.next())
     {
      int count = query.value(0).toInt();
      return count >0 ;

    }
return false;
}


bool PRODUIT::supprimer(int id)
{
QSqlQuery query;
query.prepare("Delete from PRODUITS WHERE ID_P=:ID");
query.bindValue(0,id);
return query.exec();
}


bool PRODUIT::modifier(int id,  QString nom,  int prix, QString disponibilite,  QString image,  QDate DATE_DE_VALIDITE,  QString TYPE_DE_PRODUIT,int ID_F) {
    QSqlQuery query;
    query.prepare("UPDATE  PRODUITS SET  NOM_P=:NOM_P, PRIX=:PRIX, DISPONIBILITE=:DISPONIBILITE, IMAGES=:IMAGES, DATE_DE_VALIDITE=:DATE_DE_VALIDITE, TYPE_DE_PRODUIT=:TYPE_DE_PRODUIT,ID_F=:ID_F WHERE ID_P=:ID_P ");
    query.bindValue(":ID_P", id);
    query.bindValue(":NOM_P", nom);
    query.bindValue(":PRIX", prix);
    query.bindValue(":DISPONIBILITE", disponibilite);
    query.bindValue(":IMAGES", image);
    query.bindValue(":DATE_DE_VALIDITE", DATE_DE_VALIDITE);
    query.bindValue(":TYPE_DE_PRODUIT", TYPE_DE_PRODUIT);
    query.bindValue(":ID_F", ID_F);
    return query.exec();
}


QSqlQueryModel* PRODUIT::tri(QString column)
{
QSqlQueryModel* model = new QSqlQueryModel();
model->setQuery("SELECT * FROM PRODUITS ORDER BY " + column + " ASC");

return model;
}

QSqlQueryModel* PRODUIT::tri1(QString column)
{
QSqlQueryModel* model = new QSqlQueryModel();
model->setQuery("SELECT * FROM PRODUITS ORDER BY " + column + " DESC");

return model;
}

QSqlQueryModel* PRODUIT::chercher(QString column, QString text)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Prepare the SQL query with parameter binding for safety
    QString queryStr = QString("SELECT * FROM PRODUITS WHERE %1 LIKE :text").arg(column);
    QSqlQuery qry;
    qry.prepare(queryStr);
    qry.bindValue(":text", "%" + text + "%"); // Bind the text with wildcards

    // Execute the query
    if (qry.exec()) {
        model->setQuery(qry);
    } else {
        qDebug() << "Query execution failed:" << qry.lastError().text();
    }

    return model;
}

int PRODUIT::countType(const QString& type)
 {
     int count = 0;

     QSqlQuery query;
     query.prepare("SELECT COUNT(\"TYPE_DE_PRODUIT\") FROM PRODUITS WHERE \"TYPE_DE_PRODUIT\" = :TYPE");
     query.bindValue(":TYPE", type);

     if (query.exec() && query.next()) {
         count = query.value(0).toInt();
     }

     return count;
 }
