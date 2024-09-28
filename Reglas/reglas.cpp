#include "reglas.h"
#include "../lectorarchivos.h"

Reglas::Reglas(): rand(QTime::currentTime().msec()) {
    LectorArchivos lector(":/Resources/ArchivosTexto/paises.txt");
    this->paises = lector.getArray();
    this->maxPaises = lector.getTopeArray();
}

Reglas::~Reglas()
{
    //delete paises;
}

void Reglas::setSeed(quint32 seed)
{
    rand.seed(seed);
}

QString *Reglas::getPaises(int &max) const
{
    max = this->maxPaises;
    return paises;
}

QString *Reglas::getTipoVisitas(int &max)
{
    max = MaxTipoVisitas;
    return copiarVector(this->tipoVisitas, MaxTipoVisitas);
}

QString *Reglas::getEstadosCiviles(int &max)
{
    max = MaxEstadosCiviles;
    return copiarVector(estadosCiviles, MaxEstadosCiviles);
}

QString *Reglas::copiarVector(QString * viejoVec, int max)
{
    QString * nuevoVec = new QString[max];
    for (int i = 0; i < max; i++)
        nuevoVec[i] = viejoVec[i];
    return nuevoVec;
}

bool Reglas::ValidarDatos(vector<QString> &Lista, int CantidadMinima, int CantidadMax, QString *Lista2, int maxLista2)
{
    if (Lista.size() < CantidadMinima || Lista.size() > CantidadMax)
        return false;

    if (!ValidarNombres(Lista, Lista2, maxLista2))
        return false;

    return true;
}

bool Reglas::checkRepetidos(std::vector<QString> &Lista, int CantidadInsertada)
{
    for (int i = 0; i < CantidadInsertada-1; ++i)
        for (int j = i+1; j < CantidadInsertada; ++j)
            if (Lista[i] == Lista[j]){
                qDebug() << i << Lista[i] << j << Lista[j];
                return true;
            }

    return false;
}

bool Reglas::checkValidez(QString &dato, std::vector<QString> &Lista) const
{
    for (int i = 0; i < Lista.size(); ++i)
        if (Lista[i] == dato)
            return true;
    return false;
}

bool Reglas::checkValidez(QString &dato, std::list<QString> &Lista) const
{
    for (const auto& elemento: Lista)
        if (elemento == dato)
            return true;

    return false;
}

bool Reglas::ValidarNombres(vector<QString>& Lista, QString * Lista2, int max)
{
    bool NombreValido;
    QString Nombre1, Nombre2;
    for (int i = 0; i < Lista.size(); ++i){
        NombreValido = false;
        Nombre1 = Lista[i].toLower();

        for (int j = 0; j < max; ++j){
            Nombre2 = Lista2[j].toLower();
            if (Nombre1 == Nombre2){
                NombreValido = true;
                // Si es valido porque lo encontro, lo dejamos como esta escrito en la lista original.
                Lista[i] = Lista[j];
            }
        }

        if (!NombreValido)
            return false;
    }

    return true;
}

