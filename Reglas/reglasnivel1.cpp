#include "reglasnivel1.h"
#include <ctime>
#include <QDebug>

ReglasNivel1::ReglasNivel1(AtributosComunes* atributos){
    // # Seteamos atributos principales
    this->paises = atributos->getPaises(this->maxPaises);
    this->tipoVisitas = atributos->getVisitas(this->maxTiposVisitas);
    this->estadosCiviles = atributos->getEstadosCiviles(this->maxEstadosCiviles);

    // Inicializamos la semilla del generador
    quint32 Semilla = static_cast<quint32>(time(NULL));
    Random.seed(Semilla);

    // # Inicializamos las reglas
    setPaisesPermitidos(3);
    setFechasValidas();
    setDuracionEstanciaValida(9,3);
    setTipoDeVisitaValidas();
    setEstadoCivilValidos();
}



void ReglasNivel1::resetReglas(int cantidadMinimaPaisesPermitidos)
{
    // Inicializamos la semilla del generador
    quint32 Semilla = static_cast<quint32>(time(NULL));
    Random.seed(Semilla);

    setPaisesPermitidos(3);
    setFechasValidas();
    setDuracionEstanciaValida(9,3);
    setTipoDeVisitaValidas();
    setEstadoCivilValidos();
}

void ReglasNivel1::setEstadoCivilValidos(){
    // Generamos la cantidad de tipos de estados civiles validos
    this->maxEstadosCivilPermitidos = Random.bounded(1,maxEstadosCiviles+1);

    // Si obtuvimos la misma cantidad, devuelvo el array original directamente.
    if (this->maxEstadosCivilPermitidos == maxEstadosCiviles)
        this->estadoCivilValidos = estadosCiviles;
    else
        SeleccionarEstadosCivilesValidos(this->maxEstadosCivilPermitidos);
}

void ReglasNivel1::SeleccionarEstadosCivilesValidos(int CantidadECValidos){
    this->estadoCivilValidos = new QString[CantidadECValidos];
    int sorteo, cantidadEstadosValidos = 0;

    if (CantidadECValidos < 2){
        sorteo = Random.bounded(maxEstadosCiviles);
        estadoCivilValidos[0] = estadosCiviles[sorteo];
    } else {
        for (int i = 0; i < CantidadECValidos; i++)
            estadoCivilValidos[i] = estadosCiviles[i];
    }
}

void ReglasNivel1::setTipoDeVisitaValidas(){
    // Generamos la cantidad de tipos de visitas validas
    this->maxVisitasPermitidas = Random.bounded(1,maxTiposVisitas+1);

    // Si obtuvimos la misma cantidad, devuelvo el array original directamente.
    if (this->maxVisitasPermitidas == maxTiposVisitas)
        this->tipoDeVisitaValida = tipoVisitas;
    else
        SeleccionarVisitasValidas(this->maxVisitasPermitidas);
}

void ReglasNivel1::SeleccionarVisitasValidas(int CantidadVisitasValidas){
    tipoDeVisitaValida = new QString[CantidadVisitasValidas];

    if (CantidadVisitasValidas < 2){
        int sorteo = Random.bounded(maxTiposVisitas);
        tipoDeVisitaValida[0] = tipoVisitas[sorteo];   /// CAMBIOS QUE TENGO QUE HACER
    } else {
        for (int i = 0; i < CantidadVisitasValidas; i++)
            tipoDeVisitaValida[i] = tipoVisitas[i];
    }
}

void ReglasNivel1::setDuracionEstanciaValida(int max, int min){
    // Duracion de estancia de entre duracion minima X a duracion maxima Y
    duracionDeEstanciaValida = Random.bounded(min, max);
}

void ReglasNivel1::setFechasValidas(){
    // Genera fechas de entre 1900 y 2000
    do{
        fechaMax = Random.bounded(1900,2000);
        fechaMin = Random.bounded(1900,2000);

        // Si se generan al reves las fechas las intercambio
        if (fechaMax < fechaMin){
            int aux = fechaMin;
            fechaMin = fechaMax;
            fechaMax = aux;
        }

        // Si las fechas son iguales, o la diferencia entre ellas es muy corta, volvemos a generar nuevas.
    }while(fechaMax == fechaMin || (fechaMax - fechaMin) < 20 );
}

void ReglasNivel1::setPaisesPermitidos(int cantidadMinimaPaisesPermitidos){
    // Generar cantidad de paises permitidos:
    int cantidadPaisesPermitidos;
    do{
        cantidadPaisesPermitidos = Random.bounded(1,maxPaises+1);
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
            paisesValidos[i] = Random.bounded(maxPaises);
        }while(checkRepetidos(paisesValidos[i]));

        i++;
        cantidadPaisesPermitidos--;
    }
}

bool ReglasNivel1::checkRepetidos(int dato){
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

int* ReglasNivel1::getPaisesPermitidos(int &max) const{
    max = this->maxPaisesPermitidos;
    return this->paisesValidos;
}

QString* ReglasNivel1::getEstadoCivilPermitido(int &max) const{
    max = this->maxEstadosCivilPermitidos;
    return this->estadoCivilValidos;
}

int ReglasNivel1::getFechaMinPermitida(){
    return this->fechaMin;
}

int ReglasNivel1::getFechaMaxPermitida(){
    return this->fechaMax;
}

int ReglasNivel1::getDuracionEstanciaPermitida(){
    return this->duracionDeEstanciaValida;
}

// Destructor
ReglasNivel1::~ReglasNivel1()
{
    delete[] paisesValidos;
    delete[] tipoDeVisitaValida;
    delete[] estadoCivilValidos;
}

QString *ReglasNivel1::getTipoDeVisitaValida() const
{
    return tipoDeVisitaValida;
}

int ReglasNivel1::getMaxVisitasPermitidas() const
{
    return maxVisitasPermitidas;
}