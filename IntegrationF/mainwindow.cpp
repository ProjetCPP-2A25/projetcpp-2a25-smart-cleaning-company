#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QTextStream>
#include <QFileInfo>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>

#include <QChartView>
#include <QChart>
#include <QPieSlice>
#include <QPieSeries>

#include <iostream>
#include <fstream>
#include <QFile>
#include <QStandardItem>

#include "fournisseur.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

#include "fournisseur.h"
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSlice>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QUrl>
#include <QNetworkRequest>
#include <QSslSocket>
#include "fournisseur.h"
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSlice>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QUrl>
#include <QNetworkRequest>
#include <QSslSocket>

#include "client.h"
#include <QMessageBox>
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>
#include <QPainter>
#include <QChartView>
#include <QPieSlice>
#include <QPieSeries>
#include <QList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSqlQuery>
#include "twiliomanager.h"
//#include <QWebEngineView>
using namespace  QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
ui->historique->hide();
ui->gestion_produit->show();
ui->tableView->setModel(p.afficher());
ui->IMAGES->show();




// Set a regular expression validator to allow only numbers
    QRegularExpression regex("^[0-9]+$"); // Regex for numbers only
    QRegularExpressionValidator *validator1 = new QRegularExpressionValidator(regex, this);
    ui->ID_PRODUIT->setValidator(validator1);
    ui->QUANTITE->setValidator(validator1);
    ui->PRIX->setValidator(validator1);
    ui->ID_FOURNISSEUR->setValidator(validator1);
    ui->line_supprimer->setValidator(validator1);



// Set a regular expression validator to allow only letters
    QRegularExpression regex1("^[A-Za-z]+$"); // Regex for letters only
    QRegularExpressionValidator *validator2 = new QRegularExpressionValidator(regex1, this);
    ui->NOM->setValidator(validator2);


GESTION_FORMATION_STATISTIQUE();


if (A.connect_arduino() == 0) {

          QMessageBox::information(this, "Port", A.getarduino_port_name());

      } else {

          QMessageBox::warning(this, "Erreur", "Échec de la connexion à l'Arduino.");

      }
      connect(A.get_serial(), &QSerialPort::readyRead, this, &MainWindow::fonction_arduino);






//materiel
         QDoubleValidator *prixValidator1 = new QDoubleValidator(0, 1000000, 2, this);
            prixValidator1->setNotation(QDoubleValidator::StandardNotation);
            ui->prix_materiel->setValidator(prixValidator1);

            // Validateur pour les entiers (durée de garantie, durée de vie, quantité)
            QIntValidator *intValidator1 = new QIntValidator(0, 100000, this);
            ui->duree_garantie_materiel->setValidator(intValidator1);
            ui->duree_de_vie_materiel->setValidator(intValidator1);
            ui->quantite_materiel->setValidator(intValidator1);
         // Connectez le bouton ajouter_materiel au slot on_ajouter_Materiel_clicked


//client
            ui->label->lower();
            ui->tableView_2->setModel(etmp.afficher());
            ui->tableView_2->setColumnWidth(6, 150);
            QSqlTableModel *model;
            model = new QSqlTableModel(this);
               model->setTable("FS_CLIENTS");
               model->select();  // Charger les données de la table
               ui->tableView_2->setModel(model);  // Associer le modèle à la vue
               ui->tableView_2->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
               stat_client();

 //employe
               ui->tableView_4->setModel(e.afficher());


               // Set a regular expression validator to allow only letters
                   QRegularExpression regex3("^[0-9]+$"); // Regex for letters only
                   QRegularExpressionValidator *validator3 = new QRegularExpressionValidator(regex3, this);
                   ui->ID_EMPLOYE->setValidator(validator3);
                   ui->SALAIRE->setValidator(validator3);
                   ui->DISPONIBILITE->setValidator(validator3);
                   ui->line_supprimer_2->setValidator(validator3);

               // Set a regular expression validator to allow only letters
                   QRegularExpression regex4("^[A-Za-z]+$"); // Regex for letters only
                   QRegularExpressionValidator *validator4 = new QRegularExpressionValidator(regex4, this);
                   ui->NOM_2->setValidator(validator4);
                   ui->PRENOM->setValidator(validator4);

                   GESTION_EMPLOYE_STATISTIQUE();


                   ui->login_mdp->setEchoMode(QLineEdit::Password);


                   ui->menu->hide();
                       ui->historique->hide();
                       ui->gestion_client->hide();
                       ui->gestion_employe->hide();
                       ui->gestion_produit->hide();
                       ui->gestion_fournisseur->hide();
                       ui->gestion_materiel->hide();
                       ui->login->show();
                       ui->menu->hide();

}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::fonction_arduino()
{
    QByteArray data = A.read_from_arduino();
    QString nb = QString::fromUtf8(data).trimmed(); // Convert data to QString
    //qDebug()<<nb;
if(nb!="*")
{
    A.code+=nb;
}
    else
{
    A.code.remove("*");
qDebug()<<A.code;
    QSqlQuery query;
    query.prepare("SELECT ID_P,NOM_P FROM PRODUITS WHERE ID_P = :code");
    query.bindValue(":code", A.code);

    if(query.exec() && query.next())
    {
        QString id=query.value(0).toString();
        QString nom=query.value(1).toString();
        QSqlQuery sql;
        sql.prepare("UPDATE PRODUITS SET ETAT='Disponible' WHERE ID_P=:code");
        sql.bindValue(":code", A.code);
        sql.exec();
//qDebug()<<nom;
        // Send each character to the Arduino
        for (QChar c : nom) {
                QByteArray byteArray;
                byteArray.append(c.toLatin1()); // Convert each character to QByteArray and append it
                A.write_to_arduino(byteArray);  // Send the byte to the Arduino
            }
       QByteArray byteArray1;
       byteArray1.append("*"); // Convert each character to QByteArray and append i
        A.write_to_arduino(byteArray1);  // Send the byte to the Arduino

        QMessageBox::information(this, "Succès", "Le id existe et le nom a été envoyé !");
A.code="";
    }
    else
    {
        QMessageBox::warning(this, "", "Le id n'existe pas!");
        A.code="";

    }


}
}
void MainWindow::on_AJOUTER_clicked()
{
//compteur
int c=0;
// Récupération des valeurs depuis l'interface utilisateur
   int id = ui->ID_PRODUIT->text().toInt();  // Assurez-vous d'avoir un champ pour l'ID
   QString nom = ui->NOM->text();
   int PRIX = ui->PRIX->text().toInt();
   QString QUANTITE = ui->QUANTITE->text();
   QString IMAGES = ui->IMAGES->text();
      QDate date = ui->DATE->date();
   int ID_FOURNISSEUR = ui->ID_FOURNISSEUR->text().toInt();
QString TYPE=ui->TYPE->currentText();

if(p.produitExists(id))
{
c++;
QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                      QObject::tr("id déja existe"), QMessageBox::Cancel);
}
if(ui->ID_PRODUIT->text().isEmpty() || nom.isEmpty() || ui->PRIX->text().isEmpty() || QUANTITE.isEmpty() ||IMAGES.isEmpty() ||ui->ID_FOURNISSEUR->text().isEmpty() )
{
c++;
QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                      QObject::tr("tu dois remplir tous les champs"), QMessageBox::Cancel);
}
if(c==0)
{       // Création de l'objet produit avec les attributs correspondants
PRODUIT p(id, nom, PRIX, QUANTITE,IMAGES, date,TYPE, ID_FOURNISSEUR);

   // Tente d'ajouter le produit  à la base de données
   bool insertionSuccess = p.ajouter();
   QMessageBox messageBox;

   if (insertionSuccess)
   {
       messageBox.setText("Données ajoutées à la base de données avec succès !");

       // Réinitialisez les champs de saisie
       ui->ID_PRODUIT->clear();
       ui->NOM->clear();
       ui->PRIX->clear();
       ui->QUANTITE->clear();
       ui->IMAGES->clear();
       ui->ID_FOURNISSEUR->clear();
        ui->tableView->setModel(p.afficher());

        //write to the file
QFile file("/Users/USER/Documents/produit/ajout.txt");
if(file.open(QIODevice::Append|QIODevice::Text))
{
QTextStream stream(&file);
stream <<"ID added : " <<",Time:"<<QDateTime::currentDateTime().toString()<<endl;
file.close();
}
   }
   else
   {
       messageBox.setText("Échec de l'ajout des données dans la base de données.");
   }
   messageBox.exec();
}
}

void MainWindow::on_modifier_clicked()
{
//compteur
int c=0;
// Récupération des valeurs depuis l'interface utilisateur
   int id = ui->ID_PRODUIT->text().toInt();  // Assurez-vous d'avoir un champ pour l'ID
   QString nom = ui->NOM->text();
   int PRIX = ui->PRIX->text().toInt();
   QString QUANTITE = ui->QUANTITE->text();
   QString IMAGES = ui->IMAGES->text();
      QDate dateEmbauche = ui->DATE->date();
   int ID_FOURNISSEUR = ui->ID_FOURNISSEUR->text().toInt();
QString TYPE=ui->TYPE->currentText();

if(!p.produitExists(id))
{
c++;
QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                      QObject::tr("id n' existe pas"), QMessageBox::Cancel);
}
if(ui->ID_PRODUIT->text().isEmpty() || nom.isEmpty() || ui->PRIX->text().isEmpty() || QUANTITE.isEmpty() ||IMAGES.isEmpty() ||ui->ID_FOURNISSEUR->text().isEmpty() )
{
c++;
QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                      QObject::tr("tu dois remplir tous les champs"), QMessageBox::Cancel);
}




