#ifndef PRODUIT_H
#define PRODUIT_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QDate>


class PRODUIT {
public:
     PRODUIT();
    PRODUIT(int id,  QString nom,  int prix, QString disponibilite,  QString image,  QDate DATE_DE_VALIDITE,  QString TYPE_DE_PRODUIT,int ID_F);
    // Getters
    int getId() ;
    QString getNom() ;
    int getprix() ;
    QString getdisponibilite() ;
    QString getimage() ;
    QDate getDATE_DE_VALIDITE() ;
    QString getTYPE_DE_PRODUIT() ;
    int getID_F();
    // Setters
    void setID(int id);
    void setNom( QString nom);

    void setID_F( int ID_F);
    void setprix( int prix);
    void setdisponibilite(QString disponibilite);
    void setimage( QString image);
    void setDATE_DE_VALIDITE( QDate DATE_DE_VALIDITE);
    void setTYPE_DE_PRODUIT(QString TYPE_DE_PRODUIT);


    // CRUD
    bool ajouter();
    bool supprimer(int id);
    bool modifier(int id,  QString nom,  int prix, QString disponibilite,  QString image,  QDate DATE_DE_VALIDITE,  QString TYPE_DE_PRODUIT,int ID_F);
    QSqlQueryModel* afficher() ;
    // Méthodes auxiliaires
    bool produitExists(int id) ;

    QSqlQueryModel* chercher(QString column,QString text);
    QSqlQueryModel* tri(QString column);
    QSqlQueryModel* tri1(QString column);
    int countType(const QString& type);


private:
    // Attributs
    int id;
    QString nom;
    int prix;
    QString disponibilite;
     QString image;
    QDate DATE_DE_VALIDITE;
    QString TYPE_DE_PRODUIT;
    int ID_F;
};



#endif // Produits_H
