#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QChartView>
#include <QChart>
#include <QPieSeries>
#include <QPieSlice>
#include <QTextDocument>
#include <QFileDialog>
#include <QPrinter>
#include <QFileInfo>
#include <QTextStream>
#include "email.h"
using namespace  QtCharts;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->login->show();
    ui->menu->hide();
    ui->gestion_employe->hide();
    ui->tableView->setModel(e.afficher());


    // Set a regular expression validator to allow only letters
        QRegularExpression regex("^[0-9]+$"); // Regex for letters only
        QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);
        ui->ID_EMPLOYE->setValidator(validator);
        ui->SALAIRE->setValidator(validator);
        ui->DISPONIBILITE->setValidator(validator);
        ui->line_supprimer->setValidator(validator);

    // Set a regular expression validator to allow only letters
        QRegularExpression regex1("^[A-Za-z]+$"); // Regex for letters only
        QRegularExpressionValidator *validator1 = new QRegularExpressionValidator(regex1, this);
        ui->NOM->setValidator(validator1);
        ui->PRENOM->setValidator(validator1);

        GESTION_EMPLOYE_STATISTIQUE();


        ui->login_mdp->setEchoMode(QLineEdit::Password);




        int ret = A.connect_arduino();

        switch (ret) {
        case 0:
            QMessageBox::information(this, "Connexion réussie", "Arduino connecté sur le port : " + A.get_arduino_port_name());
            break;
        case 1:
            QMessageBox::information(this, "Aucun port trouvé", "Aucun port série détecté.");
            break;
        case -1:
            QMessageBox::information(this, "Connexion échouée", "Impossible de se connecter à l'Arduino.");
            break;
        }

        // Connecter le signal readyRead au slot update.
        //QObject::connect(a.get_serial(), SIGNAL(readyRead()), this, SLOT(update()));
}

void MainWindow::fonction_arduino()
{
    QByteArray data = A.read_from_arduino();
    QString nb = QString::fromUtf8(data).trimmed(); // Convert data to QString
if(nb!="*")
{
    A.code+=nb;
}
    else
{
    A.code.remove("*");

    QSqlQuery query;
    query.prepare("SELECT ID_E,NOM FROM EMPLOYES WHERE ID_E = :code");
    query.bindValue(":code", A.code);

    if(query.exec() && query.next())
    {
        QString id=query.value(0).toString();
        QString nom=query.value(1).toString();
        QSqlQuery sql;
        sql.prepare("UPDATE EMPLOYES SET PRESENCE='Present' WHERE ID_E=:code");
        sql.exec();

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

    }
    else
    {
        QMessageBox::warning(this, "", "Le id n'existe pas!");

    }


}

  A.code.clear();
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AJOUTER_clicked()
{//compteur
int c=0;
// Récupération des valeurs depuis l'interface utilisateur
   int id = ui->ID_EMPLOYE->text().toInt();  // Assurez-vous d'avoir un champ pour l'ID
   QString nom = ui->NOM->text();
   QString PRENOM = ui->PRENOM->text();
   QString EMAIL = ui->EMAIL->text();  // Assurez-vous d'avoir un champ pour l'email
   int SALAIRE = ui->SALAIRE->text().toInt();  // Assurez-vous d'avoir un champ pour le salaire (QString)

   QString NUMEROTELEPHONE = ui->NUMEROTELEPHONE->text();  // Assurez-vous d'avoir un champ pour le téléphone
    QDate dateEmbauche = ui->DATE->date();
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
       ui->NOM->clear();
       ui->PRENOM->clear();
       ui->SALAIRE->clear();
       ui->EMAIL->clear();
       ui->NUMEROTELEPHONE->clear();
         ui->DISPONIBILITE->clear();
        ui->tableView->setModel(e.afficher());
        GESTION_EMPLOYE_STATISTIQUE();
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
    int c=0;
    // Récupération des valeurs depuis l'interface utilisateur
       int id = ui->ID_EMPLOYE->text().toInt();  // Assurez-vous d'avoir un champ pour l'ID
       QString nom = ui->NOM->text();
       QString PRENOM = ui->PRENOM->text();
       QString EMAIL = ui->EMAIL->text();  // Assurez-vous d'avoir un champ pour l'email
       int SALAIRE = ui->SALAIRE->text().toInt();  // Assurez-vous d'avoir un champ pour le salaire (QString)

       QString NUMEROTELEPHONE = ui->NUMEROTELEPHONE->text();  // Assurez-vous d'avoir un champ pour le téléphone
        QDate dateEmbauche = ui->DATE->date();
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
           ui->NOM->clear();
           ui->PRENOM->clear();
           ui->SALAIRE->clear();
           ui->EMAIL->clear();
           ui->NUMEROTELEPHONE->clear();
             ui->DISPONIBILITE->clear();
            ui->tableView->setModel(e.afficher());
            GESTION_EMPLOYE_STATISTIQUE();
       }
       else
       {
           messageBox.setText("Échec de la modification des données dans la base de données.");
       }
       messageBox.exec();
    }
}

