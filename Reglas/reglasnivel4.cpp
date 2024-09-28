#include "reglasnivel4.h"
#include "../lectorarchivos.h"
#include <QTime>

ReglasNivel4::ReglasNivel4(): random(QTime::currentTime().msec())
{
    LectorArchivos lector(":/Niveles/Nivel4/Bienes.txt");
    this->Bienes = lector.getList();
    this->Ocupaciones = lector.getList(":/Niveles/Nivel4/Ocupaciones.txt");
    this->PaisesPaso = lector.getList(":/Niveles/Nivel4/PaisesPaso.txt");
}

void ReglasNivel4::setSeed(int Seed)
{
    random.seed(Seed);
}

void ReglasNivel4::generar_PaisesPaso(int CantPermitida)
{
    if (CantPermitida < 0 || CantPermitida > PaisesPaso.size())
        CantPermitida = random.bounded(PaisesPaso.size());


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
    return generarVector(BienesTransportadosPermitidos);
}

std::vector<QString> ReglasNivel4::getBienesTransportadosNoPermitidos() const
{
    return generarVector(BienesTransportadosNoPermitidos);
}

std::vector<QString> ReglasNivel4::generarVector(const std::list<QString> &lista) const
{
    std::vector<QString> newVector;
    for (const QString& element: lista)
        newVector.push_back(element);
    return newVector;
}
