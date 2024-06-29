#include "reglas.h"
#include <stdlib.h>

reglas::reglas(string* paises, int maxPaises, string* Visitas, int maxVist){
    // Seteamos atributos principales
    this->paises = paises;
    this->maxPaises = maxPaises;
    this->maxTiposVisitas = maxVist;
    this->tipoVisitas = Visitas;

    srand(1);   // hay que cambiar esto para cuando este mas avanzado el juego a time null

    setPaisesPermitidos(3);

    //setFechas();
    //setDuracionEstancia();
    //setTipoDeVisita();
    //setEstadoCivil();
}

void reglas::setPaisesPermitidos(int cantidadMinimaPaisesPermitidos){
    // Generar cantidad de paises permitidos:
    int cantidadPaisesPermitidos;
    do{
        cantidadPaisesPermitidos = rand()%this->maxPaises + 1;
    }while(cantidadPaisesPermitidos == maxPaises || cantidadPaisesPermitidos < cantidadMinimaPaisesPermitidos);

    // Preparar el array de paises y su tope
    this->paisesValidos = new int[cantidadPaisesPermitidos];
    this->maxPaisesPermitidos = cantidadPaisesPermitidos;

    // El -1 significa que no tiene cargado ningun dato todavia, es como inicializarlo en 0.
    for (int i = 0; i < cantidadPaisesPermitidos; i++)
        paisesValidos[i] = -1;

    // Seleccionar paises permitidos
    int i = 0;
    while (cantidadPaisesPermitidos){
        do{
            paisesValidos[i] = rand()% this->maxPaises;
        }while(checkRepetidos(paisesValidos[i]));
        
        i++;
        cantidadPaisesPermitidos--;
    }
}

bool reglas::checkRepetidos(int dato){
    for (int i = 0; i < this->maxPaisesPermitidos; i++)
        if (paisesValidos[i] == dato)
            return true;
    return false;
}

int* reglas::getPaisesPermitidos(int &max){
    max = this->maxPaisesPermitidos;
    return this->paisesValidos;
}