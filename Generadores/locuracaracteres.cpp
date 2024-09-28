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
    qDebug() << "Cadena original:" << Cadena;
    // Checkeo si la cadena es muy chica
    if (Cadena.length() <= 1)
        return CambiarLetra(Cadena[0]);

    // Si la cadena es superior a la cantidad de caracteres, cambiamos el max.
    if (Cadena.length() <= cantCaracteres)
        cantCaracteres = Cadena.length();

    // Iteramos por los caracteres seleccionados cambiandolos
    int * indices = AlgoritmoDeReservoirByTomi(Cadena);
    int indice;
    QChar caracter;
    for (int i = 0; i < cantCaracteres; i++){
        indice = indices[i];
        caracter = Cadena[indice];
        if (caracter.isLetter())
            Cadena[indice] = CambiarLetra(caracter);
        else
            Cadena[indice] = CambiarNumero(caracter);
    }

    qDebug() << "Cadena cambiada:" << Cadena;

    delete[] indices;
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
    case 1: cantCaracteres = 4;
        break;
        /// Modo demonio
    case 3: cantCaracteres = 1;
        break;
        /// Modo normal
    default: cantCaracteres = 3;
            break;
    }
}

/// ······················· Algoritmo locura que me encontre por internet  ······································
int * LocuraCaracteres::AlgoritmoDeReservoirByTomi(QString CadenaLocura)
{
    // Armamos array con los indices donde estaran las letras a cambiar
    int * indices = new int[cantCaracteres];

    // Metemos los primeros elementos del conjunto
    for (int i = 0; i < cantCaracteres; i++)
        indices[i] = i;

    int Sorteo; QChar Caracter;
    for (int i = cantCaracteres; i < CadenaLocura.length(); i++){
        Sorteo = random->bounded(i);
        Caracter = CadenaLocura[i];
        if (Sorteo < cantCaracteres && Caracter.isLetterOrNumber())
            indices[Sorteo] = i;
    }

    return indices;
}
