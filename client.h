#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QSqlError>


class Clients
{
    QString nom,prenom,typeclient,adresse,typeservice,numtel;
    int idClient;

public:
    Clients(){};
    Clients( int idClient, QString nom, QString prenom ,QString typeservice, QString typeclient, QString adresse, QString numtel);
    QString getNom() const;
    QString getPrenom() const;
    QString getTypeservice() const;
    QString getTypeclient() const;
    QString getAdresse() const;
    int getIdClient() const;
    QString getNumtel() const;
    bool supprimer(int idClient);

       // Setters
    void setNom(const QString &nom);
    void setPrenom(const QString &prenom);
    void setTypeservice(const QString &typeservice);
    void setTypeclient(const QString &typeclient);
    void setAdresse(const QString &adresse);
    void setIdClient(int idClient);
    void setNumtel(QString numtel);
    bool ajouter();
    bool modifier();

    QSqlQueryModel * afficher();
    bool idExists(int id);

    QSqlQueryModel* tri(const QString&  column,const QString&  choix);



    QSqlQueryModel* chercher(QString column,QString text);
    int countService(const QString& service);


};

#endif // CLIENT_H
