#include "reglasnivel5.h"

ReglasNivel5::ReglasNivel5()
{
    rand.seed(QTime::currentTime().msec());
    LectorArchivos lector(":/Niveles/Nivel5/Objetos.txt");
    auto objetos = lector.getVector();
    crearParDatos(objetos, this->Objetos);
}

void ReglasNivel5::generar_ObjetosPermitidos(int Cantidad)
{
    resetearParDatos(this->Objetos);
    Cantidad = checkCondiciones(Cantidad, 1, this->Objetos);
    this->ObjetosPermitidos = generarPermitido(Cantidad, this->Objetos);
    this->ObjetosNoPermitidos = generarNoPermitido(this->Objetos);
}

void ReglasNivel5::generar_ObjetosPermitidos(std::vector<QString> ListaPermitidos)
{
    resetearParDatos(this->Objetos);
    if (!checkCondiciones(0, this->Objetos, ListaPermitidos)){
        generar_ObjetosPermitidos(rand.bounded(this->Objetos.size()));
        return;
    }
    ObjetosPermitidos = generarPermitido(ListaPermitidos);
    ObjetosNoPermitidos = generarNoPermitido(this->Objetos);
}

std::vector<QString> ReglasNivel5::getObjetos() const
{
    return deshacerPar(this->Objetos);
}

std::vector<QString> ReglasNivel5::getObjetosPermitidos() const
{
    return generarVector(this->ObjetosPermitidos);
}

std::vector<QString> ReglasNivel5::getObjetosNoPermitidos() const
{
    return generarVector(this->ObjetosNoPermitidos);
}
