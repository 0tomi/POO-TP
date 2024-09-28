#include "reglasnivel1.h"
#include <QTime>
#include <QDebug>

ReglasNivel1::ReglasNivel1(): Reglas()
{
    paisesInvalidos = nullptr;
    paisesValidos = nullptr;
    tipoDeVisitaValida = nullptr;
    estadoCivilValidos = nullptr;

    // # Inicializamos las reglas
    setPaisesPermitidos(6);
    setFechasValidas();
    setDuracionEstanciaValida(9,3);
    setTipoDeVisitaValidas();
    setEstadoCivilValidos();
}

ReglasNivel1::ReglasNivel1(quint32 Seed): Reglas()
{
    rand.seed(Seed);
    paisesInvalidos = nullptr;
    paisesValidos = nullptr;
    tipoDeVisitaValida = nullptr;
    estadoCivilValidos = nullptr;

    // # Inicializamos las reglas
    setPaisesPermitidos(6);
    setFechasValidas();
    setDuracionEstanciaValida(9,3);
    setTipoDeVisitaValidas();
    setEstadoCivilValidos();
}

void ReglasNivel1::resetReglas(int cantidadMinimaPaisesPermitidos, quint32 seed)
{
    // Inicializamos la semilla del generador
    rand.seed(seed);

    setPaisesPermitidos(3);
    setFechasValidas();
    setDuracionEstanciaValida(9,3);
    setTipoDeVisitaValidas();
    setEstadoCivilValidos();
}

/// ####################### Generadores de parametros #######################
void ReglasNivel1::generar_Paises(int Cantidad_Paises_Permitidos)
{
    LimpiarDatos(paisesValidos);
    LimpiarDatos(paisesInvalidos);

    if (Cantidad_Paises_Permitidos < 1 || Cantidad_Paises_Permitidos > maxPaises)
        setPaisesPermitidos(rand.bounded(4));
    else
        setPaisesPermitidos(Cantidad_Paises_Permitidos);

    SumarAstana();
}

void ReglasNivel1::generar_Paises(vector<QString>& Lista_PaisesPermitidos)
{
    // Esta funcion no checkea si hay paises repetidos

    LimpiarDatos(paisesValidos);
    LimpiarDatos(paisesInvalidos);

    if (!ValidarDatos(Lista_PaisesPermitidos, 1, maxPaises-2, paises, maxPaises)){
        setPaisesPermitidos(rand.bounded(4));
        return;
    }

    int MAXPAISESInvalidos = maxPaises - Lista_PaisesPermitidos.size();
    this->paisesValidos = new int[Lista_PaisesPermitidos.size()];
    this->paisesInvalidos = new int[MAXPAISESInvalidos];

    int indicesInvalidos = 0, indiceValidos = 0;
    bool PaisValido;
    for (int i = 0; i < maxPaises; ++i){
        PaisValido = false;
        for (int j = 0; j < Lista_PaisesPermitidos.size(); ++j)
            if (paises[i] == Lista_PaisesPermitidos[i])
                PaisValido = true;

        if (PaisValido)
            paisesValidos[indiceValidos++] = i;
        else
            paisesInvalidos[indicesInvalidos++] = i;
    }

    // Sumamos Astana (el pais del juego) al array de paises.
    SumarAstana();
}

void ReglasNivel1::generar_EstadosCiviles(int Cantidad_EstadosCiviles_Permitidos)
{
    LimpiarDatos(estadoCivilValidos);

    int MAXestadosCiviles = 4;
    if (Cantidad_EstadosCiviles_Permitidos < 1 || Cantidad_EstadosCiviles_Permitidos > MAXestadosCiviles)
        setEstadoCivilValidos();
    else{
        this->maxEstadosCivilPermitidos = Cantidad_EstadosCiviles_Permitidos;
        // Si obtuvimos la misma cantidad, devuelvo el array original directamente.
        if (this->maxEstadosCivilPermitidos == MaxEstadosCiviles)
            this->estadoCivilValidos = estadosCiviles;
        else
            SeleccionarEstadosCivilesValidos(this->maxEstadosCivilPermitidos);
    }
}

void ReglasNivel1::generar_EstadosCiviles(vector<QString> &Lista_EstadosCiviles_Permitidos)
{
    // Esta funcion no checkea si hay estados repetidos
    LimpiarDatos(estadoCivilValidos);

    int MAXEstadosCiviles = 4;
    if (!ValidarDatos(Lista_EstadosCiviles_Permitidos, 1, MAXEstadosCiviles-1, estadosCiviles, MAXEstadosCiviles)){
        setEstadoCivilValidos();
        return;
    }

    maxEstadosCivilPermitidos = Lista_EstadosCiviles_Permitidos.size();
    estadoCivilValidos = new QString[maxEstadosCivilPermitidos];

    for (int i = 0; i < maxEstadosCivilPermitidos; ++i)
        estadoCivilValidos[i] = Lista_EstadosCiviles_Permitidos[i];
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
    LimpiarDatos(tipoDeVisitaValida);

    if (Cantidad_Visitas_Permitidas < 1){
        setTipoDeVisitaValidas();
        return;
    }

    this->maxVisitasPermitidas = Cantidad_Visitas_Permitidas;
    // Si obtuvimos la misma cantidad, devuelvo el array original directamente.
    if (this->maxVisitasPermitidas == MaxTipoVisitas)
        this->tipoDeVisitaValida = tipoVisitas;
    else
        SeleccionarVisitasValidas(this->maxVisitasPermitidas);

}

