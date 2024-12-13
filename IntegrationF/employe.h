#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QDate>


class employe {
public:
     employe();
    employe(int id,  QString nom,  QString prenom, QString email,  int salaire,  QString numero,  QString poste,QString disponibilite,QDate DATE_DE_EMBAUCHE);
    // Getters
    int getId() ;
    QString getNom() ;
    QString getemail() ;
    QString getdisponibilite() ;
    QString getnumero() ;
    QDate getDATE_DE_EMBAUCHE() ;
    QString getposte() ;
      QString getprenom() ;
    int getsalaire();
    QString getmessage(){return message;}
    // Setters
    void setID(int id);
    void setNom( QString nom);
 void setprenom( QString prenom);
    void setemail( QString email);
    void setnumero( QString numero);
    void setdisponibilite(QString disponibilite);
    void setsalaire( int salaire);
    void setDATE_DE_EMBAUCHE( QDate DATE_DE_EMBAUCHE);
    void setposte(QString poste);

void setmessage(QString message){this->message=message;}

    // CRUD
    bool ajouter();
    bool supprimer(int id);
    bool modifier(int id,  QString nom,  QString prenom, QString email,  int salaire,  QString numero,  QString poste,QString disponibilite,QDate DATE_DE_EMBAUCHE);
    QSqlQueryModel* afficher() ;
    // Méthodes auxiliaires
    bool EMPLOYEExists(int id) ;
    QSqlQueryModel* chercher(QString column,QString text)  ;
    QSqlQueryModel* tri(QString column) ;
    QSqlQueryModel* tri1(QString column);
    int countSalaire(const QString& min,const QString& max);

private:
    // Attributs
    int id,salaire;
    QString nom,prenom,email,numero,poste,disponibilite,message;
    QDate DATE_DE_EMBAUCHE;

};


#endif // EMPLOYE_H
