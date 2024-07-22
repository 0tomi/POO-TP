#ifndef LOCURACARACTERES_H
#define LOCURACARACTERES_H
#include <QDebug>
#include <QString>
#include <QChar>
#include <QRandomGenerator>


class LocuraCaracteres
{
public:
    LocuraCaracteres(QRandomGenerator * newGenerador);
    QString CambiarCadena(int Dificultad, QString cadena);
    QString CambiarCadena(QString Cadena, int CantCaracteres);
private:
    QString Cambiar(QString Cadena);
    QChar CambiarNumero(QChar numeroOriginal);
    QChar CambiarLetra(QChar letraOriginal);

    QRandomGenerator * random;
    QString cadena;
    QString cadenaNew;

    int cantCaracteres;;
    void setDificultad(int Dificultad);
    int * AlgoritmoDeReservoirByTomi(QString CadenaLocura);
};

#endif // LOCURACARACTERES_H