void ReglasNivel1::generar_TiposVisita(vector<QString> &Lista_Visitas_Permitidas)
{
    LimpiarDatos(tipoDeVisitaValida);

    int MAXTiposVisita = 3;
    if (!ValidarDatos(Lista_Visitas_Permitidas, 1, MAXTiposVisita, tipoVisitas, MAXTiposVisita)){
        setTipoDeVisitaValidas();
        return;
    }

    this->maxVisitasPermitidas = Lista_Visitas_Permitidas.size();
    this->tipoDeVisitaValida = new QString [maxVisitasPermitidas];

    for (int i = 0; i < maxVisitasPermitidas; ++i)
        tipoDeVisitaValida[i] = Lista_Visitas_Permitidas[i];
}

/// ####################### Setters de parametros #######################

void ReglasNivel1::setEstadoCivilValidos(){
    // Generamos la cantidad de tipos de estados civiles validos
    this->maxEstadosCivilPermitidos = rand.bounded(MaxEstadosCiviles) + 1;

    // Si obtuvimos la misma cantidad, devuelvo el array original directamente.
    if (this->maxEstadosCivilPermitidos == MaxEstadosCiviles)
        this->estadoCivilValidos = estadosCiviles;
    else
        SeleccionarEstadosCivilesValidos(this->maxEstadosCivilPermitidos);
}

void ReglasNivel1::SeleccionarEstadosCivilesValidos(int CantidadECValidos){
    this->estadoCivilValidos = new QString[CantidadECValidos];
    int sorteo, cantidadEstadosValidos = 0;

    if (CantidadECValidos < 2){
        sorteo = rand.bounded(MaxEstadosCiviles);
        estadoCivilValidos[0] = estadosCiviles[sorteo];
    } else {
        for (int i = 0; i < CantidadECValidos; i++)
            estadoCivilValidos[i] = estadosCiviles[i];
    }
}

void ReglasNivel1::setTipoDeVisitaValidas(){
    // Generamos la cantidad de tipos de visitas validas
    this->maxVisitasPermitidas = rand.bounded(MaxTipoVisitas) +1;

    // Si obtuvimos la misma cantidad, devuelvo el array original directamente.
    if (this->maxVisitasPermitidas == MaxTipoVisitas)
        this->tipoDeVisitaValida = tipoVisitas;
    else
        SeleccionarVisitasValidas(this->maxVisitasPermitidas);
}

void ReglasNivel1::SeleccionarVisitasValidas(int CantidadVisitasValidas){
    tipoDeVisitaValida = new QString[CantidadVisitasValidas];

    if (CantidadVisitasValidas == 1){
        int sorteo = rand.bounded(MaxTipoVisitas);
        tipoDeVisitaValida[0] = tipoVisitas[sorteo];   /// CAMBIOS QUE TENGO QUE HACER
    } else {
        for (int i = 0; i < CantidadVisitasValidas; i++)
            tipoDeVisitaValida[i] = tipoVisitas[i];
    }
}

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
    int cantidadPaisesPermitidos = cantidadMinimaPaisesPermitidos;

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
            paisesValidos[i] = rand.bounded(maxPaises);
        }while(checkRepetidos(paisesValidos[i]));

        i++;
        cantidadPaisesPermitidos--;
    }

    // Crear array de paises no permitidos
    maxPaisesInvalidos = maxPaises - maxPaisesPermitidos;
    paisesInvalidos = new int[maxPaisesInvalidos];
    int Contador = 0;
    for (int i = 0; i < maxPaises; i++){
        if(!checkIfValido(i)){
            paisesInvalidos[Contador] = i;
            Contador++;
        }
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

bool ReglasNivel1::checkIfValido(int indice)
{
    for (int i = 0; i < maxPaisesPermitidos; i++){
        if (indice == paisesValidos[i])
            return true;
    }
    return false;
}

void ReglasNivel1::SumarAstana()
{
    QString * aux = new QString[this->maxPaises+1];
    aux[0] = "Astana";
    for (int i = 1; i < this->maxPaises; i++)
        aux[i] = this->paises[i-1];
    delete[] this->paises;
    this->paises = aux;
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

int *ReglasNivel1::getPaisesInvalidos(int &max) const
{
    max = maxPaisesInvalidos;
    return paisesInvalidos;
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

QString *ReglasNivel1::getTipoDeVisitaValida() const
{
    return tipoDeVisitaValida;
}

int ReglasNivel1::getMaxVisitasPermitidas() const
{
    return maxVisitasPermitidas;
}

// Destructor
ReglasNivel1::~ReglasNivel1()
{
    delete[] paisesValidos;
    if (tipoDeVisitaValida != tipoVisitas)
        delete[] tipoDeVisitaValida;
    if (estadoCivilValidos != estadosCiviles)
        delete[] estadoCivilValidos;
}
