#include "reglasnivel2.h"

ReglasNivel2::ReglasNivel2(): Reglas()
{
    for (int i = 0; i < this->maxPaises; i++)
        paisesPar.push_back({paises[i], false});
}

void ReglasNivel2::generar_PaisesPermitidos(int Cantidad)
{
    resetearParDatos(paisesPar);

    if (Cantidad < 1 || Cantidad > maxPaises-1)
        Cantidad = rand.bounded(4) + 1;

    paisesValidos = generarPermitido(Cantidad, paisesPar);
    paisesInvalidos = generarNoPermitido(paisesPar);
}

void ReglasNivel2::generar_PaisesPermitidos(std::vector<QString>& Lista_PaisesPermitidos)
{
    resetearParDatos(paisesPar);

    if (!checkCondiciones(1, paisesPar, Lista_PaisesPermitidos)){
        generar_PaisesPermitidos(rand.bounded(maxPaises));
        return;
    }

    paisesValidos = generarPermitido(Lista_PaisesPermitidos);
    paisesInvalidos = generarNoPermitido(paisesPar);
}

std::vector<QString> ReglasNivel2::getPaisesValidos() const
{
    return generarVector(paisesValidos);
}

std::vector<QString> ReglasNivel2::getPaisesInvalidos() const
{
    return generarVector(paisesInvalidos);
}

QString *ReglasNivel2::getPaisesValidos(int &Max) const
{
    Max = paisesValidos.size();
    QString* paises_Validos = new QString[Max];

    int i = 0;
    for (const auto& element: paisesValidos)
        paises_Validos[i++] = element;

    return paises_Validos;
}

QString *ReglasNivel2::getPaisesInvalidos(int &Max) const
{
    Max = paisesInvalidos.size();
    QString* paises_Invalidos = new QString[Max];
    int i = 0;
    for (const auto& element: paisesValidos)
        paises_Invalidos[i++] = element;

    return paises_Invalidos;
}
