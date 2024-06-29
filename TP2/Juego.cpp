#include <fstream>
#include "Juego.h"

Juego::Juego(){
    this->maxPaises = 20;
    int contadorPaises = 0;
    std::string direccionPaises = "./paises.txt";
    ifstream Paises(direccionPaises);
    if (Paises.fail())
        exit(5);

    this->paises = new std::string[maxPaises];
    
    while (getline(Paises, this->paises[contadorPaises])){
        contadorPaises++;
        
        if (contadorPaises == maxPaises){
            maxPaises += 20;
            this->rescaleVector(this->paises, this->maxPaises);
        }
    }

    if (contadorPaises < this->maxPaises)
        this->rescaleVector(this->paises, contadorPaises);
    this->maxPaises = contadorPaises;
}

std::string* Juego::rescaleVector(std::string* &vector, int newMax){
    std::string* newVector = new std::string[newMax];
    


}