void MainWindow::on_bt_supprimer_clicked()
{


        int id=ui->line_supprimer->text().toInt();
        if(e.EMPLOYEExists(id))
        {
        bool test =e.supprimer(id);
        QMessageBox msgBox;
        if(test)
        {
            QMessageBox::warning(this, "", "suppression avec succés");
      ui->line_supprimer->clear();
     ui->tableView->setModel(e.afficher());
     GESTION_EMPLOYE_STATISTIQUE();
        } else
        {
          QMessageBox::warning(this,"", "Erreur", "Échec de suppression des employés.");
          ui->line_supprimer->clear();

        }}
     if (e.EMPLOYEExists(id)==false) {
         QMessageBox::warning(this,"","Erreur","id n'existe pas");
         ui->line_supprimer->clear();

        }

        }


void MainWindow::on_REFRESH_clicked()
{
      ui->tableView->setModel(e.afficher());
      GESTION_EMPLOYE_STATISTIQUE();
}



void MainWindow::on_bt_chercher_clicked()
{
    QString choix=ui->choix->currentText();
    QString text=ui->line_chercher->text();

if(choix=="ID")
{
    ui->tableView->setModel(e.chercher("ID_E",text));
}
if(choix=="NOM")
{
    ui->tableView->setModel(e.chercher("NOM",text));
}
if(choix=="PRENOM")
{
    ui->tableView->setModel(e.chercher("PRENOM",text));
}
if(choix=="NUMERO")
{
    ui->tableView->setModel(e.chercher("NUMERO",text));
}
if(choix=="SALAIRE")
{
    ui->tableView->setModel(e.chercher("SALAIRE",text));
}
if(choix=="POSTE")
{
    ui->tableView->setModel(e.chercher("POSTE",text));
}

}


void MainWindow::GESTION_EMPLOYE_STATISTIQUE()
{
    
    //mise a jour
    QList<QWidget*> childWidgets = ui->stat->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();

        }
        //the clear didnt work, but my goal is when i second click this button it deleted old chart and renders a new one
        ui->stat->clear();
        ui->stat->hide();

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
    chartview->setFixedSize(ui->stat->size());
    chartview->setParent(ui->stat);
    ui->stat->setStyleSheet("background:transparent; color:white; ");
    
    ui->stat->show();

}



void MainWindow::on_pdf_clicked()
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
           "<center> <H1>Liste des employes</H1></center><br/><br/>\n"
           "<img src='file:///C:/Users/USER/Documents/produit/img.png' width='50' height='50'><br/><br/>\n"
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

void MainWindow::on_b1_clicked()
{
    QString choix=ui->choix->currentText();
if(choix=="ID")
{
    ui->tableView->setModel(e.tri("ID_E"));//asc
}
if(choix=="NOM")
{
    ui->tableView->setModel(e.tri("NOM"));
}
if(choix=="PRENOM")
{
    ui->tableView->setModel(e.tri("PRENOM"));
}
if(choix=="NUMERO")
{
    ui->tableView->setModel(e.tri("NUMERO"));
}
if(choix=="SALAIRE")
{
    ui->tableView->setModel(e.tri("SALAIRE"));
}
if(choix=="POSTE")
{
    ui->tableView->setModel(e.tri("POSTE"));
}
}

