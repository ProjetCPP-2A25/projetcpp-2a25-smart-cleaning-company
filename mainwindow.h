#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include <QSqlTableModel>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots :
    void on_bouton_clicked();
     void on_supprimer_clicked();



   // Déclaration du slot


     void on_bouton_modifier_clicked();

     void on_bt_tri_clicked();

     void on_bt_chercher_clicked();

     void on_refresh_clicked();

     void on_PDF_clicked();
     void stat();

     void on_tableView_clicked(const QModelIndex &index);

     void on_bt_envoyer_clicked();

private:
    Ui::MainWindow *ui;
    Clients etmp;
    // Ajoutez cette ligne dans la section privée de la classe MainWindow
    QSqlTableModel *model;


};
#endif // MAINWINDOW_H

