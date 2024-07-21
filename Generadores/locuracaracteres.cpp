#include "locuracaracteres.h"
/// ########################## Constructor ###############################
LocuraCaracteres::LocuraCaracteres(QRandomGenerator *newGenerador)
{
    generador = newGenerador;

}
/// ······················· Setter para cambiar cadena  ······································
QString LocuraCaracteres::CambiarCadena(QString Cadena, int Dificultad)
{
    setDificultad(Dificultad);
    return Cambiar(Cadena);
}

QString LocuraCaracteres::CambiarCadena(QString Cadena, int CantMaxCaracters, int CantMinCaracteres)
{
    cantMaxCaracteres = CantMaxCaracters;
    cantMinCaracteres = CantMinCaracteres;
    return Cambiar(Cadena);
}

QString LocuraCaracteres::Cambiar(QString Cadena)
{
    if (Cadena.length() <= 1)
        return CambiarLetra(Cadena[0]);

    if (Cadena.length() == cantMaxCaracteres)
        cantMaxCaracteres = Cadena.length();

    if (cantMaxCaracteres == cantMinCaracteres)
        cantMinCaracteres = 1;



}
/// ······················· Cambiar la cadena  ······································


/// ······················· Cambiar caracteres especificos  ······································


/// ······················· Setear dificultad ······································
void LocuraCaracteres::setDificultad(int Dificultad)
{
    switch (Dificultad){
        /// Modo facil
    case 1: cantMaxCaracteres = 6;
            cantMinCaracteres = 3;
        break;
        /// Modo demonio
    case 3: cantMaxCaracteres = 2;
        cantMinCaracteres = 1;
        break;
        /// Modo normal
    default: cantMaxCaracteres = 4;
        cantMinCaracteres = 1;
            break;
    }
}

