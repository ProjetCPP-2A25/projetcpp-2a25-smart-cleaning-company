#include "mainwindow.h"
#include "ui_mainwindow.h"
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
