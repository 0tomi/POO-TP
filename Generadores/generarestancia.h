#ifndef GENERARESTANCIA_H
#define GENERARESTANCIA_H

#include <QString>
#include "../Documentos/estancia.h"
#include "locuracaracteres.h"
#include <QRandomGenerator>

class GenerarEstancia {
public:
    GenerarEstancia(QString* TiposVisitas, int TopeVisits, QString* TiposVisitsVal, int TopeVisitsVal, int DuracMax);
    ~GenerarEstancia();
    void resetReglas(QString* TiposVisitas, int TopeVisits, QString* TiposVisitsVal, int TopeVisitsVal, int DuracMax);

    // Getter
    Estancia* getEstancia(bool valido, int Dificultad); // Estancia a generar
private:
    QRandomGenerator NumRandom;
    LocuraCaracteres * locura;
    int dificultad;
    bool ValidezCampos[2];

    QString* tipoVisitas;
    int maxTipoVisitas;

    QString* tipoVisitasValidas;
    int maxVisitasValidas;
    int duracMaximaEstancia;

    int IndicesTiposVisitasInvalidas[5];
    int maxVisitasInvalidas;
    void ObtenerVisitasInvalidas();

    // Metodos auxiliares
    void GenerarCamposValidos(int Probabilidad, bool Validez);

    QString GenerarVisita(bool validez);
    int GenerarDuracion(bool validez);
};

#endif // GENERARESTANCIA_H
