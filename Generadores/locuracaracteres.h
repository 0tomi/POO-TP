#ifndef LOCURACARACTERES_H
#define LOCURACARACTERES_H
#include <QDebug>
#include <QString>
#include <QChar>
#include <QRandomGenerator>
#include <vector>
using namespace std;

class LocuraCaracteres
{
public:
    void setSeed(quint32 seed);
    LocuraCaracteres(QRandomGenerator * newGenerador);
    QString CambiarCadena(int Dificultad, QString cadena);
    QString CambiarCadena(QString Cadena, int CantCaracteres);
private:
    // pair < posicion - insertado >
    vector<bool> caracteres2cambiar;

    QString Cambiar(QString Cadena);
    QChar CambiarNumero(QChar numeroOriginal);
    QChar CambiarLetra(QChar letraOriginal);

    QRandomGenerator * random;
    QString cadena;
    QString cadenaNew;

    int cantCaracteres;;
    void setDificultad(int Dificultad);
    void AlgoritmoDeReservoirByTomi(QString CadenaLocura);
};

#endif // LOCURACARACTERES_H