if(c==0)
{       // Création de l'objet produit avec les attributs correspondants


   // Tente d'ajouter le produit à la base de données
   bool insertionSuccess = p.modifier(id, nom, PRIX, QUANTITE,IMAGES, dateEmbauche,TYPE, ID_FOURNISSEUR);
   QMessageBox messageBox;

   if (insertionSuccess)
   {
       messageBox.setText("Données ajoutées à la base de données avec succès !");

       // Réinitialisez les champs de saisie
       ui->ID_PRODUIT->clear();
       ui->NOM->clear();
       ui->PRIX->clear();
       ui->QUANTITE->clear();
       ui->IMAGES->clear();
       ui->ID_FOURNISSEUR->clear();
        ui->tableView->setModel(p.afficher());
        //write to the file
QFile file("/Users/USER/Documents/produit/modification.txt");
if(file.open(QIODevice::Append|QIODevice::Text))
{
QTextStream stream(&file);
stream <<"ID UPDATED : " <<",Time:"<<QDateTime::currentDateTime().toString()<<endl;
file.close();
}
   }
   else
   {
       messageBox.setText("Échec de l'ajout des données dans la base de données.");
   }
   messageBox.exec();
}

}

void MainWindow::on_bt_supprimer_clicked()
{
    int id=ui->line_supprimer->text().toInt();
    if (p.produitExists(id)==false) {
        QMessageBox::warning(this,"","Erreur","id n'existe pas");
        ui->line_supprimer->clear();

       }
    else
    {
    if(p.produitExists(id)){
        bool test =p.supprimer(id);
        QMessageBox msgBox;
        if(test)
        {
            QMessageBox::warning(this, "", "suppression avec succés");
     ui->line_supprimer->clear();
     ui->tableView->setModel(p.afficher());
     //write to the file
QFile file("/Users/USER/Documents/produit/suppression.txt");
if(file.open(QIODevice::Append|QIODevice::Text))
{
QTextStream stream(&file);
stream <<"ID DELETED : " <<",Time:"<<QDateTime::currentDateTime().toString()<<endl;
file.close();
}
        } else
        {
          QMessageBox::warning(this,"", "Erreur", "Échec de suppression du produit.");
          ui->line_supprimer->clear();
        }}
   }
    }


void MainWindow::on_REFRESH_clicked()
{
    ui->tableView->setModel(p.afficher());
    GESTION_FORMATION_STATISTIQUE();

}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
          QString val = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();
          QSqlQuery qry;
               qry.prepare("select * from PRODUITS where ID_P='" + val + "'");

               if (qry.exec()) {
                   while (qry.next()) {
                       QString id = qry.value(0).toString();
                       QString nom = qry.value(1).toString();
                       QString prix = qry.value(2).toString();
                         QString disponibilite = qry.value(3).toString();
                         QString IMAGES = qry.value(4).toString();
                         QDate DATE_VALIDETE = qry.value(5).toDate();
                         QString TYPE = qry.value(6).toString();
                         QString ID_F = qry.value(7).toString();

                         ui->ID_PRODUIT->setText(id);
                         ui->NOM->setText(nom);
                         ui->PRIX->setText(prix);
                         ui->QUANTITE->setText(disponibilite);
                         ui->IMAGES->setText(IMAGES);
                         ui->ID_FOURNISSEUR->setText(ID_F);
                                 ui->TYPE->setCurrentText(TYPE);
                                 ui->DATE->setDate(DATE_VALIDETE);

                                 // Load the image from the file path
                                 QPixmap image(IMAGES);
                                 ui->image->setPixmap(image.scaled(ui->image->size(), Qt::KeepAspectRatio));

                   }
               }
}



// mainwindow.cpp







void MainWindow::on_PDF_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out << "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           "<title>Liste des PRODUITS</title>\n"
           "<style>\n"
           "table {\n"
           "    width: 100%;\n"
           "    border-collapse: collapse;\n"
           "}\n"
           "th, td {\n"
           "    padding: 8px;\n"
           "    text-align: left;\n"
           "    border-bottom: 1px solid #ddd;\n"
           "}\n"
           "tr:nth-child(even) {\n"
           "    background-color: #f2f2f2;\n"
           "}\n"
           "</style>\n"
           "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<center><H1>Liste des PRODUITS</H1></center><br/><br/>\n"
           // Correct image path using file:/// for local file
           "<img src='file:///C:/Users/USER/Documents/produit/img.png' width='300' height='200'><br/><br/>\n"
           "<table>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
    {
        if (!ui->tableView->isColumnHidden(column))
        {
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr> <td>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView->isColumnHidden(column))
            {
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }

    out << "</table>\n</body>\n</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This line adjusts the page size
    doc.print(&printer);
}

void MainWindow::GESTION_FORMATION_STATISTIQUE()
{
    QList<QWidget*> childWidgets = ui->stat->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();

        }
        //the clear didnt work, but my goal is when i second click this button it deleted old chart and renders a new one
        ui->stat->clear();
        ui->stat->hide();

    int s0, s1,s2;

    s0 = p.countType("AeroFresh");
    s1 = p.countType("FlexiCleaner");
    s2 = p.countType("EcoSpray");




    int total = s0 + s1 + s2  ;
    // Calculate percentages
        float x = (total != 0) ? (s0 * 100.0f) / total : 0.0f; //if(total!=0)  x=x0+100.0f /total else x=0.0f
        float x1 = (total != 0) ? (s1 * 100.0f) / total : 0.0f;
        float x2 = (total != 0) ? (s2 * 100.0f) / total : 0.0f;


        // Adjust the percentages to ensure they sum up to 100%
        float totalPercentage = x + x1+ x2  ;
        if (totalPercentage != 100.0f && total != 0) {
            float correction = 100.0f - totalPercentage;
            x += correction;  // Apply correction to one of the slices (usually the largest one)
        }



//qDebug() <<  x <<endl;
// 3 jour  33.00 %
    QString ch1 = QString("AeroFresh %1%").arg(QString::number(x, 'f', 2));
    QString ch2 = QString("FlexiCleaner %2%").arg(QString::number(x1, 'f', 2));
    QString ch3 = QString("EcoSpray %3%").arg(QString::number(x2, 'f', 2));





    QPieSeries *series=new QPieSeries();
    series->setHoleSize(0.35);

    QPieSlice *slice= series->append(ch1,x);
    slice->setLabelVisible();
    slice->setLabelColor(QColor(Qt::white));
        slice->setBrush(QColor(189, 76, 224, 1));//changer couleur

    QPieSlice *slice1= series->append(ch2,x1);
    slice1->setLabelVisible();
    slice1->setLabelColor(QColor(Qt::white));
    slice1->setBrush(QColor(84, 16, 149, 1));

    QPieSlice *slice2= series->append(ch3,x2);
    slice2->setLabelVisible();

    slice2->setLabelColor(QColor(Qt::white));
    slice2->setBrush(QColor(119, 82, 254));




    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBrush backgroundBrush(QColor(187,93,87,0));
    chart->setBackgroundBrush(backgroundBrush);
    QChartView *chartview=new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setFixedSize(ui->stat->size());
    chartview->setParent(ui->stat);
    ui->stat->setStyleSheet("background:transparent; color:white; ");
    ui->stat->show();

}



void MainWindow::on_b1_clicked()
{
    QString text=ui->combo_tri->currentText();
        // Appeler la fonction tri() avec la colonne sélectionnée dans le QComboBox
        if (text == "ID") {
            ui->tableView->setModel(p.tri("ID_P"));
        }
        else if (text == "NOM") {
            ui->tableView->setModel(p.tri("NOM_P"));
        }
        else if (text == "QUANTITE") {
            ui->tableView->setModel(p.tri("DISPONIBILITE"));
        }
        else if (text == "PRIX") {
            ui->tableView->setModel(p.tri("PRIX"));
        }
        else if (text == "DATE_DE_VALIDITE") {
            ui->tableView->setModel(p.tri("DATE_DE_VALIDITE"));
        }
        else {
            ui->tableView->setModel(p.afficher());  // Affiche toutes les données si aucune option sélectionnée
        }

}

void MainWindow::on_b2_clicked()
{
    QString text=ui->combo_tri->currentText();
        // Appeler la fonction tri() avec la colonne sélectionnée dans le QComboBox
        if (text == "ID") {
            ui->tableView->setModel(p.tri1("ID_P"));
        }
        else if (text == "NOM") {
            ui->tableView->setModel(p.tri1("NOM_P"));
        }
        else if (text == "QUANTITE") {
            ui->tableView->setModel(p.tri1("DISPONIBILITE"));
        }
        else if (text == "PRIX") {
            ui->tableView->setModel(p.tri1("PRIX"));
        }
        else if (text == "DATE_DE_VALIDITE") {
            ui->tableView->setModel(p.tri1("DATE_DE_VALIDITE"));
        }
        else {
            ui->tableView->setModel(p.afficher());  // Affiche toutes les données si aucune option sélectionnée
        }
}

void MainWindow::on_bt_chercher_clicked()
{
   QString text= ui->chercher->text();
    QString choix =ui->combo_chercher->currentText();
    if(choix=="ID")
    {
        ui->tableView->setModel(p.chercher("ID_P",text));

    }
    else
    {
     if(choix=="NOM")
    {
         ui->tableView->setModel(p.chercher("NOM_P",text));

     }
     if(choix=="TYPE PRODUIT")
    {
         ui->tableView->setModel(p.chercher("TYPE_DE_PRODUIT",text));

     }
    else
     {
         ui->tableView->setModel(p.afficher());

     }
    }
}

void MainWindow::on_bt_inserer_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp *.gif)");

    if (!imagePath.isEmpty()) {
        // Load the image using QPixmap
        QPixmap image(imagePath);

        // Update the QLabel with the image
        ui->image->setPixmap(image.scaled(ui->image->size(), Qt::KeepAspectRatio));
        ui->IMAGES->setText(imagePath);
        ui->IMAGES->hide();
    }
}




