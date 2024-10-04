#include "logs.h"

Logs::Logs() {
    QDir directorio;
    if (directorio.mkpath(this->DireccionCarpeta)){
        qDebug() << "creada";
    } else{
        qDebug() << "no creada";
    }
    QFile archivoNumLogs(this->CantLogsTXT);
    if(!archivoNumLogs.open(QIODevice::Text | QIODevice::ReadWrite)){
        QMessageBox::critical(nullptr, "Error al abrir el archivo de cantidad de logs en la direccion:", this->CantLogsTXT);
        QCoreApplication::exit(-1);
    }
    QTextStream stream(&archivoNumLogs);
    if(archivoNumLogs.size() != 0){
        stream >> this->cantLogs;
    } else{
        this->cantLogs = 0;
    }

    archivoNumLogs.resize(0); // para reescribir
    stream << cantLogs + 1;

    archivoNumLogs.close();
    qDebug() << "Directorio donde se guardan los logs: " << this->DireccionCarpeta;
}

void Logs::SaveLogs()
{
    QFile archivo(this->DireccionCarpeta + "/" + QString::number(this->cantLogs) + ".txt");
    if(!archivo.open(QIODevice::Text | QIODevice::Append)){
        QMessageBox::critical(nullptr, "Error al abrir el archivo de logs en la direccion:", this->DireccionCarpeta);
        QCoreApplication::exit(-1);
    }
    QTextStream stream(&archivo);
    for (QString& log : this->VectorLogs){
        stream << log;
    }
    this->VectorLogs.clear();
    archivo.close();
}

Logs::~Logs()
{
}

void Logs::RecibirLogs(QString Log)
{
    qDebug() << "Log Recibido: " << Log;
    QString CompleteLog = "[" + QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss") + "]  " + Log + "\n";
    this->VectorLogs.push_back(CompleteLog);
    if(this->VectorLogs.size() == 1 || Log.contains("salir")){
        SaveLogs();
    }
}
