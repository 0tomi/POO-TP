#include "lectorarchivos.h"
#include <fstream>
#include <QCoreApplication>
#include <QMessageBox>
#include <QString>

string* LectorArchivos::getArray(){
    return this->archivo;
}

int LectorArchivos::getTopeArray(){
    return this->max;
}

LectorArchivos::LectorArchivos(string direccion){
    this->LeerArchivoNuevo(direccion);
}

void LectorArchivos::LeerArchivoNuevo(string direccion){
    this->max = 20;
    int contador = 0;

    // Abrir archivo
    ifstream ArchivoLectura(direccion);

    // Si falla cerramos el programa
    if (ArchivoLectura.fail()){
        QString mensajeError = QString::fromStdString(direccion);
        QMessageBox::critical(nullptr, "Error al leer el siguiente directorio:", mensajeError);
        QCoreApplication::exit(-1);
    }

    // Creamos el array que contendra los this->archivo
    this->archivo = new string[max];

    // Leer archivo
    while (getline(ArchivoLectura, this->archivo[contador])){
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

void LectorArchivos::rescaleVector(int cont){
    string* newVector = new string[this->max];
    for (int i = 0; i < cont; i++)
        newVector[i] = this->archivo[i];

    delete[] this->archivo;
    this->archivo = newVector;
}