void MainWindow::on_bt_historique_clicked()
{
QString selectedOption=ui->combo_historique->currentText();
QString filePath;
QString modelHeader;
if(selectedOption=="Ajout")
{
    filePath="/Users/USER/Documents/produit/ajout.txt";
    modelHeader="AJOUT";
}
else if(selectedOption=="Modifier")
{

    filePath="/Users/USER/Documents/produit/modification.txt";
    modelHeader="MODIFICATION";
}
else if(selectedOption=="Supprimer")
{

    filePath="/Users/USER/Documents/produit/suppression.txt";
    modelHeader="SUPPRESSION";
}
QFile file(filePath);
if(file.open(QIODevice::ReadOnly | QIODevice::Text))
{
QTextStream stream(&file);
QString fileContent=stream.readAll();
file.close();
if(fileContent.isEmpty())
{
    QMessageBox::information(this,"Empty","The file is empty");

}
else
{
    QStringList rows=fileContent.split("\n");
    QStandardItemModel *model=new QStandardItemModel(this);
    model->setColumnCount(1);
    for(const QString &row :rows)
    {
        QStandardItem *item= new QStandardItem(row);
model->appendRow(item);
    }

model->setHeaderData(0,Qt::Horizontal,QObject::tr(modelHeader.toUtf8().constData()));
ui->tableView_historique->setModel(model);
ui->tableView_historique->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}}
else {
    QMessageBox::warning(this,"Error","Failed to open the file.");

}
}




void MainWindow::on_Retour_clicked()
{
    ui->historique->hide();
    ui->gestion_produit->show();
}

void MainWindow::on_Retour_2_clicked()
{
    ui->gestion_produit->hide();
    ui->historique->show();
}

void MainWindow::on_bouton_clicked()
{

    int idClient = ui->lineEdit_idClient->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString typeservice = ui->lineEdit_typeservice->currentText();
    QString typeclient = ui->lineEdit_typeclient->text();
    QString adresse = ui->lineEdit_adresse->text();
    QString numtel = ui->lineEdit_numtel->text();

    // Vérification de l'existence du client avant l'ajout
 if(etmp.idExists(idClient))
 {
     QMessageBox::warning(this, tr("Erreur dans le id"), tr("le id deja existe"));

return;
 }


    // Vérification des champs
    if (nom.isEmpty() || prenom.isEmpty() || typeservice.isEmpty() || typeclient.isEmpty() || adresse.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"), tr("Veuillez remplir tous les champs !"));
        ui->tableView_2->setModel(etmp.afficher());  // Rafraîchir le tableau
        return;  // Arrêter l'exécution si un champ est vide
    }

    // Vérifications des saisies
    if (idClient <= 0 || numtel.length() <= 0 || nom.length() < 2 || prenom.length() < 2) {
        QMessageBox::warning(this, tr("Erreur de saisie"), tr("Données invalides !"));
        ui->tableView_2->setModel(etmp.afficher());  // Rafraîchir le tableau
        return;  // Arrêter l'exécution si une des vérifications échoue
    }

    // Ajout du client
    Clients C(idClient, nom, prenom, typeservice, typeclient, adresse, numtel);
    bool test = C.ajouter();
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectué !"));
    if (test==false) {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Ajout non effectué !"));
    }

    // Rafraîchir le tableau après l'ajout (réussi ou non)
    ui->tableView_2->setModel(etmp.afficher());
    stat_client();
} }


void MainWindow::on_supprimer_clicked()
{
    int idClient = ui->lineEdit_ids->text().toInt(); // Récupérer l'ID saisi


    // Appeler la méthode supprimer
    bool test = etmp.supprimer(idClient);
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectuée \n""Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Suppression non effectuée. \n ID non existant \n""Click Cancel to exit."), QMessageBox::Cancel);
    }
    ui->tableView_2->setModel(etmp.afficher());
    stat_client();
 }
void MainWindow::genererStatistiquesMateriel(QSqlQueryModel* model)
{
    QPieSeries *series = new QPieSeries();

    qreal totalPrix = 0;
    qreal totalQuantite = 0;

    // Calculer les totaux
    for (int row = 0; row < model->rowCount(); ++row) {
        qreal prix = model->data(model->index(row, 4)).toDouble(); // Colonne du prix
        qreal quantite = model->data(model->index(row, 6)).toDouble(); // Colonne de la quantité disponible

        totalPrix += prix;
        totalQuantite += quantite;
    }

    if (totalPrix > 0) {
        series->append("Prix total (" + QString::number(totalPrix, 'f', 2) + ")", totalPrix);
    }
    if (totalQuantite > 0) {
        series->append("Quantité totale (" + QString::number(totalQuantite, 'f', 0) + ")", totalQuantite);
    }

    // Créer le graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des matériels par prix et quantité disponible");
    chart->legend()->setAlignment(Qt::AlignRight);

    // Définir les polices
    QFont font;
    font.setPixelSize(16);
    chart->setTitleFont(font);
    chart->legend()->setFont(font);

    // Afficher le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(800, 600);
    chartView->show();
}


void MainWindow::on_ajouter_Materiel_clicked()
{
    // Gather data from the UI fields
    int id = ui->id_materiel->text().toInt();
    QString nom = ui->nom_materiel->text();
    QString etat = ui->etat_materiel->text();
    QString date_achat = ui->date_achat_materiel->text();
    int duree_garantie = ui->duree_garantie_materiel->text().toInt();
    double prix = ui->prix_materiel->text().toDouble();
    int quantite_disponible = ui->quantite_materiel->text().toInt();
    int duree_de_vie = ui->duree_de_vie_materiel->text().toInt();
    // Validate fields
    if (nom.isEmpty()) {
           QMessageBox::warning(this, tr("Validation Error"), tr("Le nom du matériel ne peut pas être vide."));
           return;
       }
       if (etat.isEmpty()) {
           QMessageBox::warning(this, tr("Validation Error"), tr("L'état du matériel ne peut pas être vide."));
           return;
       }
       if (date_achat.isEmpty()) {
           QMessageBox::warning(this, tr("Validation Error"), tr("La date d'achat ne peut pas être vide."));
           return;
       }
    // Create a Materiel object with the collected data
    Materiel materiel(id, nom, etat, date_achat, duree_garantie, prix, quantite_disponible, duree_de_vie);
    ui->id_materiel->clear();
          ui->nom_materiel->clear();
          ui->etat_materiel->clear();
          ui->date_achat_materiel->clear();
          ui->duree_garantie_materiel->clear();
          ui->prix_materiel->clear();
          ui->quantite_materiel->clear();
          ui->duree_de_vie_materiel->clear();
    // Attempt to add the material to the database
    if (materiel.ajouter()) {
        // Refresh the table view to show the new entry
        ui->affichage->setModel(materiel.afficher());
        QMessageBox::information(this, tr("Success"), tr("Material added successfully."));
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Failed to add material. The ID might already exist."));
    }
}

void MainWindow::on_modifier_Materiel_clicked()
{
    // Retrieve data from the input fields and convert them to appropriate types
    int id = ui->id_materiel->text().toInt();
    QString nom = ui->nom_materiel->text();
    QString etat = ui->etat_materiel->text();
    QString date_achat = ui->date_achat_materiel->text();
    QString duree_garantie = ui->duree_garantie_materiel->text();
    double prix = ui->prix_materiel->text().toDouble();
    int quantite_disponible = ui->quantite_materiel->text().toInt();
    int duree_de_vie = ui->duree_de_vie_materiel->text().toInt();

    // Log input values for debugging
    qDebug() << "Attempting modification with ID:" << id;
    qDebug() << "New values - Nom:" << nom << ", Etat:" << etat
             << ", Date d'achat:" << date_achat << ", Durée de garantie:" << duree_garantie
             << ", Prix:" << prix << ", Quantité disponible:" << quantite_disponible
             << ", Durée de vie:" << duree_de_vie;
    ui->id_materiel->clear();
          ui->nom_materiel->clear();
          ui->etat_materiel->clear();
          ui->date_achat_materiel->clear();
          ui->duree_garantie_materiel->clear();
          ui->prix_materiel->clear();
          ui->quantite_materiel->clear();
          ui->duree_de_vie_materiel->clear();

    // Create a Materiel object with the updated information
   Materiel materiel(id, nom, etat, date_achat, duree_garantie.toInt(), prix, quantite_disponible, duree_de_vie);
    // Attempt to modify the material record and log the result
    bool test = materiel.modifier(id);
    qDebug() << "Modifier function result:" << test;

    // Display a message based on the success of the modification
    if (test) {
        // Refresh the table view to reflect changes
        ui->affichage->setModel(materiel.afficher());
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée\nCliquez sur Cancel pour quitter."),
                                 QMessageBox::Cancel);
    } else {
       QMessageBox::critical(this, QObject::tr("Erreur"),
                            QObject::tr("La modification n'a pas pu être effectuée.\nCliquez sur Cancel pour quitter."),
                           QMessageBox::Cancel);
    }
}

