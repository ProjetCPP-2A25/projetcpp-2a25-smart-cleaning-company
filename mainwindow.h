#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
#include "email.h"
#include "arduino.h"
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


    void on_bt_chercher_clicked();
    void GESTION_EMPLOYE_STATISTIQUE();

    void on_pdf_clicked();

    void on_b1_clicked();

    void on_b2_clicked();
    QString generateRandomCode(int length) ;

    void on_code_clicked();

    void on_valider_clicked();

    void on_bt_login_clicked();

    void on_menu_employe_clicked();

    void on_menu_client_clicked();
     void on_menu_fournisseur_clicked();
  void   on_menu_produit_clicked();
   void on_menu_materiel_clicked();
   void on_tableView_clicked(const QModelIndex &index);
   void fonction_arduino();

   void on_QUITTER_clicked();

private:
    Ui::MainWindow *ui;
    employe e;
    mailer emailSender;
    arduino A;
};
#endif // MAINWINDOW_H
