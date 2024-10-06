#include "generador_nuevaestancia.h"

#include <QTime>

Generador_NuevaEstancia::Generador_NuevaEstancia(): random(QTime::currentTime().msec()) {}

Generador_NuevaEstancia::~Generador_NuevaEstancia() {
    this->paisesPaso.clear();
    //this->paisesPasoInvalidos.clear();
    this->bienesTransp.clear();
    //this->bienesTranspInvalidos.clear();
    ocupacion.clear();
    //ocupacionInvalida.clear();
    this->reglasLvl4 = nullptr;
}

void Generador_NuevaEstancia::inicializadorNivel4(ReglasNivel4 *reglasLvl4, int dificultad, quint32 intSeed) {
    random.seed(intSeed); // inicializo semilla
    Dificultad = dificultad;
    
    auto paisesValidos = reglasLvl4->getPaisesPermitidos();
    paisesPaso = makeTrio(reglasLvl4->getPaises(), paisesValidos);
    maxPaisesValidos = paisesValidos.size();

    auto bienesValidos = reglasLvl4->getBienesTransportadosPermitidos();
    bienesTransp = makeTrio(reglasLvl4->getBienes(), bienesValidos);
    maxBienesValidos = bienesValidos.size();

    auto ocupacionesValidas = reglasLvl4->getOcupacionPermitidos();
    this->ocupacion = makeTrio(reglasLvl4->getOcupaciones(), ocupacionesValidas);
    maxOcupacionesValidas = ocupacionesValidas.size();

    this->reglasLvl4 = reglasLvl4;
}

NuevaEstancia* Generador_NuevaEstancia::getNuevaEstancia(Estancia* actualEstancia, bool valido) {
    estanciaActual = actualEstancia;
    SortearPaginasFalsas(valido);

    QString fraseCaso0P = "No posee paises de paso";
    auto PaisesPaso = generarDocumento(this->paisesPaso, fraseCaso0P, maxPaisesValidos, ValidezPaginas[0]);

    QString fraseCaso0B = "No transporta bienes";
    auto Bienes = generarDocumento(this->bienesTransp, fraseCaso0B, maxBienesValidos, ValidezPaginas[1]);

    QString fraseCaso0O = "Desocupado";
    auto Ocupacion = generarDocumento(this->ocupacion, fraseCaso0O, maxOcupacionesValidas, ValidezPaginas[2]);
    
    NuevaEstancia* newEst = new NuevaEstancia(actualEstancia, PaisesPaso, Bienes, Ocupacion);
    return newEst;
}

void Generador_NuevaEstancia::SortearPaginasFalsas(bool Validez)
{
    for (int i = 0; i < 3; i++)
        ValidezPaginas[i] = true;

    if (Validez)
        return;

    int CantidadPaginasFalsas;
    switch(Dificultad){
    case 1: CantidadPaginasFalsas = 3;
        break;
    case 3:
        CantidadPaginasFalsas = 1;
        break;
    default: CantidadPaginasFalsas = 2;
    }

    if (!estanciaActual->getValidez())
        CantidadPaginasFalsas--;

    int sorteo, CantidadOriginal = CantidadPaginasFalsas;
    while (CantidadPaginasFalsas){
        for (int i = 0; i < 3; i++){
            sorteo = random.bounded(10);
            if (sorteo < 5)
                ValidezPaginas[i] = true;
            else {
                ValidezPaginas[i] = false;
                CantidadPaginasFalsas--;
            }
        }

        if (CantidadPaginasFalsas)
            CantidadPaginasFalsas = CantidadOriginal;
    }
}

vector<Generador_NuevaEstancia::trioDatos> Generador_NuevaEstancia::makeTrio(const vector<QString> &listaOriginal, const vector<QString> &listaPermit)
{
    vector<trioDatos> vector2return;
    for (const auto& element: listaOriginal){
        auto permitido = esPermitido(element, listaPermit);
        vector2return.push_back({element, permitido, false});
    }

    return vector2return;
}

void Generador_NuevaEstancia::resetTrio(vector<trioDatos> &trio)
{
    for (auto& elemento: trio)
        elemento.Insertado = false;
}

bool Generador_NuevaEstancia::esPermitido(QString dato, const vector<QString> &listaPermit)
{
    for (const auto& element: listaPermit)
        if (dato == element)
            return true;
    return false;
}

vector<QString> Generador_NuevaEstancia::generarDocumento(vector<trioDatos> &listaOriginal, QString& fraseCaso0, int MaxPermitido, bool Validez)
{
    vector<QString> lista2generar;
    if (Validez) {
        if (MaxPermitido == 0)
            lista2generar.push_back(fraseCaso0);
        else
            generarListaConDatosVerdaderos(lista2generar, listaOriginal, fraseCaso0, MaxPermitido);
    } else generarListaConDatosFalsos(lista2generar, listaOriginal, fraseCaso0, MaxPermitido);

    return lista2generar;
}

void Generador_NuevaEstancia::generarListaConDatosVerdaderos(vector<QString>& lista2Generar, vector<trioDatos> &listaOriginal, QString& fraseCaso0, int MaxPermitido)
{
    resetTrio(listaOriginal);
    int MAX;
    if (MaxPermitido < MAX_OBJETOS)
        MAX = MaxPermitido;
    else MAX = MAX_OBJETOS;

    int cantidadObjetos = random.bounded(MAX);
    if (MaxPermitido == 1){
        int sorteo = random.bounded(10);
        if (sorteo < 5)
            cantidadObjetos = 1;
    }

    if (cantidadObjetos == 0)
        return lista2Generar.push_back(fraseCaso0);

    lista2Generar.resize(cantidadObjetos);
    int maxObjetos = listaOriginal.size();
    int sorteo, i = 0;
    while (cantidadObjetos){
        do{
            sorteo = random.bounded(maxObjetos);
            lista2Generar[i] = listaOriginal[sorteo].dato;
        }while (listaOriginal[sorteo].Insertado || !listaOriginal[sorteo].Permitido);
        listaOriginal[sorteo].Insertado = true;
        i++; cantidadObjetos--;
    }
}

void Generador_NuevaEstancia::generarListaConDatosFalsos(vector<QString> &lista2Generar, vector<trioDatos> &listaOriginal, QString &fraseCaso0, int MaxPermitido)
{
    resetTrio(listaOriginal);
    int CantidadObjetos = random.bounded(MAX_OBJETOS);

    if (CantidadObjetos == 0)
        CantidadObjetos = 1;

    lista2Generar.resize(CantidadObjetos);
    int maxObjetos = listaOriginal.size();
    int sorteo, i = 0;
    bool YaHayNoPermitidos = false;
    while (CantidadObjetos){
        do{
            sorteo = random.bounded(maxObjetos);
            lista2Generar[i] = listaOriginal[sorteo].dato;
        }while (listaOriginal[sorteo].Insertado);
        listaOriginal[sorteo].Insertado = true;

        if (YaHayNoPermitidos || checkSiHayObjetosNoPermitidos(lista2Generar, listaOriginal)){
            i++; CantidadObjetos--;
            YaHayNoPermitidos = true;
        }
    }
}

bool Generador_NuevaEstancia::checkSiHayObjetosNoPermitidos(vector<QString> &lista2Generar, vector<trioDatos> &listaOriginal)
{
    for (const auto& objeto1: lista2Generar)
        for (const auto& objeto2: listaOriginal)
            if (objeto1 == objeto2.dato && !objeto2.Permitido)
                return true;

    return false;
}