void MainWindow::on_supression_Materiel_clicked()
{

    // Convert the text from the id_supp field to an integer
    int id = ui->id_supp->text().toInt();

    // Create a Materiel object and set its ID for deletion
    Materiel materiel;
    materiel.setId(id);

    // Call the supprimer() method of the Materiel object
    bool test = materiel.supprimer(materiel.getId());

    // Display a message based on the success of the deletion
    if (test) {
        // Refresh the table view only if the deletion succeeded
        ui->affichage->setModel(materiel.afficher());
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\n"
                                             "Cliquez sur Annuler pour quitter."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée. Assurez-vous que l'ID existe.\n"
                                          "Cliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
    ui->id_materiel->clear();
          ui->nom_materiel->clear();
          ui->etat_materiel->clear();
          ui->date_achat_materiel->clear();
          ui->duree_garantie_materiel->clear();
          ui->prix_materiel->clear();
          ui->quantite_materiel->clear();
          ui->duree_de_vie_materiel->clear();
}

void MainWindow::on_recherche_clicked()
{
    // Get the search query (either id or nom)
    QString GA_searchParam = ui->comboBox_rech->currentText();
    QString searchQuery = ui->id_rech->text();

    // Create a Materiel object to perform the search
    Materiel materiel;

    // Call the rechercher function
    QSqlQueryModel* model = materiel.rechercher(searchQuery);

    // Display the search results in the table view
    ui->affichage->setModel(model);
}


void MainWindow::on_trier_Materiel_clicked()
{
    QString GA_sortParam = ui->comboBox_trie->currentText(); // Get the selected sort parameter

    QSqlQueryModel *sortedModel = new QSqlQueryModel();

    if (GA_sortParam == "Etat") {
        // Tri de l'état en ordre alphabétique de A à Z
        sortedModel->setQuery("SELECT * FROM Materiel ORDER BY etat ASC");
    } else if (GA_sortParam == "Date d'achat") {
        // Tri des dates d'achat de la première date à la dernière date (ordre croissant)
        sortedModel->setQuery("SELECT * FROM Materiel ORDER BY date_achat ASC");
    } else {
        QMessageBox::warning(this, "Erreur", "Paramètre de tri non valide.");
        return;
    }

    ui->affichage->setModel(sortedModel);
}

void MainWindow::on_btnExporterPDF_clicked()
{

    // Boîte de dialogue pour choisir l'emplacement d'enregistrement
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer sous", "", "Fichiers CSV (*.csv)");

    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun emplacement sélectionné pour l'exportation.");
        return;
    }

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        // Écrire les en-têtes des colonnes
        out << "\"id\",\"nom\",\"etat\",\"date_achat\",\"quantite_disponible\",\"duree_de_vie\",\"duree_garantie\",\"prix\"\n";

        // Préparer la requête pour récupérer les données de matériel
        QSqlQuery query;
        query.prepare("SELECT id, nom, etat, date_achat, quantite_disponible, duree_de_vie, duree_garantie, prix FROM materiel");

        // Exécuter la requête et écrire chaque ligne dans le fichier CSV
        if (query.exec()) {
            while (query.next()) {
                int id = query.value("id").toInt();
                QString nom = query.value("nom").toString();
                QString etat = query.value("etat").toString();
                QString date_achat = query.value("date_achat").toString();
                int quantite_disponible = query.value("quantite_disponible").toInt();
                int duree_de_vie = query.value("duree_de_vie").toInt();
                int duree_garantie = query.value("duree_garantie").toInt();
                double prix = query.value("prix").toDouble();

                out << "\"" << id << "\","
                    << "\"" << nom << "\","
                    << "\"" << etat << "\","
                    << "\"" << date_achat << "\","
                    << "\"" << quantite_disponible << "\","
                    << "\"" << duree_de_vie << "\","
                    << "\"" << duree_garantie << "\","
                    << "\"" << prix << "\"\n";
            }
            QMessageBox::information(this, "Exportation réussie", "Les données ont été exportées avec succès en CSV.");
        } else {
            QMessageBox::warning(this, "Erreur", "Échec de la récupération des données de matériel : " + query.lastError().text());
        }

        file.close();
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier pour l'écriture.");
    }
}

void MainWindow::on_mail_clicked()
{
    QString serveur = "smtp.gmail.com";
                 int port = 587; // Port pour SMTP avec STARTTLS

                 // Informations de l'expéditeur et du destinataire
                 QString expediteur = "amal.gharssa2501@gmail.com";
                 QString destinataire = ui->dest->text();

                 QString subject = "Alerte de Stock";

                 // Détails du message
                  QString corps = "Le stock a atteint le seuil minimal veuillez vous le consulter le plut tot possible ";

                 // Connexion au serveur SMTP
                 QSslSocket socket;
                 socket.connectToHost(serveur, port);
                 if (!socket.waitForConnected()) {
                     qDebug() << "Échec de connexion au serveur SMTP:" << socket.errorString();
                     return;
                 }

                 // Attente de la réponse du serveur
                 if (!socket.waitForReadyRead()) {
                     qDebug() << "Délai d'attente de réponse du serveur SMTP:" << socket.errorString();
                     return;
                 }
                 qDebug() << socket.readAll(); // Afficher la réponse initiale du serveur

                 // Envoi de la commande EHLO
                 socket.write("EHLO localhost\r\n");
                 if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                     qDebug() << "Délai d'attente de réponse du serveur SMTP (EHLO):" << socket.errorString();
                     return;
                 }
                 qDebug() << socket.readAll(); // Afficher la réponse après EHLO

                 // Envoi de la commande STARTTLS
                 socket.write("STARTTLS\r\n");
                 if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                     qDebug() << "Délai d'attente de réponse du serveur SMTP (STARTTLS):" << socket.errorString();
                     return;
                 }
                 qDebug() << socket.readAll(); // Afficher la réponse après STARTTLS

                 // Démarrer le chiffrement
                 socket.startClientEncryption();
                 if (!socket.waitForEncrypted()) {
                     qDebug() << "Échec du chiffrement:" << socket.errorString();
                     return;
                 }

                 // Envoi de la commande AUTH LOGIN
                 socket.write("AUTH LOGIN\r\n");
                 if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                     qDebug() << "Délai d'attente de réponse du serveur SMTP (AUTH LOGIN):" << socket.errorString();
                     return;
                 }
                 qDebug() << socket.readAll(); // Afficher la réponse après AUTH LOGIN

                 // Envoi du nom d'utilisateur encodé en Base64
                 socket.write(QByteArray().append(expediteur.toUtf8()).toBase64() + "\r\n");
                 if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                     qDebug() << "Délai d'attente de réponse du serveur SMTP (Nom d'utilisateur):" << socket.errorString();
                     return;
                 }
                 qDebug() << socket.readAll(); // Afficher la réponse après l'envoi du nom d'utilisateur

                 // Envoi du mot de passe encodé en Base64
                 socket.write(QByteArray().append("tueg fvoq uzdt pcow").toBase64() + "\r\n");
                 if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                     qDebug() << "Échec de l'authentification SMTP (Mot de passe):" << socket.errorString();
                     return;
                 }
                 qDebug() << socket.readAll(); // Afficher la réponse après l'envoi du mot de passe

                 // Envoi de la commande MAIL FROM
                 socket.write("MAIL FROM:<" + expediteur.toUtf8() + ">\r\n");
                 if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                     qDebug() << "Délai d'attente de réponse du serveur SMTP (MAIL FROM):" << socket.errorString();
                     return;
                 }
                 qDebug() << socket.readAll(); // Afficher la réponse après MAIL FROM

                 // Envoi de la commande RCPT TO
                 socket.write("RCPT TO:<" + destinataire.toUtf8() + ">\r\n");
                 if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                     qDebug() << "Délai d'attente de réponse du serveur SMTP (RCPT TO):" << socket.errorString();
                     return;
                 }
                 qDebug() << socket.readAll(); // Afficher la réponse après RCPT TO

                 // Envoi de la commande DATA
                 socket.write("DATA\r\n");
                 if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                     qDebug() << "Délai d'attente de réponse du serveur SMTP (DATA):" << socket.errorString();
                     return;
                 }
                 qDebug() << socket.readAll(); // Afficher la réponse après DATA

                 // Envoi des en-têtes et du corps du message
                 socket.write("From: " + expediteur.toUtf8() + "\r\n");
                 socket.write("To: " + destinataire.toUtf8() + "\r\n");
                 socket.write("Subject: " + subject.toUtf8() + "\r\n");
                 socket.write("\r\n");
                 socket.write(corps.toUtf8() + "\r\n");
                 socket.write(".\r\n");
                 if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                     qDebug() << "Échec d'envoi des données du mail:" << socket.errorString();
                     return;
                 }
                 qDebug() << socket.readAll(); // Afficher la réponse après l'envoi des données du mail

                 // Envoi de la commande QUIT
                 socket.write("QUIT\r\n");
                 if (!socket.waitForBytesWritten()) {
                     qDebug() << "Échec d'envoi de la commande QUIT:" << socket.errorString();
                     return;
                 }

                 // Fermeture de la connexion
                 socket.close();
                 QMessageBox::information(this, "Succès", "L'email a été envoyé avec succès à " + destinataire);

}

#include "qrcodegen.h"
void MainWindow::on_qrcodegen_clicked()
{
    // Obtenez le modèle de sélection de la QTableView
    QItemSelectionModel *selectionModel = ui->affichage->selectionModel();
    if (!selectionModel->hasSelection()) {
        QMessageBox::warning(this, "No Selection", "Please select a supplier first.");
        return;
    }

    // Obtenez l'index de la ligne sélectionnée
    QModelIndex selectedIndex = selectionModel->currentIndex();
    int selectedRow = selectedIndex.row();

    // Obtenez le modèle associé à la QTableView
    QAbstractItemModel *model = ui->affichage->model();

    // Récupérer les informations ID, nom, état, durée/quantité, et prix à partir des colonnes correspondantes
    QString id = model->data(model->index(selectedRow, 0)).toString();  // Colonne 0 : ID
    QString nom = model->data(model->index(selectedRow, 1)).toString(); // Colonne 1 : Nom
    QString etat = model->data(model->index(selectedRow, 2)).toString(); // Colonne 2 : État
    QString dureeQuantite = model->data(model->index(selectedRow, 4)).toString(); // Colonne 4 : Durée/Quantité
    QString prix = model->data(model->index(selectedRow, 5)).toString(); // Colonne 5 : Prix

    // Vérifier que les informations sont valides
    if (id.isEmpty() || nom.isEmpty() || etat.isEmpty() || dureeQuantite.isEmpty() || prix.isEmpty()) {
        QMessageBox::warning(this, "Invalid Data", "Some required information is missing for the selected item.");
        return;
    }

    // Créer une chaîne de texte avec les informations pour le QR code
    QString qrData = QString("ID: %1\nNom: %2\nÉtat: %3\nDurée: %4\nPrix: %5")
                         .arg(id, nom, etat, dureeQuantite, prix);

    // Générer le QR code
    using namespace qrcodegen;
    QrCode qr = QrCode::encodeText(qrData.toUtf8().data(), QrCode::Ecc::MEDIUM);
    int sz = qr.getSize();
    QImage im(sz, sz, QImage::Format_RGB32);
    QRgb black = qRgb(0, 0, 0);
    QRgb white = qRgb(255, 255, 255);

    // Remplir l'image du QR code avec les modules (pixels)
    for (int y = 0; y < sz; y++) {
        for (int x = 0; x < sz; x++) {
            im.setPixel(x, y, qr.getModule(x, y) ? black : white);
        }
    }

    // Afficher le QR code dans qrcodeLabel
    ui->qrcodeLabel->setPixmap(QPixmap::fromImage(im.scaled(125, 125, Qt::KeepAspectRatio, Qt::FastTransformation)));
}

