#ifndef PATIENT_H
#define PATIENT_H
#include <QSqlDatabase>
#include <QString>
#include <QSqlQueryModel>
#include <QList>
#include <QStringList>
#include <QtWidgets/QTableView>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QtWidgets/QTableView>
#include <list>
#include <QByteArray>

class patient
{
public:
    patient();
    patient(int cin,QString nom,QString prenom,int num_tel,QString age,QString genre,QString maladie,QPixmap image);


    int getcin();
    QString getnom();
    QString getprenom();
    int getnum_tel();
    QString getage();
    QString getgenre();
     QString getmaladie();
     QPixmap getimage();

     void setcin(int);
    void setnum_tel(int);
    void setprenom(QString );
    void setnom(QString );
    void setage(QString );
    void setgenre(QString );
 void setmaladie(QString );
 void setimage(QPixmap image);




    void ajouter_patient(int cin, QString nom , QString prenom,int num_tel, QString genre , QString maladie, QString age,QPixmap image);

QSqlQueryModel* afficher();
QSqlQueryModel* trier_nom();
QSqlQueryModel*trier_prenom();
    bool supprimer(int);
     void modifier_patient(int,QString,QString,int,QString,QString,QString);
   // void historique(int,QString);
     patient chercher_patient(int cin);
    bool pdf(QWidget *viewport, const QString &fileName);
    patient chercher_nom(QString nom);

patient chercher_prenom(QString prenom);
void historique(int a,QString name);


 QChartView *chartView ;

   void choix_pie();



private :
    int cin;
    QString nom ;
    QString prenom;
    QString maladie;
    QString age;
    QString genre;
    int num_tel;
    QPixmap image;





};
#endif // PATIENT_H
