#include "reglasnivel1.h"
#include "qlabel.h"
#include <QTime>
#include <QDebug>

ReglasNivel1::ReglasNivel1(): Reglas()
{
    tipoDeVisitaValida = nullptr;
    // # Inicializamos las reglas
    setPaisesPermitidos(6);
    setFechasValidas();
    setDuracionEstanciaValida(9,3);
    generar_EstadosCiviles(2);
    generar_TiposVisita(2);
}

ReglasNivel1::ReglasNivel1(quint32 Seed): Reglas()
{
    rand.seed(Seed);
    tipoDeVisitaValida = nullptr;

    // # Inicializamos las reglas
    setPaisesPermitidos(6);
    setFechasValidas();
    setDuracionEstanciaValida(9,3);
    generar_EstadosCiviles(2);
    generar_TiposVisita(2);
}

void ReglasNivel1::resetReglas(int cantidadMinimaPaisesPermitidos, quint32 seed)
{
    // Inicializamos la semilla del generador
    rand.seed(seed);

    setPaisesPermitidos(3);
    setFechasValidas();
    setDuracionEstanciaValida(9,3);
    generar_EstadosCiviles(2);
    generar_TiposVisita(2);
}

/// ####################### Generadores de parametros #######################
void ReglasNivel1::generar_Paises(int Cantidad_Paises_Permitidos)
{
    LimpiarDatos(PaisesValidos);
    LimpiarDatos(PaisesInvalidos);

    if (Cantidad_Paises_Permitidos < 1 || Cantidad_Paises_Permitidos > maxPaises)
        setPaisesPermitidos(rand.bounded(4));
    else
        setPaisesPermitidos(Cantidad_Paises_Permitidos);

    SumarAstana();
}

void ReglasNivel1::generar_EstadosCiviles(int Cantidad_EstadosCiviles_Permitidos)
{
    estadosCivilesValidos.clear();
    vector EstadosCiviles = {estadosCiviles[0], estadosCiviles[1], estadosCiviles[2], estadosCiviles[3]};
    vector <parDatos> EstadosCivilesPar;
    crearParDatos(EstadosCiviles, EstadosCivilesPar);

    Cantidad_EstadosCiviles_Permitidos = checkCondiciones(Cantidad_EstadosCiviles_Permitidos, 1, EstadosCivilesPar);
    estadosCivilesValidos = generarPermitido(Cantidad_EstadosCiviles_Permitidos, EstadosCivilesPar);
    estadosCivilesInvalidos = generarNoPermitido(EstadosCivilesPar);
}

void ReglasNivel1::generar_Fechas(int Rango)
{
    if (Rango == 0){
        setFechasValidas();
        return;
    }

    this->fechaMin = rand.bounded(1900,2000);
    this->fechaMax = this->fechaMin + Rango;
}

void ReglasNivel1::set_Fechas(int FechaMinima, int FechaMaxima)
{
    this->fechaMin = FechaMinima;
    this->fechaMax = FechaMaxima;
}

void ReglasNivel1::generar_DuracionEstancia(int duracion)
{
    if (duracion < 1)
        setDuracionEstanciaValida(3, 9);
    else{
        this->duracionDeEstanciaValida = duracion;
    }
}

void ReglasNivel1::generar_TiposVisita(int Cantidad_Visitas_Permitidas)
{
    tiposVistaValida.clear();
    vector TiposVisita = {tipoVisitas[0], tipoVisitas[1], tipoVisitas[2]};
    vector <parDatos> TiposVisitaPar;
    crearParDatos(TiposVisita, TiposVisitaPar);
    Cantidad_Visitas_Permitidas = checkCondiciones(Cantidad_Visitas_Permitidas, 1, TiposVisitaPar);
    tiposVistaValida = generarPermitido(Cantidad_Visitas_Permitidas, TiposVisitaPar);
    tiposVisitaInvalida = generarNoPermitido(TiposVisitaPar);
}

/// ####################### Setters de parametros #######################
void ReglasNivel1::setDuracionEstanciaValida(int max, int min){
    // Duracion de estancia de entre duracion minima X a duracion maxima Y
    duracionDeEstanciaValida = rand.bounded(min, max);
}

void ReglasNivel1::setFechasValidas(){
    // Genera fechas de entre 1900 y 2000
    do{
        fechaMax = rand.bounded(1900,2000);
        fechaMin = rand.bounded(1900,2000);

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


    crearParDatos(this->paises, this->parpaisesValidos);
    this->maxPaisesPermitidos = cantidadMinimaPaisesPermitidos;

    this->PaisesValidos = generarVector(generarPermitido(this->maxPaisesPermitidos,this->parpaisesValidos));

    crearParDatos(this->paises,this->parpaisesInvalidos);

    this->PaisesInvalidos = generarVector(generarNoPermitido(this->parpaisesInvalidos));
}

/*bool ReglasNivel1::checkRepetidos(int dato){
    int ocurrencias = 0;
    for (int i = 0; i < this->maxPaisesPermitidos; i++){
        if (PaisesValidos[i] == dato)
            ocurrencias++;
        if (ocurrencias == 2)
            return true;
    }

    return false;
}*/

/*bool ReglasNivel1::checkIfValido(int indice)
{
    for (int i = 0; i < maxPaisesPermitidos; i++){
        if (indice == PaisesValidos[i])
            return true;
    }
    return false;
}*/

void ReglasNivel1::SumarAstana()
{
    this->paises.push_back("astana");
}

// Getters
vector<QString> ReglasNivel1::getPaisesPermitidos() const{
    return this->PaisesValidos;
}

vector<QString> ReglasNivel1::getEstadoCivilPermitido() const{
    return this->estadoCivilValidos;
}

vector<QString> ReglasNivel1::getPaisesInvalidos() const
{
    return this->PaisesInvalidos;
}

vector<QString> ReglasNivel1::getEstadoCivilInvalido() const
{
    return generarVector(this->estadosCivilesInvalidos);
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

vector<QString>ReglasNivel1::getTipoDeVisitaValida() const
{
    return generarVector(this->tiposVistaValida);
}

int ReglasNivel1::getMaxVisitasPermitidas() const
{
    return tiposVistaValida.size();
}

// Destructor
ReglasNivel1::~ReglasNivel1()
{

}
