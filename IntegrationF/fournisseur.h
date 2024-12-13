#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDebug>

class Fournisseur
{
    QString type_f,type_p,nom,mail,adresse;
    int id,num_tel,id_produit ;

public:
    Fournisseur(){};
    Fournisseur(int,QString,int,QString,QString,QString,QString,int);

    int getId() {return id;}
    QString getNom() {return nom;}
    int getNum_tel(){return num_tel;}
    QString getMail() {return mail;}
    QString getAdresse() {return adresse;}
    QString getType_f() {return type_f;}
    QString getType_p() {return type_f;}
    int getid_produit() {return id_produit;}


    void setId (int c) {this->id=c;}
    void setNom (QString n) {nom=n;}
    void setNum_tel (int p) {num_tel=p;}
    void setMail (QString a) {mail=a;}
    void setAdresse (QString s) {adresse=s;}
    void setType_f (QString tf) {type_f=tf;}
    void setType_p (QString tp) {type_p=tp;}
    void setid_produit (int c) {this->id_produit=c;}

    bool validateNumTel() const;
    bool validateMail() const;
    bool validateTypeF() const;



    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer (int);
    bool  modifier(int);
    QSqlQueryModel * triID();
    QSqlQueryModel * triNOM();
    QSqlQueryModel * triMAIL();
    QSqlQueryModel* chercher( QString searchCriteria);
};

#endif // FOURNISSEUR_H
