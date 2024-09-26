#include "reglasnivel2.h"
#include <QTime>

ReglasNivel2::ReglasNivel2(): Reglas(), Random(QTime::currentTime().msec())
{

}

void ReglasNivel2::generar_PaisesPermitidos(int Cantidad)
{
    paisesValidos.clear();
    paisesInvalidos.clear();

    if (Cantidad < 1 || Cantidad > maxPaises-1)
        Cantidad = Random.bounded(4) + 1;

    int CantidadPaisesInvalidos = maxPaises - Cantidad;
    paisesValidos.resize(Cantidad);
    paisesInvalidos.resize(CantidadPaisesInvalidos);

    // Sorteamos los paises validos, usamos el dowhile para checkear si tenemos paises repetidos en la lista de validos.
    // Si tenemos repetidos volvemos a sortear, sino incrementa el indice y disminuye la cantidad de paises validos a generar.
    int i = 0;
    while(Cantidad){
        do{
            paisesValidos[i] = paises[Random.bounded(maxPaises)];
        }while(checkRepetidos(paisesValidos, i+1));
        i++; Cantidad--;
    }

    i = 0;
    for (int j = 0; j < maxPaises; ++j)
        if (!checkValidez(paises[j], paisesValidos)){
            paisesInvalidos[i] = paises[j];
            i++;
        }
}

void ReglasNivel2::generar_PaisesPermitidos(std::vector<QString>& Lista_PaisesPermitidos)
{
    if (!ValidarDatos(Lista_PaisesPermitidos, 1, maxPaises-1, paises, maxPaises)){
        generar_PaisesPermitidos(Random.bounded(maxPaises));
        return;
    }

    paisesInvalidos.clear();
    paisesValidos.clear();
    paisesValidos = Lista_PaisesPermitidos;
    paisesInvalidos.resize(maxPaises - Lista_PaisesPermitidos.size());

    int i = 0;
    for (int j = 0; i < maxPaises; ++j)
        if (!checkValidez(paises[j], paisesValidos)){
            paisesInvalidos[i] = paises[j];
            i++;
        }
}

QString *ReglasNivel2::getPaisesValidos(int &Max)
{
    Max = paisesValidos.size();
    QString* paises_Validos = new QString[Max];
    for (int i = 0; i < Max; i++)
        paises_Validos[i] = paisesValidos[i];

    return paises_Validos;
}

QString *ReglasNivel2::getPaisesInvalidos(int &Max)
{
    Max = paisesInvalidos.size();
    QString* paises_Invalidos = new QString[Max];
    for (int i = 0; i < Max; i++)
        paises_Invalidos[i] = paisesInvalidos[i];

    return paises_Invalidos;
}
