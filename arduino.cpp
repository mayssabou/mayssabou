#include "arduino.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QObject>
#include <QSerialPort>
Arduino::Arduino()
{
    data="";
    Arduinoo_port_name="";
    Arduinoo_is_available=false;
    serial=new QSerialPort;
}

QString Arduino::getArduinoo_port_name()
{
    return Arduinoo_port_name;
}

QSerialPort *Arduino::getserial()
{
   return serial;
}
int Arduino::connect_Arduinoo()
{   // recherche du port sur lequel la carte Arduinoo identifée par  Arduinoo_uno_vendor_id
    // est connectée
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == Arduinoo_uno_vendor_id && serial_port_info.productIdentifier()
                       == Arduinoo_uno_producy_id) {
                   Arduinoo_is_available = true;
                   Arduinoo_port_name=serial_port_info.portName();
               } } }
        qDebug() << "Arduinoo_port_name is :" << Arduinoo_port_name;
        if(Arduinoo_is_available){ // configuration de la communication ( débit...)
            serial->setPortName(Arduinoo_port_name);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
                serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
                serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
                serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}

int Arduino::close_Arduinoo()

{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;


}


 QByteArray Arduino::read_from_Arduinoo()
{
     QByteArray data;

         if (serial->isReadable()) {
             serial->waitForReadyRead(10);
             data = serial->readAll();

             // Convertir la chaîne de caractères reçue en un nombre entier
             int patientsCount = data.toInt();

             // Insérer le nombre de patients captés dans la base de données à l'aide d'une requête SQL INSERT
             QSqlQuery query;
             query.prepare("INSERT INTO patients (nbrpatients) VALUES (:patientsCount)");
             query.bindValue(":patientsCount", patientsCount);

             if (query.exec()) {
                 qDebug() << "Data inserted successfully";
             } else {
                 qDebug() << "Failed to insert data";
             }
         }

         return data;
     }





int Arduino::write_to_Arduinoo(QByteArray d)
{ if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduinoo
    }else{
        qDebug() << "Couldn't write to serial!";
    }
    QSqlQuery query("SELECT nbr_participants FROM activite");
    if(query.exec() && query.first()) {
        int participantsCount = query.value(0).toInt();

        // Convertir le nombre de participants en une chaîne de caractères
        QByteArray data = QByteArray::number(participantsCount);

        // Envoyer la chaîne de caractères à l'Arduino
        if(serial->isWritable()) {
            serial->write(data);
        } else {
            qDebug() << "Couldn't write to serial!";
        }
    } /*else {
        qDebug() << "Error retrieving number of participants from database: " << query.lastError().text();*/
}
