#ifndef Arduinoo_H
#define Arduinoo_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>


class Arduino
{
public:     //méthodes de la classe Arduinoo
    Arduino();
    int connect_Arduinoo(); // permet de connecter le PC à Arduinoo
    int close_Arduinoo(); // permet de femer la connexion
    int write_to_Arduinoo( QByteArray ); // envoyer des données vers Arduinoo
    QByteArray read_from_Arduinoo();  //recevoir des données de la carte Arduinoo
    QSerialPort* getserial();   // accesseur
    QString getArduinoo_port_name();
private:
QSerialPort * serial; //Cet objet rassemble des informations (vitesse, bits de données, etc.)
//et des fonctions (envoi, lecture de réception,…) sur ce qu’est une voie série pour Arduinoo.
static const quint16 Arduinoo_uno_vendor_id=9025;
static const quint16 Arduinoo_uno_producy_id=66;
QString Arduinoo_port_name;
bool Arduinoo_is_available;
QByteArray data;  // contenant les données lues à partir d'Arduinoo
void storeDataInSqlite();
void  updatePatients();
};



#endif // Arduinoo_H