void MainWindow::on_statsButton_clicked()
{
    QSqlQueryModel* model= materiel.afficher();
    MainWindow::genererStatistiquesMateriel(model);
}

void MainWindow::on_qrcodegen_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_ajouter_Materiel_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_ajouter_Materiel_2_clicked()
{

        QSqlQuery query=materiel.prendre(ui->id_materiel_2->text().toInt());
            qDebug()<<QDate::fromString(query.value(0).toString(),"dd/MM/yyyy").daysTo(QDate::currentDate());

        if(QDate::fromString(query.value(0).toString(),"dd/MM/yyyy").daysTo(QDate::currentDate())>query.value(1).toString().toInt())
        {
            QMessageBox::information(this, "Garantie", "La durée de garantie est terminée !");

            QString chr="ssss";
            ard.write_to_arduino(chr.toUtf8());
        } else {
               QMessageBox::information(this, "Garantie", "La durée de garantie est encore disponible !");
           }


}

void MainWindow::on_ajouter_clicked()
{
    int ID = ui->ID->text().toInt();
    QString NOM = ui->nom->text();
    int NUM_TEL = ui->num->text().toInt();
    QString MAIL = ui->mail_2->text();
    QString ADRESSE = ui->adresse->text();
    QString TYPE_F = ui->typef->text();
    QString TYPE_P = ui->typep->text();
    int ID_PRODUIT = ui->prod->text().toInt();
    Fournisseur f(ID, NOM, NUM_TEL, MAIL, ADRESSE, TYPE_F, TYPE_P, ID_PRODUIT);
    bool test = f.ajouter();
    if (test) {
        ui->tableView_3->setModel(f.afficher()); //refresh(actualisation)
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n" "Click Cancel to exit."), QMessageBox::Cancel);
        ui->ID->clear();
        ui->nom->clear();
        ui->num->clear();
        ui->mail_2->clear();
        ui->adresse->clear();
        ui->typef->clear();
        ui->typep->clear();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\n"
                                                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_modifier_2_clicked()
{
    int ID = ui->ID->text().toInt();
    QString NOM = ui->nom->text();
    int NUM_TEL = ui->num->text().toInt();
    QString MAIL = ui->mail_2->text();
    QString ADRESSE = ui->adresse->text();
    QString TYPE_F = ui->typef->text();
    QString TYPE_P = ui->typep->text();
    int ID_PRODUIT = ui->prod->text().toInt();
    Fournisseur f(ID, NOM, NUM_TEL, MAIL, ADRESSE, TYPE_F, TYPE_P, ID_PRODUIT);
    bool test = f.modifier(ID);
    if (test) {
        ui->tableView_3->setModel(f.afficher()); //refresh(actualisation)
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("modifier effectué\n" "Click Cancel to exit."), QMessageBox::Cancel);
        ui->ID->clear();
        ui->nom->clear();
        ui->num->clear();
        ui->mail_2->clear();
        ui->adresse->clear();
        ui->typef->clear();
        ui->typep->clear();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("modifier non effectué.\n"
                                                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_suprimer_2_clicked()
{
    Fournisseur f;
    int ID = ui->SUP->text().toInt();
    bool test = f.supprimer(ID);
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("suppression effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_3->setModel(f.afficher());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("suppresion non effectué.\n"
                                                                           "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_contrat_clicked()
{
    // Step 1: Retrieve data from labels
    QString fournisseurName = ui->nom->text();
    QString fournisseurNumTel = ui->num->text();

    if (fournisseurName.isEmpty() || fournisseurNumTel.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please make sure both 'Name' and 'Phone Number' fields are filled.");
        return;
    }

    // Step 2: Generate the PDF file path
    QString filePath = QFileDialog::getSaveFileName(this, "Save Contract", fournisseurName + "_Contract.pdf", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return; // User cancelled the file save dialog
    }

    // Step 3: Initialize the PDF Writer
    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);

    QPainter painter(&writer);
    QRect pageRect(0, 0, writer.width(), writer.height()); // Define the page rectangle manually

    // Step 4: Set fonts and draw content
    QFont titleFont("Arial", 16, QFont::Bold);
    QFont textFont("Arial", 12);

    painter.setFont(titleFont);
    painter.drawText(pageRect, Qt::AlignCenter, "Contract Agreement");

    painter.setFont(textFont);
    painter.translate(0, 50); // Move down from the title

    painter.drawText(100, 150, QString("Fournisseur Name: %1").arg(fournisseurName));
    painter.drawText(100, 200, QString("Phone Number: %1").arg(fournisseurNumTel));
    painter.drawText(100, 250, QString("Date: %1").arg(QDate::currentDate().toString("dd/MM/yyyy")));

    QRect textRect(100, 300, pageRect.width() - 200, pageRect.height() - 400);
    QString contractDetails = QString("This contract is made between the company and the supplier %1.\n\n"
                                       "Phone: %2\n\n"
                                       "The terms and conditions of the agreement are as follows...")
                                  .arg(fournisseurName)
                                  .arg(fournisseurNumTel);

    painter.drawText(textRect, Qt::TextWordWrap, contractDetails);

    painter.end();

    // Step 5: Notify user
    QMessageBox::information(this, "Success", "PDF Contract has been generated successfully!");
}

void MainWindow::on_getlocation_clicked()
{
   //   {  QWebEngineView *webView = new QWebEngineView(this);
        // webView->setGeometry(0, 0, 800, 600); // Adjust dimensions as needed
        // webView->load(QUrl::fromLocalFile("path/to/your/leaflet_map.html")); // Set path to the HTML file
        // webView->show();}
}

void MainWindow::on_bouton_modifier_clicked()
{

    int idClient = ui->lineEdit_idClient->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString typeservice = ui->lineEdit_typeservice->currentText();
    QString typeclient = ui->lineEdit_typeclient->text();
    QString adresse = ui->lineEdit_adresse->text();
    QString numtel = ui->lineEdit_numtel->text();

    // Vérification de l'existence du client avant l'ajout
 if(!etmp.idExists(idClient))
 {
     QMessageBox::warning(this, tr("Erreur dans le id"), tr("le id n'existe pas"));

return;
 }



    if (nom.isEmpty() || prenom.isEmpty() || typeservice.isEmpty() || typeclient.isEmpty() || adresse.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"), tr("Veuillez remplir tous les champs !"));
        ui->tableView_2->setModel(etmp.afficher());
        return;
    }


    if (idClient <= 0 || numtel.length() < 8 || nom.length() < 2 || prenom.length() < 2) {
        QMessageBox::warning(this, tr("Erreur de saisie"), tr("Données invalides prenom,nom doit etre 2 character au minimum !"));
        ui->tableView_2->setModel(etmp.afficher());
        return;
    }


    Clients C(idClient, nom, prenom, typeservice, typeclient, adresse, numtel);
    bool test = C.modifier();
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("modifier effectué !"));
    if (test==false) {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("modifier non effectué !"));
    }


    ui->tableView_2->setModel(etmp.afficher());
    stat_client();
} }

void MainWindow::on_bt_tri_clicked()
{
    {
        QString choix = ui->choix_tri->currentText();
        QString asc = ui->asc_desc->currentText();

        // Determine the sort order
        QString order = (asc == "ASCENDANT") ? "ASC" : "DESC";

        // Check if the selected column is valid
        if (choix == "IDCLIENT" || choix == "NOM" || choix == "PRENOM" ||
            choix == "TYPECLIENT" || choix == "TYPESERVICE" || choix == "NUMTEL")
        {
            // Set the model based on the selected column and order
            ui->tableView_2->setModel(etmp.tri(choix, order));
        }
    }
}

void MainWindow::on_bt_chercher_2_clicked()
{

    QString text=ui->cherche->text();
    QString choix=ui->choix_chercher->currentText();
    if(choix=="IDCLIENT" )
        ui->tableView_2->setModel(etmp.chercher("IDCLIENT",text));
        if(choix=="NOM")

            ui->tableView_2->setModel(etmp.chercher("NOM",text));

            if(choix=="PRENOM" )
                ui->tableView_2->setModel(etmp.chercher("NOM",text));

               if(choix=="TYPECLIENT")
                   ui->tableView_2->setModel(etmp.chercher("TYPECLIENT",text));

                   if(choix=="TYPESERVICE" )
                       ui->tableView_2->setModel(etmp.chercher("TYPESERVICE",text));
        if(choix=="NUMTEL")
            ui->tableView_2->setModel(etmp.chercher("NUMTEL",text));
}


void MainWindow::on_refresh_clicked()
{
    ui->tableView_2->setModel(etmp.afficher());

}


void MainWindow::on_PDF_2_clicked()

    {
        QString strStream;
        QTextStream out(&strStream);

        const int rowCount = ui->tableView->model()->rowCount();
        const int columnCount = ui->tableView->model()->columnCount();

        out << "<html>\n"
               "<head>\n"
               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
               "<title>%1</title>\n"
               "<style>\n"
               "table {\n"
               "    width: 100%;\n"
               "    border-collapse: collapse;\n"
               "}\n"
               "th, td {\n"
               "    padding: 8px;\n"
               "    text-align: left;\n"
               "    border-bottom: 1px solid #ddd;\n"
               "}\n"
               "tr:nth-child(even) {\n"
               "    background-color: #f2f2f2;\n"
               "}\n"
               "</style>\n"
               "</head>\n"
               "<body bgcolor=#ffffff link=#5000A0>\n"
               "<center> <H1>Liste des formations</H1></center><br/><br/>\n"
               "<img src=\"path/to/your/image.jpg\" alt=\"Description of image\" style=\"max-width: 100%; height: auto;\">\n"
               "<table>\n";

        // headers
        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView->isColumnHidden(column))
            {
                out << QString("<th>%1</th>").arg(ui->tableView_2->model()->headerData(column, Qt::Horizontal).toString());
            }
        }
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++)
        {
            out << "<tr> <td>" << row + 1 << "</td>";
            for (int column = 0; column < columnCount; column++)
            {
                if (!ui->tableView_2->isColumnHidden(column))
                {
                    QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
                    out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }



        QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".pdf");
        }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        //printer.setPageSize(QPageSize::A4);
        printer.setOutputFileName(fileName);


        QTextDocument doc;
        doc.setHtml(strStream);
        doc.print(&printer);

    }

