#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "patient.h"
#include <QSqlQuery>
#include "connection.h"
#include <QMessageBox>
#include <QList>
#include <QStringList>
#include <QApplication>
#include <QFile>
#include <QTextDocument>
#include <QTextCursor>
#include <QPrinter>
#include <QFileDialog>
#include <QList>
#include <QImage>
#include <QtGui>
#include <QtWidgets/QListWidget>
#include "image.h"

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QLabel>
#include <QTextBrowser>
#include <QApplication>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    // MainWindow::on_tabWidget_currentChanged();
    ui->lineEdit_4->setValidator(new QIntValidator(11111, 99999, this));
       ui->lineEdit_7->setValidator(new QIntValidator(1, 99, this));
       ui->lineEdit_8->setValidator(new QRegExpValidator(QRegExp("[A-z]*"), this));
       ui->lineEdit_9->setValidator(new QRegExpValidator(QRegExp("[A-z]*"), this));
        ui->lineEdit_3->setValidator(new QIntValidator(11111, 99999, this));

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_16_clicked);
     connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_16_clicked()//ajouter
{
    int cin = ui->lineEdit_3->text().toInt();
    QString nom = ui->lineEdit_8->text();
    QString prenom = ui->lineEdit_9->text();
    int num_tel = ui->lineEdit_4->text().toInt();
    QString genre = ui->lineEdit_5->text();
     QString maladie = ui->lineEdit_6->text();
    QString age = ui->lineEdit_7->text();

    /*QPixmap image("/chemin/vers/votre/image.png");
    ui->label_13->setPixmap(image.scaled(ui->label_13->size(), Qt::KeepAspectRatio, Qt::FastTransformation));*/
    if (nom.isEmpty() || prenom.isEmpty() || genre.isEmpty() || maladie.isEmpty() || age.isEmpty()) {
          QMessageBox::warning(this, tr("Erreur de saisie"), tr("Tous les champs sont obligatoires"));
          return;
      }


    patient p;

    QString fileName = QFileDialog::getOpenFileName(this, "Sélectionnez une image", QDir::homePath(), "Images (*.png *.jpg *.jpeg *.bmp)");

    if (!fileName.isEmpty()) {
        QImage image(fileName);
        ui->label_13->setPixmap(QPixmap::fromImage(image));
        QByteArray imageBytes;
        QBuffer buffer(&imageBytes);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");
        buffer.close();
        ui->lineEdit_11->setText(fileName);

        QPixmap pixmap;
        pixmap.loadFromData(imageBytes);
        p.ajouter_patient(cin, nom, prenom, num_tel, genre, maladie, age, pixmap);
        p.historique(1, nom + " " + prenom);
    }

}
void MainWindow::on_pushButton_clicked()//modifier
{
    int cin = ui->lineEdit_3->text().toInt();
    QString nom = ui->lineEdit_8->text();
    QString prenom = ui->lineEdit_9->text();
    int num_tel = ui->lineEdit_4->text().toInt();
    QString genre = ui->lineEdit_5->text();
     QString maladie = ui->lineEdit_6->text();
    QString age = ui->lineEdit_7->text();


patient p;
 p.modifier_patient(cin, nom, prenom, num_tel, maladie, age,genre);
 p.historique(3, nom + " " + prenom);



}

void MainWindow::on_pushButton_11_clicked()//afficher
{
 //QPixmap image("chemin/vers/mon/image.jpg");
       patient p;
        QSqlQueryModel* model = p.afficher();
        const int IMAGE_COLUMN = 7;
        ImageDelegate* delegate = new ImageDelegate();
        ui->tableView->setItemDelegateForColumn(IMAGE_COLUMN, delegate);
          ui->tableView->setModel(model); // Ajout manquant
          ui->lineEdit_3->setText("");
          ui->lineEdit_8->setText("");
          ui->lineEdit_9->setText("");
          ui->lineEdit_4->setText("");
          ui->lineEdit_5->setText("");
          ui->lineEdit_6->setText("");
          ui->lineEdit_7->setText("");
          ui->label_13->clear();
}



void MainWindow::on_pushButton_10_clicked()//suppression
{ int cin = ui->lineEdit_3->text().toInt();
patient p;
p.supprimer(cin);
p.historique(2, QString("cin %1").arg(QString::number(cin)));
}



//les metiers






void MainWindow::on_pushButton_2_clicked()//pdf
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf)"));
        if (fileName.isEmpty()) {
            QMessageBox::critical(this, tr("Error"), tr("No file name specified."));
            return;
        }

        patient p;
        if (! p.pdf(ui->tableView, fileName)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not create PDF file."));
            return;
        }


        QMessageBox::information(this, tr("Information"), tr("PDF file created successfully."));
       /* // Récupération du chemin d'accès à l'image
            QString imagePath = "C:/Users/maissa/Downloads/logo6.png";

            // Génération du code HTML pour l'image
            QString imgHtml = QString("<img src='%1' width='100' height='100'>").arg(imagePath);

            out <<  "<html>\n"
                "<head>\n"

                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                <<  QString("<title>%1</title>\n").arg("strTitle")
                <<  "</head>\n"
                   " <div><p class=""exempleTexte"">Gestion Des Recherches</p></div>"
                "<body  bgcolor=""#FAEBD7"" link=""#5000A0"">\n";

            // Insertion de l'image en haut à gauche du PDF
            out << imgHtml << "<br><br>";

            out << "<center> <H1>Liste Des Recherches </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";*/


}



