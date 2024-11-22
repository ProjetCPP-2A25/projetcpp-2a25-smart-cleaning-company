#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include "Qrcode.hpp"
#include "twiliomanager.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   ui->label->lower();
   ui->tableView->setModel(etmp.afficher());
   ui->tableView->setColumnWidth(6, 150);
   QSqlTableModel *model;
   model = new QSqlTableModel(this);
      model->setTable("FS_CLIENTS");
      model->select();  // Charger les données de la table
      ui->tableView->setModel(model);  // Associer le modèle à la vue
      ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
      stat();
}
MainWindow::~MainWindow()
{
   delete ui;
}


void MainWindow::on_bouton_clicked() {
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
        ui->tableView->setModel(etmp.afficher());  // Rafraîchir le tableau
        return;  // Arrêter l'exécution si un champ est vide
    }

    // Vérifications des saisies
    if (idClient <= 0 || numtel.length() <= 0 || nom.length() < 2 || prenom.length() < 2) {
        QMessageBox::warning(this, tr("Erreur de saisie"), tr("Données invalides !"));
        ui->tableView->setModel(etmp.afficher());  // Rafraîchir le tableau
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
    ui->tableView->setModel(etmp.afficher());
    stat();
} }

void MainWindow::on_supprimer_clicked() {
   int idClient = ui->lineEdit_ids->text().toInt(); // Récupérer l'ID saisi


   // Appeler la méthode supprimer
   bool test = etmp.supprimer(idClient);
   if (test) {
       QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectuée \n""Click Cancel to exit."), QMessageBox::Cancel);
   } else {
       QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Suppression non effectuée. \n ID non existant \n""Click Cancel to exit."), QMessageBox::Cancel);
   }
   ui->tableView->setModel(etmp.afficher());
   stat();
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
        ui->tableView->setModel(etmp.afficher());
        return;
    }


    if (idClient <= 0 || numtel.length() < 8 || nom.length() < 2 || prenom.length() < 2) {
        QMessageBox::warning(this, tr("Erreur de saisie"), tr("Données invalides prenom,nom doit etre 2 character au minimum !"));
        ui->tableView->setModel(etmp.afficher());
        return;
    }


    Clients C(idClient, nom, prenom, typeservice, typeclient, adresse, numtel);
    bool test = C.modifier();
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("modifier effectué !"));
    if (test==false) {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("modifier non effectué !"));
    }


    ui->tableView->setModel(etmp.afficher());
    stat();
} }
/*
void MainWindow::on_bt_tri_clicked()
{
    QString choix=ui->choix_tri->currentText();
    QString asc=ui->asc_desc->currentText();
    if(choix=="IDCLIENT" && asc=="ASCENDANT")
       { ui->tableView->setModel(etmp.tri("IDCLIENT","ASCENDANT"));}

        if(choix=="NOM"&& asc =="ASCENDANT")
            {ui->tableView->setModel(etmp.tri("NOM","ASCENDANT"));}

            if(choix=="PRENOM" && asc=="ASCENDANT")
                {ui->tableView->setModel(etmp.tri("PRENOM","ASCENDANT"));}

               if(choix=="TYPECLIENT"&& asc=="ASCENDANT")
                   {ui->tableView->setModel(etmp.tri("TYPECLIENT","ASCENDANT"));}

                   if(choix=="TYPESERVICE" && asc=="ASCENDANT")
                       {ui->tableView->setModel(etmp.tri("TYPESERVICE","ASCENDANT"));}

        if(choix=="NUMTEL" && asc=="ASCENDANT")
            {ui->tableView->setModel(etmp.tri("NUMTEL","ASCENDANT"));}


        if(choix=="IDCLIENT" && asc=="DESCENDANT")
            {ui->tableView->setModel(etmp.tri("IDCLIENT","DESCENDANT"));}

            if(choix=="NOM"&& asc =="DESCENDANT")
                {ui->tableView->setModel(etmp.tri("NOM","DESCENDANT"));}

                if(choix=="PRENOM" && asc=="DESCENDANT")
                    {ui->tableView->setModel(etmp.tri("NOM","DESCENDANT"));}

                   if(choix=="TYPECLIENT"&& asc=="DESCENDANT")
                       {ui->tableView->setModel(etmp.tri("TYPECLIENT","DESCENDANT"));}

                       if(choix=="TYPESERVICE" && asc=="DESCENDANT")
                           {ui->tableView->setModel(etmp.tri("TYPESERVICE","DESCENDANT"));}

            if(choix=="NUMTEL" && asc=="DESCENDANT")
                {ui->tableView->setModel(etmp.tri("NUMTEL","DESCENDANT"));}





}
*/
void MainWindow::on_bt_tri_clicked()
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
        ui->tableView->setModel(etmp.tri(choix, order));
    }
}
void MainWindow::on_bt_chercher_clicked()
{
    QString text=ui->cherche->text();
    QString choix=ui->choix_chercher->currentText();
    if(choix=="IDCLIENT" )
        ui->tableView->setModel(etmp.chercher("IDCLIENT",text));
        if(choix=="NOM")

            ui->tableView->setModel(etmp.chercher("NOM",text));

            if(choix=="PRENOM" )
                ui->tableView->setModel(etmp.chercher("NOM",text));

               if(choix=="TYPECLIENT")
                   ui->tableView->setModel(etmp.chercher("TYPECLIENT",text));

                   if(choix=="TYPESERVICE" )
                       ui->tableView->setModel(etmp.chercher("TYPESERVICE",text));
        if(choix=="NUMTEL")
            ui->tableView->setModel(etmp.chercher("NUMTEL",text));
}

void MainWindow::on_refresh_clicked()
{
    ui->tableView->setModel(etmp.afficher());

}

void MainWindow::on_PDF_clicked()
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



    QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);
    printer.setOutputFileName(fileName);


    QTextDocument doc;
    doc.setHtml(strStream);
    doc.print(&printer);

}

void MainWindow::stat()
{
    QList<QWidget*> childWidgets = ui->label_stat->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();

        }
        //the clear didnt work, but my goal is when i second click this button it deleted old chart and renders a new one
        ui->label_stat->clear();
        ui->label_stat->hide();

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
    chartview->setFixedSize(ui->label_stat->size());
    chartview->setParent(ui->label_stat);
    ui->label_stat->setStyleSheet("background:transparent; color:white; ");
    ui->label_stat->show();

}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
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