void MainWindow::on_b2_clicked()
{
    QString choix=ui->choix->currentText();
if(choix=="ID")
{
    ui->tableView->setModel(e.tri1("ID_E"));//desc
}
if(choix=="NOM")
{
    ui->tableView->setModel(e.tri1("NOM"));
}
if(choix=="PRENOM")
{
    ui->tableView->setModel(e.tri1("PRENOM"));
}
if(choix=="NUMERO")
{
    ui->tableView->setModel(e.tri1("NUMERO"));
}
if(choix=="SALAIRE")
{
    ui->tableView->setModel(e.tri1("SALAIRE"));
}
if(choix=="POSTE")
{
    ui->tableView->setModel(e.tri1("POSTE"));
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

void MainWindow::on_menu_employe_clicked()
{
    QString ROLE=e.getposte();

       if(ROLE == "RH" || ROLE == "ADMIN") // || ROLE=="DEV"
       {ui->menu->hide();
           ui->gestion_employe->show();
       }
       else
       {
      QMessageBox::critical(this, "Error", "tu n'as pas l'accès à la gestion employe");
       }
}

void MainWindow::on_menu_client_clicked()
{
    QString ROLE=e.getposte();

       if(ROLE == "ADMIN" ) // || ROLE=="DEV"
       {ui->menu->hide();
           ui->gestion_employe->show();
       }
       else
       {
      QMessageBox::critical(this, "Error", "tu n'as pas l'accès à la gestion client");
       }
}
void MainWindow::on_menu_fournisseur_clicked()
{
    QString ROLE=e.getposte();

       if(ROLE == "ADMIN" ) // || ROLE=="DEV"
       {ui->menu->hide();
           ui->gestion_employe->show();
       }
       else
       {
      QMessageBox::critical(this, "Error", "tu n'as pas l'accès à la gestion fournisseur");
       }
}
void MainWindow::on_menu_produit_clicked()
{
    QString ROLE=e.getposte();

       if(ROLE == "ADMIN" ) // || ROLE=="DEV"
       {ui->menu->hide();
           ui->gestion_employe->show();
       }
       else
       {
      QMessageBox::critical(this, "Error", "tu n'as pas l'accès à la gestion produit");
       }
}
void MainWindow::on_menu_materiel_clicked()
{
    QString ROLE=e.getposte();

       if(ROLE == "ADMIN" ) // || ROLE=="DEV"
       {ui->menu->hide();
           ui->gestion_employe->show();
       }
       else
       {
      QMessageBox::critical(this, "Error", "tu n'as pas l'accès à la gestion materiel");
       }
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
          QString id = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();
          QString nom = ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString();
          QString prenom = ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString();
          QString email = ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString();
          QString salaire = ui->tableView->model()->data(ui->tableView->model()->index(row, 4)).toString();
          QString numero = ui->tableView->model()->data(ui->tableView->model()->index(row, 5)).toString();
          QString poste = ui->tableView->model()->data(ui->tableView->model()->index(row, 6)).toString();
          QString disponibilite = ui->tableView->model()->data(ui->tableView->model()->index(row, 7)).toString();

        QDate DATE = ui->tableView->model()->data(ui->tableView->model()->index(row, 8)).toDate();


ui->ID_EMPLOYE->setText(id);
ui->NOM->setText(nom);
ui->PRENOM->setText(prenom);
ui->EMAIL->setText(email);
ui->SALAIRE->setText(salaire);
ui->NUMEROTELEPHONE->setText(numero);
ui->POSTE->setCurrentText(poste);
ui->DISPONIBILITE->setText(disponibilite);
ui->DATE->setDate(DATE);
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
