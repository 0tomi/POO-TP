#include "lectorarchivos.h"
#include <QCoreApplication>
#include <QMessageBox>
#include <QFile>

QString* LectorArchivos::getArray(){
    return this->archivo;
}

int LectorArchivos::getTopeArray(){
    return this->max;
}

LectorArchivos::LectorArchivos(QString direccion){
    this->LeerArchivoNuevo(direccion);
}

void LectorArchivos::LeerArchivoNuevo(QString direccion){
    this->max = 20;
    int contador = 0;

    // Abrir archivo
    QFile ArchivoLectura(direccion);
    if (!ArchivoLectura.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(nullptr, "Error al leer el siguiente directorio:", direccion);
        QCoreApplication::exit(-1);
    }

    // Creamos el array que contendra los this->archivo
    this->archivo = new QString[max];

    // Leo usando QTextStream
    QTextStream in(&ArchivoLectura);
    while (!in.atEnd()){
        archivo[contador] = in.readLine();
        contador++;

        // Si el array se nos queda chico, lo incrementamos
        if (contador == max){
            max += 20;
            rescaleVector(contador);
        }
    }

    // Si el array quedo sobredimensionado, lo acortamos
    if (contador < max){
        this->max = contador;
        rescaleVector(contador);
    }

    ArchivoLectura.close();
}

std::vector<QString> LectorArchivos::getVector(QString direccion)
{
    this->LeerArchivoNuevo(direccion);
    return this->getVector();
}

std::vector<QString> LectorArchivos::getVector() const
{
    std::vector<QString> Vector;
    for (int i =0; i < this->max; ++i)
        Vector.push_back(this->archivo[i]);

    return Vector;
}

std::list<QString> LectorArchivos::getList(QString direccion)
{
    this->LeerArchivoNuevo(direccion);
    return this->getList();
}

std::list<QString> LectorArchivos::getList() const
{
    std::list<QString> Lista;
    for (int i =0; i < this->max; ++i)
        Lista.push_back(this->archivo[i]);

    return Lista;
}

void LectorArchivos::rescaleVector(int cont){
    QString* newVector = new QString[this->max];
    for (int i = 0; i < cont; i++)
        newVector[i] = this->archivo[i];

    delete[] this->archivo;
    this->archivo = newVector;
}