void MainWindow::on_pushButton_5_clicked()//chercher
{
    patient p ;
    int cin = ui->lineEdit_12->text().toInt();
    p=p.chercher_patient(cin);
    QStandardItemModel *model = new QStandardItemModel(1, 6, this);
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Numéro de téléphone");
    model->setHeaderData(4, Qt::Horizontal, "Âge");
    model->setHeaderData(5, Qt::Horizontal, "Maladie");

    model->setItem(0, 0, new QStandardItem(QString::number(p.getcin())));
    model->setItem(0, 1, new QStandardItem(p.getnom()));
    model->setItem(0, 2, new QStandardItem(p.getprenom()));
    model->setItem(0, 3, new QStandardItem(QString::number(p.getnum_tel())));
    model->setItem(0, 4, new QStandardItem(p.getage()));
    model->setItem(0, 5, new QStandardItem(p.getmaladie()));
ui->tableView_2->setModel(model);
}




void MainWindow::on_pushButton_6_clicked()//trier
{
    patient p;
        QSqlQueryModel* model = p.trier_nom();
        ui->tableView_3->setModel(model);
}

void MainWindow::on_pushButton_7_clicked()
{
    patient p;
        QSqlQueryModel* model = p.trier_prenom();
        ui->tableView_3->setModel(model);
}


void MainWindow::on_pushButton_3_clicked()//chercher par nom
{

    patient p ;
    QString nom = QString::fromStdString(ui->lineEdit->text().toStdString());
    p=p.chercher_nom(nom);
    QStandardItemModel *model = new QStandardItemModel(1, 6, this);
    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "prenom");
    model->setHeaderData(2, Qt::Horizontal, "nom");
    model->setHeaderData(3, Qt::Horizontal, "Numéro de téléphone");
    model->setHeaderData(4, Qt::Horizontal, "Âge");
    model->setHeaderData(5, Qt::Horizontal, "Maladie");

    model->setItem(0, 0, new QStandardItem(QString::number(p.getcin())));
    model->setItem(0, 1, new QStandardItem(p.getnom()));
    model->setItem(0, 2, new QStandardItem(p.getprenom()));
    model->setItem(0, 3, new QStandardItem(QString::number(p.getnum_tel())));
    model->setItem(0, 4, new QStandardItem(p.getage()));
    model->setItem(0, 5, new QStandardItem(p.getmaladie()));
ui->tableView_2->setModel(model);
}


void MainWindow::on_pushButton_4_clicked()//chercher par prenom
{

        patient p ;
        QString prenom = QString::fromStdString(ui->lineEdit_5->text().toStdString());
        p=p.chercher_prenom(prenom);
        QStandardItemModel *model = new QStandardItemModel(1, 6, this);
        model->setHeaderData(0, Qt::Horizontal, "CIN");
        model->setHeaderData(1, Qt::Horizontal, "prenom");
        model->setHeaderData(2, Qt::Horizontal, "nom");
        model->setHeaderData(3, Qt::Horizontal, "Numéro de téléphone");
        model->setHeaderData(4, Qt::Horizontal, "Âge");
        model->setHeaderData(5, Qt::Horizontal, "Maladie");

        model->setItem(0, 0, new QStandardItem(QString::number(p.getcin())));
        model->setItem(0, 1, new QStandardItem(p.getnom()));
        model->setItem(0, 2, new QStandardItem(p.getprenom()));
        model->setItem(0, 3, new QStandardItem(QString::number(p.getnum_tel())));
        model->setItem(0, 4, new QStandardItem(p.getage()));
        model->setItem(0, 5, new QStandardItem(p.getmaladie()));
    ui->tableView_2->setModel(model);
    }





/*void MainWindow::on_pushButton_8_clicked()
{
    s = new patient();

    s->setWindowTitle("statistique ComboBox");
    s->choix_pie();
    s->show();
}*/
void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM patients WHERE cin  LIKE'"+arg1+"%' or nom  LIKE'"+arg1+"%' or prenom LIKE'"+arg1+"%'");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tableView_2->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("NO MATCH FOUND !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
        // ui->recherche->clear()
}}

void MainWindow::on_pushButton_9_clicked()
{


    patient p;
    QFile file("C:/Users/maissa/Desktop/his.txt");
          if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
               QMessageBox::information(0,"info",file.errorString());
                   QTextStream lecture(&file);
                   ui->textBrowser->setText(lecture.readAll());
                   QString montext = lecture.readAll();
                   QMessageBox::information(nullptr, QObject::tr("Text History is open"),
                               QObject::tr("Text History is successfully displayed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
                   //QMessageBox::information(this, "Fichier", montext);
                   file.close();


}

void MainWindow::on_pushButton_12_clicked()
{
    int cin = ui->lineEdit_3->text().toInt();
    QString nom = ui->lineEdit_8->text();
    QString prenom = ui->lineEdit_9->text();
    int num_tel = ui->lineEdit_4->text().toInt();
    QString genre = ui->lineEdit_5->text();
     QString maladie = ui->lineEdit_6->text();
    QString age = ui->lineEdit_7->text();


patient p;
 p.modifier_patient(cin, nom, prenom, num_tel, maladie, age,genre);
 p.historique(3, nom + " " + prenom);
 // Réinitialiser les champs après l'ajout

}
