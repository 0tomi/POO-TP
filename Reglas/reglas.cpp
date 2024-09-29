#include "reglas.h"

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


void Reglas::crearParDatos(std::vector<QString> &vectorOriginal, std::vector<parDatos> &vectorPar)
{
    for (const auto& elemento: vectorOriginal)
        vectorPar.push_back({elemento, false});
}

void Reglas::resetearParDatos(std::vector<parDatos> &vectorPar)
{
    for (auto& elemento: vectorPar)
        elemento.Insertado = false;
}

int Reglas::checkCondiciones(int cantidad, int min, std::vector<parDatos>& vec)
{
    if (cantidad < 0 || cantidad > vec.size())
        cantidad = rand.bounded(vec.size());

    return cantidad;
}

bool Reglas::checkCondiciones(int min, std::vector<parDatos> &vec, std::vector<QString> &lista)
{
    auto tamanioLista = lista.size();
    if (tamanioLista < min || tamanioLista > vec.size())
        return false;
    if (!checkTipado(vec, lista))
        return false;

    return true;
}

bool Reglas::checkTipado(std::vector<parDatos> &vec, std::vector<QString> &lista)
{
    bool ListaCorrecta = true;
    for (auto& elemento: lista)
        if (!checkTipado(elemento, vec))
            ListaCorrecta = false;

    return ListaCorrecta;
}

bool Reglas::checkTipado(QString &elemento, std::vector<parDatos> &vec)
{
    QString palabra1 = elemento.toLower(); QString palabra2;
    for (auto& element: vec){
        palabra2 = element.dato.toLower();
        if (palabra1 == palabra2){
            element.Insertado = true;
            return true;
        }
    }

    return false;
}

std::list<QString> Reglas::generarPermitido(int cantidad, std::vector<parDatos> &vec)
{
    std::vector<QString> VectorPermitido;
    VectorPermitido.resize(cantidad);

    int CantidadInsertada = 0; int tamanio = vec.size(); int indice_random;
    while (cantidad){
        do{
            indice_random = rand.bounded(tamanio);
            VectorPermitido[CantidadInsertada] = vec[indice_random].dato;
        }while(vec[indice_random].Insertado);

        vec[indice_random].Insertado = true;
        cantidad--; CantidadInsertada++;
    }

    std::list<QString> Lista2Return;
    for (const auto& elemento: VectorPermitido)
        Lista2Return.push_back(elemento);

    return Lista2Return;
}

std::list<QString> Reglas::generarPermitido(std::vector<QString> &Permitidos)
{
    std::list<QString> Lista2Return;
    for (const auto& elemento: Permitidos)
        Lista2Return.push_back(elemento);

    return Lista2Return;
}

std::list<QString> Reglas::generarNoPermitido(std::vector<parDatos> &total)
{
    std::list<QString> listaNoPermitidos;
    for (auto& elemento: total)
        if (!elemento.Insertado)
            listaNoPermitidos.push_back(elemento.dato);

    return listaNoPermitidos;
}

std::vector<QString> Reglas::deshacerPar(const std::vector<parDatos> &par) const
{
    std::vector<QString> Vector;
    for (const auto& elemento: par)
        Vector.push_back(elemento.dato);

    return Vector;
}

std::vector<QString> Reglas::generarVector(const std::list<QString> &lista) const
{
    std::vector<QString> newVector;
    for (const QString& element: lista)
        newVector.push_back(element);
    return newVector;
}
