#ifndef LECTORARCHIVOS_CPP
#define LECTORARCHIVOS_CPP

#include <fstream>
#include <string>
using namespace std;

class LectorArchivos{
    public:
        LectorArchivos(string direccion);
        string* getArray();
        int getTopeArray();
    private:
        void rescaleVector(int cont);
        string* archivo;
        int max;
};

string* LectorArchivos::getArray(){
    return this->archivo;
}

int LectorArchivos::getTopeArray(){
    return this->max;
}

LectorArchivos::LectorArchivos(string direccion){
    this->max = 20;
    int contador = 0;

    // Abrir archivo
    ifstream ArchivoLectura(direccion);

    // Si falla cerramos el programa
    if (ArchivoLectura.fail())
        exit(1);

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

#endif // !LECTORARCHIVOS_CPP
