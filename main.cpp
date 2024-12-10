#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    // Créer une connexion à la base de données
    bool test = c.createconnect();
        MainWindow w;
    if (test) {
        // Si la connexion est réussie, afficher la fenêtre principale
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Base de données ouverte"),
                                 QObject::tr("Connexion réussie.\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    } else {
        // Si la connexion échoue, afficher un message d'erreur
        QMessageBox::critical(nullptr, QObject::tr("Base de données non ouverte"),
                              QObject::tr("Échec de la connexion.\n"
                                          "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }

    return a.exec();
};
