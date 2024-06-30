#include "reglas.h"
#include <stdlib.h>

reglas::reglas(string* paises, int maxPaises, string* Visitas, int maxVist, string* EC, int maxEC){
    // # Seteamos atributos principales
    this->paises = paises;
    this->maxPaises = maxPaises;
    this->maxTiposVisitas = maxVist;
    this->tipoVisitas = Visitas;
    this->estadosCiviles = EC;
    this->maxEstadosCiviles = maxEC;
    srand(1);   // hay que cambiar esto para cuando este mas avanzado el juego a time null

    // # Inicializamos las reglas
    setPaisesPermitidos(3);
    setFechasValidas();
    setDuracionEstanciaValida(9,3);
    setTipoDeVisitaValidas();
    setEstadoCivilValidos();
}

void reglas::setEstadoCivilValidos(){
    // Generamos la cantidad de tipos de estados civiles validos
    this->maxEstadosCivilPermitidos = rand()%maxEstadosCiviles + 1;

    // Si obtuvimos la misma cantidad, devuelvo el array original directamente.
    if (this->maxEstadosCivilPermitidos == maxEstadosCiviles)
        this->EstadoCivilValidos = estadosCiviles;
    else
        SeleccionarEstadosCivilesValidos(this->maxEstadosCivilPermitidos);
}

void reglas::SeleccionarEstadosCivilesValidos(int CantidadECValidos){
    this->EstadoCivilValidos = new string[CantidadECValidos];

    for (int i = 0; i < CantidadECValidos; i++)
        EstadoCivilValidos[i] = estadosCiviles[i];
}

void reglas::setTipoDeVisitaValidas(){
    // Generamos la cantidad de tipos de visitas validas
    this->maxVisitasPermitidas = rand()%maxTiposVisitas + 1;

    // Si obtuvimos la misma cantidad, devuelvo el array original directamente.
    if (this->maxVisitasPermitidas == maxTiposVisitas)
        this->tipoDeVisitaValida = tipoVisitas;
    else
        SeleccionarVisitasValidas(this->maxVisitasPermitidas);
}

void reglas::SeleccionarVisitasValidas(int CantidadVisitasValidas){
    this->tipoDeVisitaValida = new string[CantidadVisitasValidas];

    for (int i = 0; i < CantidadVisitasValidas; i++)
        tipoDeVisitaValida[i] = tipoVisitas[i];
}

void reglas::setDuracionEstanciaValida(int max, int min){
    // Duracion de estancia de entre duracion minima X a duracion maxima Y
    int intervalo = max - min;
    duracionDeEstanciaValida = rand()%(intervalo+1) + min;
}

void reglas::setFechasValidas(){
    // Genera fechas de entre 1900 y 2000
    do{
        fechaMax = rand()%100 + 1900;
        fechaMin = rand()%100 + 1900;

        // Si se generan al reves las fechas las intercambio
        if (fechaMax < fechaMin){
            int aux = fechaMin;
            fechaMin = fechaMax;
            fechaMax = aux;
        }

        // Si las fechas son iguales, o la diferencia entre ellas es muy corta, volvemos a generar nuevas.
    }while(fechaMax == fechaMin || (fechaMax - fechaMin) < 20 );
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
    int ocurrencias = 0;
    for (int i = 0; i < this->maxPaisesPermitidos; i++){
        if (paisesValidos[i] == dato)
            ocurrencias++;
        if (ocurrencias == 2)
            return true;
    }
        
    return false;
}

// Getters

int* reglas::getPaisesPermitidos(int &max){
    max = this->maxPaisesPermitidos;
    return this->paisesValidos;
}

string* reglas::getEstadoCivilPermitido(int &max){
    max = this->maxEstadosCivilPermitidos;
    return this->EstadoCivilValidos;
}

string* reglas::getTipoVisitaPermitida(int &max){
    max = this->maxEstadosCivilPermitidos;
    return tipoDeVisitaValida;
}

int reglas::getFechaMinPermitida(){
    return this->fechaMin;
}

int reglas::getFechaMaxPermitida(){
    return this->fechaMax;
}

int reglas::getDuracionEstanciaPermitida(){
    return this->duracionDeEstanciaValida;
}