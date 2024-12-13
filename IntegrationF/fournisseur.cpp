#include "fournisseur.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QFileDialog>


Fournisseur::Fournisseur(int id, QString nom, int num_tel, QString mail, QString adresse, QString type_f, QString type_p, int id_produit)
{
    this->id = id;
    this->nom = nom;
    this->num_tel = num_tel;
    this->mail = mail;
    this->adresse = adresse;
    this->type_f = type_f;
    this->type_p = type_p;
    this->id_produit = id_produit;
}

// Function to validate num_tel
bool Fournisseur::validateNumTel() const
{
    QString numStr = QString::number(num_tel);
    return numStr.length() == 6 && numStr.toInt() > 0;  // Ensures it has 8 digits
}

// Function to validate email
bool Fournisseur::validateMail() const
{
    QRegularExpression emailRegex("^[^@]+@[^@]+$");
    return emailRegex.match(mail).hasMatch();  // Checks for valid email format
}

// Function to validate type_f
bool Fournisseur::validateTypeF() const
{
    return (type_f == "Type A" || type_f == "Type B" || type_f == "Type C");
}

bool Fournisseur::ajouter()
{
    // Validate input before adding to the database
    if (!validateNumTel()) {
        QMessageBox::warning(nullptr, "Invalid Input", "Phone number must be exactly 8 digits.");
        return false;
    }
    if (!validateMail()) {
        QMessageBox::warning(nullptr, "Invalid Input", "Email is not in a valid format.");
        return false;
    }
    if (!validateTypeF()) {
        QMessageBox::warning(nullptr, "Invalid Input", "Type must be 'Type A', 'Type B', or 'Type C'.");
        return false;
    }

    QSqlQuery query;

    // Convert the integer values to QString for binding
    QString res = QString::number(id);
    QString res1 = QString::number(num_tel);
    QString res2 = QString::number(id_produit);

    query.prepare("INSERT INTO FOURNISSEURS (ID, NOM, NUM_TEL, MAIL, ADRESSE, TYPE_F, TYPE_P, ID_PRODUIT) "
                  "VALUES (:id, :nom, :num_tel, :mail, :adresse, :type_f, :type_p, :id_produit)");

    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":num_tel", res1);
    query.bindValue(":mail", mail);
    query.bindValue(":adresse", adresse);
    query.bindValue(":type_f", type_f);
    query.bindValue(":type_p", type_p);
    query.bindValue(":id_produit", res2);

    return query.exec();
}

bool Fournisseur::modifier(int id)
{
    // Validate input before modifying the database
    if (!validateNumTel()) {
        QMessageBox::warning(nullptr, "Invalid Input", "Phone number must be exactly 8 digits.");
        return false;
    }
    if (!validateMail()) {
        QMessageBox::warning(nullptr, "Invalid Input", "Email is not in a valid format.");
        return false;
    }
    if (!validateTypeF()) {
        QMessageBox::warning(nullptr, "Invalid Input", "Type must be 'Type A', 'Type B', or 'Type C'.");
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE FOURNISSEURS SET NOM = :1, NUM_TEL = :2, MAIL = :3, ADRESSE = :4, TYPE_F = :5, TYPE_P = :6, ID_PRODUIT = :7 WHERE ID = :0");

    query.bindValue(":0", id);
    query.bindValue(":1", nom);
    query.bindValue(":2", num_tel);
    query.bindValue(":3", mail);
    query.bindValue(":4", adresse);
    query.bindValue(":5", type_f);
    query.bindValue(":6", type_p);
    query.bindValue(":7", id_produit);

    return query.exec();
}



 QSqlQueryModel * Fournisseur::afficher()
 {
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("select * from FOURNISSEURS");
   model->setHeaderData (0,Qt::Horizontal, QObject::tr("ID"));
   model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
   model->setHeaderData (2,Qt::Horizontal, QObject::tr("NUM_TEL"));
   model->setHeaderData (3,Qt::Horizontal, QObject::tr("MAIL"));
   model->setHeaderData (4,Qt::Horizontal, QObject::tr("ADRESSE"));
   model->setHeaderData (5,Qt::Horizontal, QObject::tr("TYPE_F"));
   model->setHeaderData (6,Qt::Horizontal, QObject::tr("TYPE_P"));
   model->setHeaderData (7,Qt::Horizontal, QObject::tr("ID_PRODUIT"));

   return model;
 }

 bool Fournisseur::supprimer (int ID)
 {
    QSqlQuery query;
    QString res = QString::number(ID);
    query.prepare("Delete from FOURNISSEURS where ID = :ID");
    query.bindValue(":ID", res);

    return query.exec();
 }


 QSqlQueryModel * Fournisseur::triID()
 {
     QSqlQueryModel * model = new QSqlQueryModel();
     model->setQuery("SELECT * FROM FOURNISSEURS ORDER BY ID");

     // Set column headers based on the 'afficher' function
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM_TEL"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE_F"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("TYPE_P"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_PRODUIT"));

     return model;
 }

 QSqlQueryModel * Fournisseur::triNOM()
 {
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("select * from FOURNISSEURS ORDER by NOM");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM_TEL"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE_F"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("TYPE_P"));
   model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_PRODUIT"));

   return model;
 }

 QSqlQueryModel * Fournisseur::triMAIL()
 {
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("select * from FOURNISSEURS ORDER by MAIL");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM_TEL"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE_F"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("TYPE_P"));
   model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_PRODUIT"));

   return model;
 }

 QSqlQueryModel* Fournisseur::chercher(QString searchCriteria)
 {
     QSqlQueryModel* model = new QSqlQueryModel();
     QSqlQuery query;

     // Construct the SQL query to search in the "NOM" column in the FOURNISSEURS table
     QString queryString = "SELECT * FROM FOURNISSEURS WHERE NOM LIKE '%" + searchCriteria + "%'";

     model->setQuery(queryString);

     // Set column headers based on the attributes of the FOURNISSEURS table
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM_TEL"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE_F"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("TYPE_P"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_PRODUIT"));

     return model;
 }



