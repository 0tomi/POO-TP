#include "reglasnivel4.h"
#include "../lectorarchivos.h"

ReglasNivel4::ReglasNivel4()
{
    rand.seed(QTime::currentTime().msec());
    LectorArchivos lector(":/Niveles/Nivel4/Bienes.txt");
    auto bienes = lector.getVector();
    auto ocupaciones = lector.getVector(":/Niveles/Nivel4/Ocupaciones.txt");
    auto paisesPaso = lector.getVector(":/Niveles/Nivel4/PaisesPaso.txt");

    crearParDatos(bienes, this->Bienes);
    crearParDatos(ocupaciones, this->Ocupaciones);
    crearParDatos(paisesPaso, this->PaisesPaso);
}

void ReglasNivel4::generar_Todo(int CantidadPaises, int CantidadOcupaciones, int CantidadBienes)
{
    generar_PaisesPaso(CantidadPaises);
    generar_Ocupacion(CantidadOcupaciones);
    generar_BienesTransportados(CantidadBienes);
}

void ReglasNivel4::generar_PaisesPaso(int CantPermitida)
{
    resetearParDatos(PaisesPaso);
    const int MINIMA_CANTIDAD_PERMITIDA = 0;
    CantPermitida = checkCondiciones(CantPermitida, MINIMA_CANTIDAD_PERMITIDA, PaisesPaso);
    PaisesPermitidos = generarPermitido(CantPermitida, PaisesPaso);
    PaisesNoPermitidos = generarNoPermitido(PaisesPaso);
}

void ReglasNivel4::generar_PaisesPaso(std::vector<QString> ListaPaisesPermitidos)
{
    resetearParDatos(this->PaisesPaso);
    if (!checkCondiciones(0, this->PaisesPaso, ListaPaisesPermitidos)){
        generar_PaisesPaso(rand.bounded(this->PaisesPaso.size()));
        return;
    }

    this->PaisesPermitidos = generarPermitido(ListaPaisesPermitidos);
    this->PaisesNoPermitidos = generarNoPermitido(this->PaisesPaso);
}

void ReglasNivel4::generar_Ocupacion(int CantPermitida)
{
    resetearParDatos(this->Ocupaciones);
    const int MINIMA_CANTIDAD_PERMITIDA = 0;
    CantPermitida = checkCondiciones(CantPermitida, MINIMA_CANTIDAD_PERMITIDA, this->Ocupaciones);
    this->OcupacionPermitidos = generarPermitido(CantPermitida, this->Ocupaciones);
    this->OcupacionNoPermitidos = generarNoPermitido(this->Ocupaciones);
}

void ReglasNivel4::generar_Ocupacion(std::vector<QString> ListaOcupacionPermitidos)
{
    resetearParDatos(this->Ocupaciones);
    if (!checkCondiciones(0, this->Ocupaciones, ListaOcupacionPermitidos)){
        generar_Ocupacion(rand.bounded(this->Ocupaciones.size()));
        return;
    }

    this->OcupacionPermitidos = generarPermitido(ListaOcupacionPermitidos);
    this->OcupacionNoPermitidos = generarNoPermitido(this->Ocupaciones);
}

void ReglasNivel4::generar_BienesTransportados(int CantPermitida)
{
    resetearParDatos(this->Bienes);
    const int MINIMA_CANTIDAD_PERMITIDA = 0;
    CantPermitida = checkCondiciones(CantPermitida, MINIMA_CANTIDAD_PERMITIDA, this->Bienes);
    this->BienesPermitidos = generarPermitido(CantPermitida, this->Bienes);
    this->BienesNoPermitidos = generarNoPermitido(this->Bienes);
}

void ReglasNivel4::generar_BienesTransportados(std::vector<QString> ListaBienesTransportadosPermitidos)
{
    resetearParDatos(this->Bienes);
    if (!checkCondiciones(0, this->Bienes, ListaBienesTransportadosPermitidos)){
        generar_BienesTransportados(rand.bounded(this->Bienes.size()));
        return;
    }

    this->BienesPermitidos = generarPermitido(ListaBienesTransportadosPermitidos);
    this->BienesPermitidos = generarNoPermitido(this->Bienes);
}

std::vector<QString> ReglasNivel4::getPaises() const
{
    return deshacerPar(PaisesPaso);
}

std::vector<QString> ReglasNivel4::getOcupaciones() const
{
    return deshacerPar(Ocupaciones);
}

std::vector<QString> ReglasNivel4::getBienes() const
{
    return deshacerPar(Bienes);
}

std::vector<QString> ReglasNivel4::getPaisesPermitidos() const
{
    return generarVector(PaisesPermitidos);
}

std::vector<QString> ReglasNivel4::getPaisesNoPermitidos() const
{
    return generarVector(PaisesNoPermitidos);
}

std::vector<QString> ReglasNivel4::getOcupacionPermitidos() const
{
    return generarVector(OcupacionPermitidos);
}

std::vector<QString> ReglasNivel4::getOcupacionNoPermitidos() const
{
    return generarVector(OcupacionNoPermitidos);
}

std::vector<QString> ReglasNivel4::getBienesTransportadosPermitidos() const
{
    return generarVector(this->BienesPermitidos);
}

std::vector<QString> ReglasNivel4::getBienesTransportadosNoPermitidos() const
{
    return generarVector(this->BienesNoPermitidos);
}
