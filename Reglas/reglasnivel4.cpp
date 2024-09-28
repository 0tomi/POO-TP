#include "reglasnivel4.h"
#include <QTime>

ReglasNivel4::ReglasNivel4(): Reglas(), Random(QTime::currentTime().msec())
{

}

std::vector<QString> ReglasNivel4::getPaisesPermitidos() const
{
    return PaisesPermitidos;
}

std::vector<QString> ReglasNivel4::getPaisesNoPermitidos() const
{
    return PaisesNoPermitidos;
}

std::vector<QString> ReglasNivel4::getOcupacionPermitidos() const
{
    return OcupacionPermitidos;
}

std::vector<QString> ReglasNivel4::getOcupacionNoPermitidos() const
{
    return OcupacionNoPermitidos;
}

std::vector<QString> ReglasNivel4::getBienesTransportadosPermitidos() const
{
    return BienesTransportadosPermitidos;
}

std::vector<QString> ReglasNivel4::getBienesTransportadosNoPermitidos() const
{
    return BienesTransportadosNoPermitidos;
}
