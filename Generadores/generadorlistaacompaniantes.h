#ifndef GENERADORLISTAACOMPANIANTES_H
#define GENERADORLISTAACOMPANIANTES_H

#include "../Documentos/listaacompaniantes.h"
#include "../lectorarchivos.h"

#include <QRandomGenerator>
#include <QString>

class GeneradorListaAcompaniantes {
private:
    QRandomGenerator * numRandom;

    // arrays con nombres:
    QString * nombresMujeres;
    QString * nombresHombres;
    QString * nombresX;
    QString * apellidos;

    // topes de los arrays:
    int maxHombres;
    int maxMujeres;
    int maxX;
    int maxApellidos;

    QString generarNombre(char genero);
    char getGeneroRandom();
    int generarRandomExcluido(int excluded);
public:
    GeneradorListaAcompaniantes();
    void Inicializar(QRandomGenerator * generador);

    ~GeneradorListaAcompaniantes();

    ListaAcompaniantes * getListaAcompaniantes(bool validez);
};

#endif // GENERADORLISTAACOMPANIANTES_H