void MainWindow::stat_client()
{
    QList<QWidget*> childWidgets = ui->label_stat_client->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();

        }
        //the clear didnt work, but my goal is when i second click this button it deleted old chart and renders a new one
        ui->label_stat_client->clear();
        ui->label_stat_client->hide();

    int s0, s1,s2;

    s0 = etmp.countService("Residential");
    s1 = etmp.countService("Commercial");
    s2 = etmp.countService("Specialized");




    int total = s0 + s1  +s2 ;
    // Calculate percentages
        float x = (total != 0) ? (s0 * 100.0f) / total : 0.0f;
        float x1 = (total != 0) ? (s1 * 100.0f) / total : 0.0f;
        float x2 = (total != 0) ? (s2 * 100.0f) / total : 0.0f;


        // Adjust the percentages to ensure they sum up to 100%
        float totalPercentage = x + x1+x2  ;
        if (totalPercentage != 100.0f && total != 0) {
            float correction = 100.0f - totalPercentage;
            x += correction;  // Apply correction to one of the slices (usually the largest one)
        }



//qDebug() <<  x <<endl;
// 3 jour  33.00 %
    QString ch1 = QString("Residential %1%").arg(QString::number(x, 'f', 2));
    QString ch2 = QString("Commercial %2%").arg(QString::number(x1, 'f', 2));
    QString ch3 = QString("Specialized %2%").arg(QString::number(x2, 'f', 2));






    QPieSeries *series=new QPieSeries();
    series->setHoleSize(0.35);

    QPieSlice *slice= series->append(ch1,x);
    slice->setLabelVisible();
    slice->setLabelColor(QColor(Qt::white));
        slice->setBrush(QColor(189, 76, 224, 1));

    QPieSlice *slice1= series->append(ch2,x1);
    slice1->setLabelVisible();
    slice1->setLabelColor(QColor(Qt::white));
    slice1->setBrush(QColor(84, 16, 149, 1));
    QPieSlice *slice2= series->append(ch3,x2);
    slice2->setLabelVisible();
    slice2->setLabelColor(QColor(Qt::white));
    slice2->setBrush(QColor(Qt::red));

    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBrush backgroundBrush(QColor(187,93,87,0));
    chart->setBackgroundBrush(backgroundBrush);
    QChartView *chartview=new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setFixedSize(ui->label_stat_client->size());
    chartview->setParent(ui->label_stat_client);
    ui->label_stat_client->setStyleSheet("background:transparent; color:white; ");
    ui->label_stat_client->show();

}
#include "qrcodegen.h"

void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
using namespace qrcodegen;
    QAbstractItemModel* model = ui->tableView->model();
    int row = index.row();
    QString IDCLIENT = model->data(model->index(row, 0)).toString();
      QString NOM = model->data(model->index(row, 1)).toString();
      QString PRENOM = model->data(model->index(row, 2)).toString();
      QString TYPECLIENT = model->data(model->index(row, 3)).toString();
      QString TYPESERVICE = model->data(model->index(row, 4)).toString();
      QString ADRESSE = model->data(model->index(row, 5)).toString();
      QString NUMTEL = model->data(model->index(row, 6)).toString();

ui->lineEdit_idClient->setText(IDCLIENT);
ui->lineEdit_nom->setText(NOM);
ui->lineEdit_prenom->setText(PRENOM);
ui->lineEdit_typeservice->setCurrentText(TYPESERVICE);
ui->lineEdit_typeclient->setText(TYPECLIENT);
ui->lineEdit_adresse->setText(ADRESSE);
ui->lineEdit_numtel->setText(NUMTEL);

                    // Using QrCodegen to create a QR code from Facture attributes
                    QString text = "IDCLIENT: " + IDCLIENT + "\n"
                                    "NOM: " + NOM + "\n"
                                    "PRENOM: " + PRENOM + "\n"
                                    "TYPECLIENT : " + TYPECLIENT + "\n"
                                    "TYPESERVICE : " + TYPESERVICE + "\n"
                                     "ADRESSE: " + ADRESSE + "\n"
                                        "NUMTEL: " + NUMTEL + "\n";

                    QrCode qr = QrCode::encodeText(text.toUtf8().data(), QrCode::Ecc::MEDIUM);

                    qint32 sz = qr.getSize();
                    QImage im(sz, sz, QImage::Format_RGB32);
                    QRgb black = qRgb(0, 0, 0);
                    QRgb white = qRgb(255, 255, 255);

                    for (int y = 0; y < sz; y++) {
                        for (int x = 0; x < sz; x++) {
                            im.setPixel(x, y, qr.getModule(x, y) ? black : white);
                        }
                    }
                    ui->qrcode->setPixmap(QPixmap::fromImage(im.scaled(200, 200, Qt::KeepAspectRatio, Qt::FastTransformation), Qt::MonoOnly));




}

void MainWindow::on_bt_envoyer_clicked()
{
    TwilioManager sms;
    sms.sendSMS(ui->sms_body->text());

}

void MainWindow::on_AJOUTER_2_clicked()
{//compteur
int c=0;
// Récupération des valeurs depuis l'interface utilisateur
   int id = ui->ID_EMPLOYE->text().toInt();  // Assurez-vous d'avoir un champ pour l'ID
   QString nom = ui->NOM_2->text();
   QString PRENOM = ui->PRENOM->text();
   QString EMAIL = ui->EMAIL->text();  // Assurez-vous d'avoir un champ pour l'email
   int SALAIRE = ui->SALAIRE->text().toInt();  // Assurez-vous d'avoir un champ pour le salaire (QString)

   QString NUMEROTELEPHONE = ui->NUMEROTELEPHONE->text();  // Assurez-vous d'avoir un champ pour le téléphone
    QDate dateEmbauche = ui->DATE_2->date();
               QString DISPONIBILITE = ui->DISPONIBILITE->text();
QString POSTE=ui->POSTE->currentText();

if(e.EMPLOYEExists(id))
{
c++;
QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                      QObject::tr("id déja existe"), QMessageBox::Cancel);
}
if(ui->ID_EMPLOYE->text().isEmpty() || nom.isEmpty() || PRENOM.isEmpty() || EMAIL.isEmpty()|| ui->SALAIRE->text().isEmpty()|| ui->NUMEROTELEPHONE->text().isEmpty() || DISPONIBILITE.isEmpty()  )
{
c++;
QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                      QObject::tr("tu dois remplir tous les champs"), QMessageBox::Cancel);
}



QRegularExpression regex("^[2|5|7|9]\\d{7}$"); // Expression régulière : commence par 2, 5, 7 ou 9, suivi de 7 chiffres

                if (!regex.match(NUMEROTELEPHONE).hasMatch())
                {
                    QMessageBox::critical(nullptr, QObject::tr("Numéro invalide"), QObject::tr("Le numéro doit contenir 8 chiffres et commencer par 2, 5, 7 ou 9."), QMessageBox::Cancel);
                    return;
                }

        // Vérifier si l'e-mail est valide
        QRegularExpression emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}\\b");//aa@aa.aa
        QRegularExpressionMatch match = emailRegex.match(EMAIL);
        if (!match.hasMatch())
        {
            QMessageBox::critical(nullptr, QObject::tr("Email invalide"), QObject::tr("Le format de l'e-mail est invalide. Veuillez entrer un e-mail valide."), QMessageBox::Cancel);
            return;
        }

if(c==0)
{       // Création de l'objet Employee avec les attributs correspondants
employe e(id, nom, PRENOM, EMAIL,SALAIRE,NUMEROTELEPHONE,POSTE,DISPONIBILITE, dateEmbauche);
   bool insertionSuccess = e.ajouter();
   QMessageBox messageBox;

   if (insertionSuccess)
   {
       messageBox.setText("Données ajoutées à la base de données avec succès !");

       // Réinitialisez les champs de saisie
       ui->ID_EMPLOYE->clear();
       ui->NOM_2->clear();
       ui->PRENOM->clear();
       ui->SALAIRE->clear();
       ui->EMAIL->clear();
       ui->NUMEROTELEPHONE->clear();
         ui->DISPONIBILITE->clear();
        ui->tableView_4->setModel(e.afficher());
        GESTION_EMPLOYE_STATISTIQUE();
   }
   else
   {
       messageBox.setText("Échec de l'ajout des données dans la base de données.");
   }
   messageBox.exec();
}
}

