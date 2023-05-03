#include "patient.h"
#include <QDebug>
#include <QObject>
#include <QMessageBox>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QTextStream>
#include <QString>
#include <QSqlQuery>
#include "connection.h"
#include <QtWidgets>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QList>
#include <QStringList>
#include <QApplication>
#include <QFile>
#include <QTextDocument>
#include <QTextCursor>
#include <QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtGui>
#include <QtWidgets>
#include <QPdfWriter>
#include <QPrinter>
#include <QPainter>
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
#include <mainwindow.h>
#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCore/QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtCore/QList>
#include <QtCore/QMap>
#include "ui_mainwindow.h"
#include"image.h"


patient::patient()
{
cin = 0;
nom = "";
prenom = "";
maladie = "";
age = "";
num_tel = 0;
genre = "";
image = QPixmap();
}


patient::patient(int cin, QString nom, QString prenom, int num_tel, QString genre, QString age, QString maladie,QPixmap image)
{
this->cin = cin;
this->nom = nom;
this->prenom = prenom;
this->num_tel = num_tel;
this->genre = genre;
this->maladie = maladie;
this->age = age;
this->image = image;
}

//getters
int patient::getcin() { return cin; }
QString patient::getnom() { return nom; }
QString patient::getprenom() { return prenom; }
int patient::getnum_tel() { return num_tel; }
QString patient::getgenre() { return genre; }
QString patient::getmaladie() { return maladie; }
QString patient::getage() { return age; }
QPixmap patient::getimage() { return image; }

//setters
void patient::setcin(int cin) { this->cin = cin; }
void patient::setnum_tel(int num_tel) { this->num_tel = num_tel; }
void patient::setnom(QString nom) { this->nom = nom; }
void patient::setprenom(QString prenom) { this->prenom = prenom; }
void patient::setgenre(QString genre) { this->genre = genre; }
void patient::setmaladie(QString maladie) { this->maladie = maladie; }
void patient::setage(QString age) { this->age = age; }
void patient::setimage(QPixmap image) { this->image = image; }



//////////////////////cruds ////////////

void patient::ajouter_patient(int cin, QString nom , QString prenom, int num_tel, QString genre , QString maladie, QString age, QPixmap image)
{
   QSqlQuery query;
   QString cin_string = QString::number(cin);
   QString num_tel_string = QString::number(num_tel);

   query.prepare("INSERT INTO patients (cin, nom, prenom, num_tel, age, maladie, genre, image) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
   query.bindValue(0, cin_string);
   query.bindValue(1, nom);
   query.bindValue(2, prenom);
   query.bindValue(3, num_tel_string);
   query.bindValue(4, age);
   query.bindValue(5, maladie);
   query.bindValue(6, genre);
   QByteArray imageByteArray;
   QBuffer buffer(&imageByteArray);
   buffer.open(QIODevice::WriteOnly);
   image.save(&buffer, "PNG"); // save the pixmap as a PNG to the buffer
   query.bindValue(7, imageByteArray);

  query.exec();
}
 bool patient::supprimer(int cin)
{
QSqlQuery query;
// sélectionner le patient par son cin //
query.prepare("SELECT * FROM patients WHERE cin = :cin");
query.bindValue(":cin", cin);
if (!query.exec())
{
//qDebug() << "Erreur lors de la sélection du patient à supprimer : " << query.lastError().text();
return false;
}
if (query.next())
{
// le patient existe, donc on peut le supprimer //
query.prepare("DELETE FROM patients WHERE cin = :cin");
query.bindValue(":cin", cin);
if (!query.exec())
{
//qDebug() << "Erreur lors de la suppression du patient : " << query.lastError().text();
return false;
}
else
{
qDebug() << "Patient supprimé avec succès !";
return true;
}
}
else
{
QMessageBox::warning(nullptr, "Patient introuvable !", "Le patient que vous voulez supprimer n'existe pas !");
return false;
}
}


void patient::modifier_patient(int cin, QString nom , QString prenom,int num_tel, QString genre , QString maladie, QString age)
 {
    QSqlQuery query;
    QString cin_string=QString::number(cin);
    QString num_tel_string=QString::number(num_tel);
 query.prepare("update patients set nom=:nom,prenom=:prenom,num_tel=:num_tel,genre=:genre,age=:age,maladie=:maladie WHERE cin=:cin");

 //query.exec();
query.bindValue(":cin",cin);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":num_tel", num_tel);
query.bindValue(":genre", genre);
query.bindValue(":age",age);
query.bindValue(":maladie",maladie);
query.exec();

}

QSqlQueryModel* patient::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();


  model->setQuery("SELECT* FROM patients ");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("age "));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("genre"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("maladie "));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("num_tel "));
  model->setHeaderData(7, Qt::Horizontal, QObject::tr("Image"));


  return  model;


}

