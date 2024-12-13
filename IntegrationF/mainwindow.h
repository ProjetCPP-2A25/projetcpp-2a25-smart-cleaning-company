#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "produit.h"
#include "arduino.h"
#include "client.h"
#include <QSqlTableModel>
#include "materiel.h"

#include "fournisseur.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

#include "employe.h"
#include "email.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_AJOUTER_clicked();

    void on_modifier_clicked();

    void on_bt_supprimer_clicked();

    void on_REFRESH_clicked();

    void on_tableView_clicked(const QModelIndex &index);


    void on_b1_clicked();
    void on_b2_clicked();


    void on_PDF_clicked();
    void GESTION_FORMATION_STATISTIQUE();

    void on_bt_chercher_clicked();

    void on_bt_inserer_clicked();

    void on_bt_historique_clicked();

    void on_Retour_clicked();

    void on_Retour_2_clicked();
    void fonction_arduino();

    void on_bouton_clicked();

    void on_supprimer_clicked();
    void genererStatistiquesMateriel(QSqlQueryModel* model);

    void on_ajouter_Materiel_clicked();

    void on_modifier_Materiel_clicked();

    void on_supression_Materiel_clicked();

    void on_recherche_clicked();

    void on_trier_Materiel_clicked();

    void on_btnExporterPDF_clicked();

    void on_mail_clicked();

    void on_qrcodegen_clicked();

    void on_statsButton_clicked();

    void on_qrcodegen_2_clicked();

    void on_ajouter_Materiel_3_clicked();

    void on_ajouter_Materiel_2_clicked();

    void on_ajouter_clicked();

    void on_modifier_2_clicked();

    void on_suprimer_2_clicked();

    void on_contrat_clicked();

    void on_getlocation_clicked();

    void on_bouton_modifier_clicked();

    void on_bt_tri_clicked();

    void on_bt_chercher_2_clicked();

    void on_refresh_clicked();

    void on_PDF_2_clicked();
    void stat_client();

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_bt_envoyer_clicked();

    void on_AJOUTER_2_clicked();

    void on_modifier_3_clicked();

    void on_bt_supprimer_2_clicked();

    void on_REFRESH_2_clicked();

    void on_bt_chercher_3_clicked();
    void GESTION_EMPLOYE_STATISTIQUE();

    void on_pdf_2_clicked();

    void on_b1_2_clicked();

    void on_b2_2_clicked();
    QString generateRandomCode(int length);

    void on_QUITTER_clicked();


    void on_tableView_4_clicked(const QModelIndex &index);

    void on_code_clicked();

    void on_valider_clicked();

    void on_bt_login_clicked();

    void on_Retour_3_clicked();

    void on_Retour_4_clicked();

    void on_Retour_5_clicked();

    void on_Retour_6_clicked();

    void on_Retour_7_clicked();

    void on_menu_employe_clicked();

    void on_menu_client_clicked();

    void on_menu_fournisseur_clicked();

    void on_menu_materiel_clicked();

    void on_menu_produit_clicked();

    void on_chercher_2_clicked();

    void on_chercher_3_clicked();

private:
    Ui::MainWindow *ui;
    PRODUIT p;
    arduino A;
    Clients etmp;
    // Ajoutez cette ligne dans la section privée de la classe MainWindow
    QSqlTableModel *model;
    Materiel materiel;
    arduino ard;

    //fournisseur
    Fournisseur Ctmp;
    QNetworkAccessManager *networkManager;
    employe e;
    mailer emailSender;
};
#endif // MAINWINDOW_H
