#ifndef GENERADORLISTAACOMPANIANTES_H
#define GENERADORLISTAACOMPANIANTES_H

#include "../Documentos/listaacompaniantes.h"
#include "../lectorarchivos.h"
#include "../Reglas/reglasnivel3.h"

#include <QRandomGenerator>
#include <QString>

class GeneradorListaAcompaniantes {
private:
    QRandomGenerator * numRandom;
    bool Campos[2]; // 0: Lista, 1: Dialogo

    // arrays con nombres:
    QString * nombresMujeres;
    QString * nombresHombres;
    QString * nombresX;
    QString * apellidos;

    // topes de los arrays:
    int maxAcompaniantesValidos;
    int maxHombres;
    int maxMujeres;
    int maxX;
    int maxApellidos;

    QString *generarAcompaniantes(int max);
    QString generarNombre(char genero);
    char getGeneroRandom();
    int generarRandomExcluido(int excluded);
    void generarCamposValidos(bool validez);

    ListaAcompaniantes * generarLista(int valormin, int valormax, bool Validez, bool Dialogos);
    ListaAcompaniantes* getListaFalsa();
    void SetDatosFalsos(bool Validez, ListaAcompaniantes* doc);
public:
    GeneradorListaAcompaniantes();
    void Inicializar(QRandomGenerator * generador, ReglasNivel3 * reglas);

    ~GeneradorListaAcompaniantes();

    ListaAcompaniantes * generar(bool validez);
};

#endif // GENERADORLISTAACOMPANIANTES_H
