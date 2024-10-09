#ifndef GENERARESTANCIA_H
#define GENERARESTANCIA_H

#include <QString>
#include "../Documentos/estancia.h"
#include "../Reglas/reglasnivel1.h"
#include "locuracaracteres.h"
#include <QRandomGenerator>

class GenerarEstancia {
public:
    // Constructor
    void setSeed(quint32 seed);
    GenerarEstancia();
    void Inicializar(ReglasNivel1 * rules, LocuraCaracteres *  randomizador, quint32 seed, int Dificultad);

    // Getter
    Estancia* generar(bool valido); // Estancia a generar
private:
    int Probabilidades;
    QRandomGenerator NumRandom;
    LocuraCaracteres * locura;

    int dificultad;
    bool ValidezCampos[2];

    vector<QString> tipoVisitas;

    vector<QString> tipoVisitasValidas;
    vector<QString> tipoVisitasInvalidas;
    int maxVisitasValidas;
    int duracMaximaEstancia;

    int IndicesTiposVisitasInvalidas[5];
    int maxVisitasInvalidas;

    // Metodos auxiliares
    void GenerarCamposValidos(int Probabilidad, bool Validez);

    QString GenerarVisita(bool validez);
    int GenerarDuracion(bool validez);
};

#endif // GENERARESTANCIA_H
