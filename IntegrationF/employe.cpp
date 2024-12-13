#include "employe.h"


#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>

employe::employe(int id,  QString nom,  QString prenom, QString email,  int salaire,  QString numero,  QString poste,QString disponibilite,QDate DATE_DE_EMBAUCHE) {
 this->id=id;
 this->nom=nom;
 this->prenom=prenom;
 this->disponibilite=disponibilite;
 this->email=email;
 this->salaire=salaire;
 this->numero=numero;
    this->poste=poste;
        this->DATE_DE_EMBAUCHE=DATE_DE_EMBAUCHE;
}

employe::employe()
    {
      id=0;
      nom="";
      prenom="";
      disponibilite=("");
      email="";
      numero="";
      DATE_DE_EMBAUCHE=QDate::currentDate();
    salaire=0;
    poste="";
}

int employe::getId()  {
    return id;
}

QString employe::getNom()  {
    return nom;
}

QString employe::getprenom()  {
    return prenom;
}

QString employe::getdisponibilite()  {
    return disponibilite;
}

QString employe::getemail()  {
    return email;
}

QDate employe::getDATE_DE_EMBAUCHE()  {
    return  DATE_DE_EMBAUCHE;
}

QString employe::getnumero()  {
    return numero;
}
QString employe::getposte()  {
    return poste;
}
int employe::getsalaire()  {
    return salaire;
}

void employe::setID( int id) {
    this->id = id;
}
void employe::setNom( QString nom) {
    this->nom = nom;
}
void employe::setprenom(QString prenom)  {
    this->prenom = prenom;
}
void employe::setemail(QString email)
{
    this->email = email;
}


void employe::setdisponibilite( QString disponibilite) {
    this->disponibilite = disponibilite;
}

void employe::setDATE_DE_EMBAUCHE(QDate DATE_DE_EMBAUCHE) {
    this->DATE_DE_EMBAUCHE = DATE_DE_EMBAUCHE;
}




void employe::setsalaire(int salaire)
 {
    this->salaire = salaire;
}

void employe::setnumero( QString numero) {
    this->numero = numero;
}
void employe::setposte(QString poste)  {
    this->poste = poste;
}


bool employe::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYES (ID_E, NOM, PRENOM, EMAIL, SALAIRE, NUMEROTELEPHONE, POSTE,DISPONIBILITE,DATEEMBAUCHE) "
                  "VALUES (:ID, :NOM, :PRENOM, :EMAIL,:SALAIRE, :NUMEROTELEPHONE, :POSTE,:DISPONIBILITE,:DATEEMBAUCHE)");

    query.bindValue(":ID", id);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":EMAIL", email);
    query.bindValue(":SALAIRE", salaire);
    query.bindValue(":NUMEROTELEPHONE", numero);
    query.bindValue(":POSTE", poste);
    query.bindValue(":DISPONIBILITE", disponibilite);
    query.bindValue(":DATEEMBAUCHE", DATE_DE_EMBAUCHE);

    return query.exec();
}


QSqlQueryModel* employe::afficher()  {
    QSqlQueryModel* model = new QSqlQueryModel();
    // Exécutez la requête
    model->setQuery("SELECT * FROM EMPLOYES");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("SALAIRE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUMEROTELEPHONE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("POSTE"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("DISPONIBILITE"));
model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATEEMBAUCHE"));

    return model;
}

bool employe::EMPLOYEExists(int id)  {
    QSqlQuery query;
    query.prepare("SELECT ID_E FROM EMPLOYES WHERE ID_E = :ID");
    query.bindValue(":ID", id);
    if(query.exec() && query.next())
     {
      int count = query.value(0).toInt();
      return count >0 ;

    }
return false;
}


bool employe::supprimer(int id)
{
QSqlQuery query;
query.prepare("Delete from EMPLOYES WHERE ID_E=:ID");
query.bindValue(0,id);
return query.exec();
}


bool employe::modifier(int id,  QString nom,  QString prenom, QString email,  int salaire,  QString numero,  QString poste,QString disponibilite,QDate DATE_DE_EMBAUCHE) {
    QSqlQuery query;
    query.prepare("UPDATE  EMPLOYES SET  NOM=:NOM, PRENOM=:PRENOM, EMAIL=:EMAIL, SALAIRE=:SALAIRE, NUMEROTELEPHONE=:NUMEROTELEPHONE, POSTE=:POSTE,DISPONIBILITE=:DISPONIBILITE,DATEEMBAUCHE=:DATE_DE_EMBAUCHE WHERE ID_E=:ID ");
    query.bindValue(":ID", id);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":EMAIL", email);
    query.bindValue(":SALAIRE", salaire);
    query.bindValue(":NUMEROTELEPHONE", numero);
    query.bindValue(":POSTE", poste);
    query.bindValue(":DISPONIBILITE", disponibilite);
    query.bindValue(":DATE_DE_EMBAUCHE", DATE_DE_EMBAUCHE);
    return query.exec();
}



QSqlQueryModel* employe::tri(QString column)  {
    QSqlQueryModel* model = new QSqlQueryModel();
    // Exécutez la requête
    model->setQuery("SELECT * FROM EMPLOYES ORDER BY "+column+ " ASC");// ORDER BY ID

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("SALAIRE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUMEROTELEPHONE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("POSTE"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("DISPONIBILITE"));
model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATEEMBAUCHE"));

    return model;
}

QSqlQueryModel* employe::tri1(QString column)  {
    QSqlQueryModel* model = new QSqlQueryModel();
    // Exécutez la requête
    model->setQuery("SELECT * FROM EMPLOYES ORDER BY "+column+ " DESC");// ORDER BY ID

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("SALAIRE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUMEROTELEPHONE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("POSTE"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("DISPONIBILITE"));
model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATEEMBAUCHE"));

    return model;
}

QSqlQueryModel* employe::chercher(QString column,QString text)  {
    QSqlQueryModel* model = new QSqlQueryModel();
    bool isNumeric = false;

       if (column == "ID_E" || column == "SALAIRE" || column == "NUMEROTELEPHONE") {
           isNumeric = true;
       }
qDebug()<<text;
       QString query;
       if (isNumeric) {
           query = QString("SELECT * FROM EMPLOYES WHERE %1 LIKE %2").arg(column).arg("'%"+text+"%'");
       } else {
           query = QString("SELECT * FROM EMPLOYES WHERE %1 LIKE '%%2%'").arg(column).arg(text);
       }
       // Exécutez la requête

       model->setQuery(query);

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("SALAIRE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUMEROTELEPHONE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("POSTE"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("DISPONIBILITE"));
model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATEEMBAUCHE"));

    return model;
}



int employe::countSalaire(const QString& min,const QString& max)
 {
     int count = 0;

     QSqlQuery query;
     query.prepare("SELECT COUNT(SALAIRE) FROM EMPLOYES WHERE SALAIRE BETWEEN :min AND :max");
     query.bindValue(":min", min);
 query.bindValue(":max", max);
     if (query.exec() && query.next()) {
         count = query.value(0).toInt();
     }

     return count;
 }