void MainWindow::on_modifier_3_clicked()
{
    {
        int c=0;
        // Récupération des valeurs depuis l'interface utilisateur
           int id = ui->ID_EMPLOYE->text().toInt();  // Assurez-vous d'avoir un champ pour l'ID
           QString nom = ui->NOM_2->text();
           QString PRENOM = ui->PRENOM->text();
           QString EMAIL = ui->EMAIL->text();  // Assurez-vous d'avoir un champ pour l'email
           int SALAIRE = ui->SALAIRE->text().toInt();  // Assurez-vous d'avoir un champ pour le salaire (QString)

           QString NUMEROTELEPHONE = ui->NUMEROTELEPHONE->text();  // Assurez-vous d'avoir un champ pour le téléphone
            QDate dateEmbauche = ui->DATE_2->date();
                       QString DISPONIBILITE = ui->DISPONIBILITE->text();
        QString POSTE=ui->POSTE->currentText();

        if(!e.EMPLOYEExists(id))
        {
        c++;
        QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                              QObject::tr("id n'existe pas"), QMessageBox::Cancel);
        }
        if(ui->ID_EMPLOYE->text().isEmpty() || nom.isEmpty() || PRENOM.isEmpty() || EMAIL.isEmpty()|| ui->SALAIRE->text().isEmpty()|| ui->NUMEROTELEPHONE->text().isEmpty() || DISPONIBILITE.isEmpty()  )
        {
        c++;
        QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                              QObject::tr("tu dois remplir tous les champs"), QMessageBox::Cancel);
        }


        // Vérifier si le numéro correspond au format requis
                       QRegularExpression regex("^[2|5|7|9]\\d{7}$"); // Expression régulière : commence par 2, 5, 7 ou 9, suivi de 7 chiffres

                       if (!regex.match(NUMEROTELEPHONE).hasMatch())
                       {
                           QMessageBox::critical(nullptr, QObject::tr("Numéro invalide"), QObject::tr("Le numéro doit contenir 8 chiffres et commencer par 2, 5, 7 ou 9."), QMessageBox::Cancel);
                           return;
                       }

               // Vérifier si l'e-mail est valide
               QRegularExpression emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}\\b");
               QRegularExpressionMatch match = emailRegex.match(EMAIL);
               if (!match.hasMatch())
               {
                   QMessageBox::critical(nullptr, QObject::tr("Email invalide"), QObject::tr("Le format de l'e-mail est invalide. Veuillez entrer un e-mail valide."), QMessageBox::Cancel);
               }

        if(c==0)
        {       // Création de l'objet Employee avec les attributs correspondants

           bool insertionSuccess = e.modifier(id, nom, PRENOM, EMAIL,SALAIRE,NUMEROTELEPHONE,POSTE,DISPONIBILITE, dateEmbauche);
           QMessageBox messageBox;

           if (insertionSuccess)
           {
               messageBox.setText("Données modifiés à la base de données avec succès !");

               // Réinitialisez les champs de saisie
               ui->ID_EMPLOYE->clear();
               ui->NOM_2->clear();
               ui->PRENOM->clear();
               ui->SALAIRE->clear();
               ui->EMAIL->clear();
               ui->NUMEROTELEPHONE->clear();
                 ui->DISPONIBILITE->clear();
                ui->tableView_4->setModel(e.afficher());
                GESTION_EMPLOYE_STATISTIQUE();
           }
           else
           {
               messageBox.setText("Échec de la modification des données dans la base de données.");
           }
           messageBox.exec();
        }
    }
}

void MainWindow::on_bt_supprimer_2_clicked()
{


        int id=ui->line_supprimer_2->text().toInt();
        if(e.EMPLOYEExists(id))
        {
        bool test =e.supprimer(id);
        QMessageBox msgBox;
        if(test)
        {
            QMessageBox::warning(this, "", "suppression avec succés");
      ui->line_supprimer_2->clear();
     ui->tableView_4->setModel(e.afficher());
     GESTION_EMPLOYE_STATISTIQUE();
        } else
        {
          QMessageBox::warning(this,"", "Erreur", "Échec de suppression des employés.");
          ui->line_supprimer_2->clear();

        }}
     if (e.EMPLOYEExists(id)==false) {
         QMessageBox::warning(this,"","Erreur","id n'existe pas");
         ui->line_supprimer_2->clear();

        }

        }


void MainWindow::on_REFRESH_2_clicked()
{
    ui->tableView_4->setModel(e.afficher());
    GESTION_EMPLOYE_STATISTIQUE();
}

void MainWindow::on_bt_chercher_3_clicked()
{
    QString choix=ui->choix->currentText();
    QString text=ui->line_chercher->text();

if(choix=="ID")
{
    ui->tableView_4->setModel(e.chercher("ID_E",text));
}
if(choix=="NOM")
{
    ui->tableView_4->setModel(e.chercher("NOM",text));
}
if(choix=="PRENOM")
{
    ui->tableView_4->setModel(e.chercher("PRENOM",text));
}
if(choix=="NUMERO")
{
    ui->tableView_4->setModel(e.chercher("NUMERO",text));
}
if(choix=="SALAIRE")
{
    ui->tableView_4->setModel(e.chercher("SALAIRE",text));
}
if(choix=="POSTE")
{
    ui->tableView_4->setModel(e.chercher("POSTE",text));
}

}

void MainWindow::GESTION_EMPLOYE_STATISTIQUE()
{

    //mise a jour
    QList<QWidget*> childWidgets = ui->stat_3->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();

        }
        //the clear didnt work, but my goal is when i second click this button it deleted old chart and renders a new one
        ui->stat_3->clear();
        ui->stat_3->hide();

    int s0, s1,s2,s3;

    s0 = e.countSalaire("0","2000");
    s1 = e.countSalaire("2001","3000");
    s2 = e.countSalaire("3001","4000");
    s3 = e.countSalaire("4001","5000");




    int total = s0 + s1 + s2  +s3;

    // Calculate percentages
        float x = (total != 0) ? (s0 * 100.0f) / total : 0.0f;
        float x1 = (total != 0) ? (s1 * 100.0f) / total : 0.0f;
        float x2 = (total != 0) ? (s2 * 100.0f) / total : 0.0f;
        float x3 = (total != 0) ? (s3 * 100.0f) / total : 0.0f;


        // Adjust the percentages to ensure they sum up to 100%
        float totalPercentage = x + x1+ x2  +x3;
        if (totalPercentage != 100.0f && total != 0) {
            float correction = 100.0f - totalPercentage;
            x += correction;  // Apply correction to one of the slices (usually the largest one)
        }


//+0 50.00%
    QString ch1 = QString("+0 %1%").arg(QString::number(x, 'f', 2));
    QString ch2 = QString("+2000 %2%").arg(QString::number(x1, 'f', 2));
    QString ch3 = QString("+3000 %3%").arg(QString::number(x2, 'f', 2));
    QString ch4 = QString("+4000 %4%").arg(QString::number(x3, 'f', 2));




    QPieSeries *series=new QPieSeries();
    series->setHoleSize(0.35);

    QPieSlice *slice= series->append(ch1,x);
    slice->setLabelVisible();
    slice->setLabelColor(QColor(Qt::white));
        slice->setBrush(QColor(189, 76, 224, 1));//changer couleur !!!

    QPieSlice *slice1= series->append(ch2,x1);
    slice1->setLabelVisible();
    slice1->setLabelColor(QColor(Qt::white));
    slice1->setBrush(QColor(84, 16, 149, 1));

    QPieSlice *slice2= series->append(ch3,x2);//changer couleur !!!
    slice2->setLabelVisible();

    slice2->setLabelColor(QColor(Qt::white));
    slice2->setBrush(QColor(119, 82, 254));//changer couleur !!!

    QPieSlice *slice3= series->append(ch4,x3);
    slice3->setLabelVisible();


    slice3->setLabelColor(QColor(Qt::white));
    slice3->setBrush(QColor(119, 82, 254));//changer couleur !!!




    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBrush backgroundBrush(QColor(187,93,87,0));
    chart->setBackgroundBrush(backgroundBrush);
    QChartView *chartview=new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setFixedSize(ui->stat_3->size());
    chartview->setParent(ui->stat_3);
    ui->stat_3->setStyleSheet("background:transparent; color:white; ");

    ui->stat_3->show();

}
void MainWindow::on_pdf_2_clicked()
{
    {
        QString strStream;
        QTextStream out(&strStream);

        const int rowCount = ui->tableView_3->model()->rowCount();
        const int columnCount = ui->tableView_3->model()->columnCount();

        out << "<html>\n"
               "<head>\n"
               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
               "<title>%1</title>\n"
               "<style>\n"
               "table {\n"
               "    width: 100%;\n"
               "    border-collapse: collapse;\n"
               "}\n"
               "th, td {\n"
               "    padding: 8px;\n"
               "    text-align: left;\n"
               "    border-bottom: 1px solid #ddd;\n"
               "}\n"
               "tr:nth-child(even) {\n"
               "    background-color: #f2f2f2;\n"
               "}\n"
               "</style>\n"
               "</head>\n"
               "<body bgcolor=#ffffff link=#5000A0>\n"
               "<center> <H1>Liste des employes</H1></center><br/><br/>\n"
               "<img src='file:///C:/Users/USER/Documents/produit/img.png' width='50' height='50'><br/><br/>\n"
               "<table>\n";

        // headers
        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_3->isColumnHidden(column))
            {
                out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
            }
        }
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++)
        {
            out << "<tr> <td>" << row + 1 << "</td>";
            for (int column = 0; column < columnCount; column++)
            {
                if (!ui->tableView_3->isColumnHidden(column))
                {
                    QString data = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, column)).toString().simplified();
                    out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }



        QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), ".pdf");
        if (QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".pdf");
        }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        doc.setHtml(strStream);
        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);

    }
}

void MainWindow::on_b1_2_clicked()
{
    {
        QString choix=ui->choix->currentText();
    if(choix=="ID")
    {
        ui->tableView_4->setModel(e.tri("ID_E"));//asc
    }
    if(choix=="NOM")
    {
        ui->tableView_4->setModel(e.tri("NOM"));
    }
    if(choix=="PRENOM")
    {
        ui->tableView_4->setModel(e.tri("PRENOM"));
    }
    if(choix=="NUMERO")
    {
        ui->tableView_4->setModel(e.tri("NUMERO"));
    }
    if(choix=="SALAIRE")
    {
        ui->tableView_4->setModel(e.tri("SALAIRE"));
    }
    if(choix=="POSTE")
    {
        ui->tableView_4->setModel(e.tri("POSTE"));
    }
    }
}

