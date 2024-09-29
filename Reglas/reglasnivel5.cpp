#include "reglasnivel5.h"

ReglasNivel5::ReglasNivel5()
{
    rand.seed(QTime::currentTime().msec());
}

std::vector<QString> ReglasNivel5::getObjetos() const
{
    return Objetos;
}
