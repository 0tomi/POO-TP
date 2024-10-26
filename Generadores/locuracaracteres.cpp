#include "locuracaracteres.h"
/// ########################## Constructor ###############################
void LocuraCaracteres::setSeed(quint32 seed)
{
    this->random->seed(seed);
}

LocuraCaracteres::LocuraCaracteres(QRandomGenerator *newGenerador)
{
    random = newGenerador;
}

/// ······················· Setter para cambiar cadena  ······································
QString LocuraCaracteres::CambiarCadena(int Dificultad, QString Cadena)
{
    setDificultad(Dificultad);
    return Cambiar(Cadena);
}

QString LocuraCaracteres::CambiarCadena(QString Cadena, int CantCaracteres)
{
    cantCaracteres = CantCaracteres;
    return Cambiar(Cadena);
}
/// ······················· Cambiar la cadena  ······································
QString LocuraCaracteres::Cambiar(QString Cadena)
{
    // Checkeo si la cadena es muy chica
    if (Cadena.length() <= 1)
        return CambiarLetra(Cadena[0]);

    // Si la cadena es superior a la cantidad de caracteres, cambiamos el max.
    if (Cadena.length() <= cantCaracteres)
        cantCaracteres = Cadena.length();

    // Iteramos por los caracteres seleccionados cambiandolos
    AlgoritmoDeReservoirByTomi(Cadena);
    for (int i = 0; i < cantCaracteres; i++){
        if (!caracteres2cambiar[i]){
            if (Cadena[i].isLetter())
                Cadena[i] = CambiarLetra(Cadena[i]);
            else
                Cadena[i] = CambiarNumero(Cadena[i]);
        }
    }

    return Cadena;
}
/// ······················· Cambiar caracteres especificos  ······································
QChar LocuraCaracteres::CambiarNumero(QChar numeroOriginal)
{
    // 10 = cantidad de numeros de 0 a 9
    int caracterRandom = random->bounded(10);
    QChar nuevoCaracter('0' + caracterRandom);

    return nuevoCaracter;
}

QChar LocuraCaracteres::CambiarLetra(QChar letraOriginal)
{
    QChar nuevoCaracter;
    QChar auxiliar = letraOriginal;
    auxiliar.toUpper();

    do{  // Repetimos hasta obtener un caracter diferente
        // 26 = cantidad de letras de la A a la Z
        int caracterRandom = random->bounded(26);
        nuevoCaracter = QChar('A' + caracterRandom);
    }while(nuevoCaracter == auxiliar);

    // Si la letra original era minuscula, devolvemos una minuscula, sino una mayus.
    return (letraOriginal.isLower()) ? nuevoCaracter.toLower() : nuevoCaracter;
}

/// ······················· Setear dificultad ······································
void LocuraCaracteres::setDificultad(int Dificultad)
{
    switch (Dificultad){
        /// Modo facil
    case 1: cantCaracteres = 3;
        break;
        /// Modo demonio
    case 3: cantCaracteres = 1;
        break;
        /// Modo normal
    default: cantCaracteres = 2;
            break;
    }
}

/// ······················· Algoritmo locura que me encontre por internet  ······································
void LocuraCaracteres::AlgoritmoDeReservoirByTomi(QString CadenaLocura)
{
    caracteres2cambiar.resize(CadenaLocura.size());
    for (auto el: caracteres2cambiar)
        el = true;

    int tamanio = CadenaLocura.size();
    // odiamos a qrandom y a rand
    for (int i = 0; i < 100; i++)
        random->bounded(tamanio);

    int temp = cantCaracteres;
    int sorteo;
    while (temp) {
        sorteo = random->bounded(tamanio);
        if (caracteres2cambiar[sorteo]){
            if (CadenaLocura[sorteo].isLetterOrNumber()){
                caracteres2cambiar[sorteo] = false;
                temp--;
            }
        }
    }
}