void MainWindow::on_b2_2_clicked()
{
    {
        QString choix=ui->choix->currentText();
    if(choix=="ID")
    {
        ui->tableView_4->setModel(e.tri1("ID_E"));//desc
    }
    if(choix=="NOM")
    {
        ui->tableView_4->setModel(e.tri1("NOM"));
    }
    if(choix=="PRENOM")
    {
        ui->tableView_4->setModel(e.tri1("PRENOM"));
    }
    if(choix=="NUMERO")
    {
        ui->tableView_4->setModel(e.tri1("NUMERO"));
    }
    if(choix=="SALAIRE")
    {
        ui->tableView_4->setModel(e.tri1("SALAIRE"));
    }
    if(choix=="POSTE")
    {
        ui->tableView_4->setModel(e.tri1("POSTE"));
    }
    }

}
QString MainWindow::generateRandomCode(int length) {
    const QString characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    QString randomCode;

    for (int i = 0; i < length; ++i) {
        int index = rand() % characters.length();
        randomCode.append(characters[index]);
    }

    return randomCode;
}
void MainWindow::on_QUITTER_clicked()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Quitter", "Voulez-vous vraiment quitter ?",
                                    QMessageBox::Yes | QMessageBox::No);

      // Check the response
      if (reply == QMessageBox::Yes) {
          // If user clicks Yes, close the application
          qApp->quit(); // This will terminate the application

          QSqlQuery query;
          query.prepare("UPDATE  EMPLOYES SET PRESENCE='absent' ");
          query.exec();
      }
}


void MainWindow::on_tableView_4_clicked(const QModelIndex &index)
{
    {
        int row = index.row();
              QString id = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, 0)).toString();
              QString nom = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, 1)).toString();
              QString prenom = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, 2)).toString();
              QString email = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, 3)).toString();
              QString salaire = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, 4)).toString();
              QString numero = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, 5)).toString();
              QString poste = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, 6)).toString();
              QString disponibilite = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, 7)).toString();

            QDate DATE = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, 8)).toDate();


    ui->ID_EMPLOYE->setText(id);
    ui->NOM_2->setText(nom);
    ui->PRENOM->setText(prenom);
    ui->EMAIL->setText(email);
    ui->SALAIRE->setText(salaire);
    ui->NUMEROTELEPHONE->setText(numero);
    ui->POSTE->setCurrentText(poste);
    ui->DISPONIBILITE->setText(disponibilite);
    ui->DATE_2->setDate(DATE);
    }
}

void MainWindow::on_code_clicked()
{
    QString email=ui->login_email->text();
    QString code = generateRandomCode(6); // Generate a 6-character code
    QString message = "Your verification code is: " + code;
    e.setmessage(code);
    emailSender.sendEmail(email, "Recuperation du mot de pass"
                          , message);
}

void MainWindow::on_valider_clicked()
{
    {
        QString email=ui->login_email->text();
    QString code=ui->line_code->text();
    if(code==e.getmessage())
    {
        QSqlQuery query;
        query.prepare("SELECT MDP FROM EMPLOYES WHERE EMAIL = :email");
        query.bindValue(":email", email);

        if (query.exec() && query.next()) {

            QString storedPassword = query.value("MDP").toString();
            QString message = QString("Votre mot de passe est : %1").arg(storedPassword);
            QMessageBox::information(nullptr, QObject::tr("Mot de passe"), message, QMessageBox::Cancel);
        }
    }
    else
        QMessageBox::information(nullptr, QObject::tr("code incorrecte"), "", QMessageBox::Cancel);

    }
}

void MainWindow::on_bt_login_clicked()
{
    QString email = ui->login_email->text();
     QString password = ui->login_mdp->text();

     QSqlQuery query;
     query.prepare("SELECT * FROM EMPLOYES WHERE EMAIL = :email");
     query.bindValue(":email", email);

     if (query.exec() && query.next()) {

         QString storedPassword = query.value("MDP").toString();
         if (password == storedPassword) {

             query.prepare("SELECT POSTE FROM EMPLOYES WHERE EMAIL = :email");
             query.bindValue(":email", email);

             if (query.exec() && query.next())
             e.setposte ( query.value("POSTE").toString());
             ui->login_email->clear();
             ui->login_mdp->clear();
             ui->historique->hide();
             ui->gestion_client->hide();
             ui->gestion_employe->hide();
             ui->gestion_produit->hide();
             ui->gestion_fournisseur->hide();
             ui->gestion_materiel->hide();
             ui->login->hide();
             ui->menu->show();
         } else {
             // Password is incorrect
             QMessageBox::critical(this, "Error", "Incorrect password");
         }
     } else {
         // User record not found
         QMessageBox::critical(this, "Error", "Incorrect email");
     }

}

void MainWindow::on_Retour_3_clicked()
{
    ui->historique->hide();
    ui->gestion_client->hide();
    ui->gestion_employe->hide();
    ui->gestion_produit->hide();
    ui->gestion_fournisseur->hide();
    ui->gestion_materiel->hide();
    ui->login->hide();
    ui->menu->show();
}

void MainWindow::on_Retour_4_clicked()
{
    ui->historique->hide();
    ui->gestion_client->hide();
    ui->gestion_employe->hide();
    ui->gestion_produit->hide();
    ui->gestion_fournisseur->hide();
    ui->gestion_materiel->hide();
    ui->login->hide();
    ui->menu->show();
}

void MainWindow::on_Retour_5_clicked()
{

        ui->historique->hide();
        ui->gestion_client->hide();
        ui->gestion_employe->hide();
        ui->gestion_produit->hide();
        ui->gestion_fournisseur->hide();
        ui->gestion_materiel->hide();
        ui->login->hide();
        ui->menu->show();
}


void MainWindow::on_Retour_6_clicked()
{
    ui->historique->hide();
    ui->gestion_client->hide();
    ui->gestion_employe->hide();
    ui->gestion_produit->hide();
    ui->gestion_fournisseur->hide();
    ui->gestion_materiel->hide();
    ui->login->hide();
    ui->menu->show();
}

void MainWindow::on_Retour_7_clicked()
{
    ui->historique->hide();
    ui->gestion_client->hide();
    ui->gestion_employe->hide();
    ui->gestion_produit->hide();
    ui->gestion_fournisseur->hide();
    ui->gestion_materiel->hide();
    ui->login->hide();
    ui->menu->show();
}

void MainWindow::on_menu_employe_clicked()
{
    QString ROLE=e.getposte();

          if(ROLE == "RH" || ROLE == "ADMIN") // || ROLE=="DEV"
          {ui->menu->hide();
              ui->historique->hide();
              ui->gestion_client->hide();
              ui->gestion_employe->show();
              ui->gestion_produit->hide();
              ui->gestion_fournisseur->hide();
              ui->gestion_materiel->hide();
              ui->login->hide();
              ui->menu->hide();
          }
          else
          {
         QMessageBox::critical(this, "Error", "tu n'as pas l'accès à la gestion employe");
          }
}

void MainWindow::on_menu_client_clicked()
{
    QString ROLE=e.getposte();

          if(ROLE == "RH" || ROLE == "ADMIN") // || ROLE=="DEV"
          {ui->menu->hide();
              ui->historique->hide();
              ui->gestion_client->show();
              ui->gestion_employe->hide();
              ui->gestion_produit->hide();
              ui->gestion_fournisseur->hide();
              ui->gestion_materiel->hide();
              ui->login->hide();
              ui->menu->hide();
          }
          else
          {
         QMessageBox::critical(this, "Error", "tu n'as pas l'accès à la gestion employe");
          }
}

void MainWindow::on_menu_fournisseur_clicked()
{
    QString ROLE=e.getposte();

          if(ROLE == "DEV" || ROLE == "ADMIN") // || ROLE=="DEV"
          {ui->menu->hide();
              ui->historique->hide();
              ui->gestion_client->hide();
              ui->gestion_employe->hide();
              ui->gestion_produit->hide();
              ui->gestion_fournisseur->show();
              ui->gestion_materiel->hide();
              ui->login->hide();
              ui->menu->hide();
          }
          else
          {
         QMessageBox::critical(this, "Error", "tu n'as pas l'accès à la gestion employe");
          }
}

void MainWindow::on_menu_materiel_clicked()
{
    QString ROLE=e.getposte();

          if(ROLE == "RH" || ROLE == "ADMIN") // || ROLE=="DEV"
          {ui->menu->hide();
              ui->historique->hide();
              ui->gestion_client->hide();
              ui->gestion_employe->hide();
              ui->gestion_produit->hide();
              ui->gestion_fournisseur->hide();
              ui->gestion_materiel->show();
              ui->login->hide();
              ui->menu->hide();
          }
          else
          {
         QMessageBox::critical(this, "Error", "tu n'as pas l'accès à la gestion employe");
          }
}

void MainWindow::on_menu_produit_clicked()
{
    QString ROLE=e.getposte();

          if(ROLE == "RH" || ROLE == "ADMIN") // || ROLE=="DEV"
          {ui->menu->hide();
              ui->historique->hide();
              ui->gestion_client->hide();
              ui->gestion_employe->hide();
              ui->gestion_produit->show();
              ui->gestion_fournisseur->hide();
              ui->gestion_materiel->hide();
              ui->login->hide();
              ui->menu->hide();
          }
          else
          {
         QMessageBox::critical(this, "Error", "tu n'as pas l'accès à la gestion employe");
          }
}

void MainWindow::on_chercher_2_clicked()
{
QString cher=ui->cher->text();
Fournisseur f;
ui->tableView_3->setModel(f.chercher(cher));
}

void MainWindow::on_chercher_3_clicked()
{
    Fournisseur f;

    ui->tableView_3->setModel(f.afficher());

}