bool patient::pdf(QWidget *viewport, const QString &fileName)
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QPainter painter(&printer);

    viewport->render(&painter);

    return true;
}
patient patient::chercher_patient(int cin)
 {

        patient p1;
int cas;
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT * FROM PATIENTS  WHERE cin = :cin");
        checkQuery.bindValue(":cin",cin);

        if (checkQuery.exec())
        {

            if (checkQuery.next())
            { QMessageBox msgBox;
                msgBox.setText("client trouvee" );
                msgBox.exec();
                p1.setcin(checkQuery.value(0).toInt());
               p1.setnom(checkQuery.value(1).toString());;
                p1.setprenom(checkQuery.value(2).toString());
                p1.setnum_tel(checkQuery.value(3).toInt());
                p1.setage(checkQuery.value(4).toString());
                p1.setmaladie(checkQuery.value(5).toString());
                cas=4;
            // historique(cas,p.getnom()+""+c1.getprenom());


                return p1 ;
            }
        }
        else
        {
            qDebug() << "User not found:" << checkQuery.lastError();
        }
p1.setnom("vide");
return p1;
      }
patient patient::chercher_nom(QString nom)
{
    patient p1;
    int cas;
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM PATIENTS  WHERE nom = :nom");
    checkQuery.bindValue(":nom", nom);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            QMessageBox msgBox;
            msgBox.setText("Patient trouvé");
            msgBox.exec();
            p1.setcin(checkQuery.value(0).toInt());
            p1.setnom(checkQuery.value(1).toString());
            p1.setprenom(checkQuery.value(2).toString());
            p1.setnum_tel(checkQuery.value(3).toInt());
            p1.setage(checkQuery.value(4).toString());
            p1.setmaladie(checkQuery.value(5).toString());
            cas = 4;
            // historique(cas,p.getnom()+""+c1.getprenom());

            return p1;
        }
    }
    else
    {
        qDebug() << "User not found:" << checkQuery.lastError();
    }

    p1.setnom("vide");
    return p1;
}
patient patient::chercher_prenom(QString prenom)
{
    patient p1;
    int cas;
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM PATIENTS  WHERE prenom = :prenom");
    checkQuery.bindValue(":prenom", prenom);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            QMessageBox msgBox;
            msgBox.setText("Patient trouvé");
            msgBox.exec();
            p1.setcin(checkQuery.value(0).toInt());
            p1.setnom(checkQuery.value(1).toString());
            p1.setprenom(checkQuery.value(2).toString());
            p1.setnum_tel(checkQuery.value(3).toInt());
            p1.setage(checkQuery.value(4).toString());
            p1.setmaladie(checkQuery.value(5).toString());
            cas = 4;
            // historique(cas,p.getnom()+""+c1.getprenom());

            return p1;
        }
    }
    else
    {
        qDebug() << "User not found:" << checkQuery.lastError();
    }

    p1.setnom("vide");
    return p1;
}
QSqlQueryModel* patient::trier_nom()
{

QSqlQueryModel* model=new QSqlQueryModel();

  model->setQuery("SELECT cin, prenom, nom, age, genre, maladie, num_tel FROM patients ORDER BY nom ASC");

  model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("age "));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("genre"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("maladie "));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("num_tel "));
  return  model;


}
QSqlQueryModel* patient::trier_prenom()
{

QSqlQueryModel* model=new QSqlQueryModel();

  model->setQuery("SELECT cin, prenom, nom, age, genre, maladie, num_tel FROM patients ORDER BY prenom ASC");

  model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("age "));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("genre"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("maladie "));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("num_tel "));
  return  model;

}

//pie chart
    void patient::choix_pie()
    {
    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;

    q1.prepare("SELECT * FROM patients");
    q1.exec();

    q2.prepare("SELECT * FROM patients WHERE maladie='a'");
    q2.exec();

    q3.prepare("SELECT * FROM patients WHERE maladie='b'");
    q3.exec();

    q4.prepare("SELECT * FROM patients WHERE maladie='c' ");
    q4.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;

    // Define slices and percentage of whole they take up
    QPieSeries *series = new QPieSeries();
    series->append("a",c1);
    series->append("b",c2);
    series->append("c",c3);




    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();


    // Used to display the chart
     //QChartView *chartView ;
    //chartView = new QChartView(chart,ui->graphicsView);
    //chartView->setRenderHint(QPainter::Antialiasing);
    //chartView->setMinimumSize(400,400);

    //chartView->show();
    }
    void patient:: historique(int a,QString name)
    {  QString text;
        if(a==1)
          { text=QString(" le client  '%1'a ete ajouté \n ").arg(name);}

        else if(a==3)
          { text=QString(" le client  '%1' a ete modifié \n ").arg(name);}


    else if(a==2) { text=QString(" le client  '%1'   a ete supprimé \n ").arg(name);}

        else if(a==4) { text=QString(" vous avez recherché le client '%1' \n ").arg(name);}

    QSqlQuery query;

    QDate date = QDate::currentDate();
    QString formatteddate = date.toString("dd:MM:yyyy");
    QFile file ("C:/Users/maissa/Desktop/his.txt");
       if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
        qDebug()<<"erreur";
       QTextStream out(&file);
       out << formatteddate+"\n"<<text<<endl;


    }










