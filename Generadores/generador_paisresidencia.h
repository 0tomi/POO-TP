#include "generador_pasaporte.h"
#include "../Reglas/ReglasNivel1.h"
#include "../Documentos/paisresidencia.h"
#include "locuracaracteres.h"
#ifndef GENERADOR_PAISRESIDENCIA_H
#define GENERADOR_PAISRESIDENCIA_H

class generador_paisresidencia : public Generar_pasaporte
{
private:
    int dificultad;
    ReglasNivel1 * rules;
    Pasaporte * Pasaporte2Copy;

    bool camposValidos[3]; // 1 nombre, 2 fecha, 3 pais de residencia
    bool camposLocura[3]; // 1 nombre , 2 fecha, 3 pais de residencia
    //campos locura es para ver si se usa locura caracteres o no, si es false no se usa locura si es true si

    QRandomGenerator rand;
    PaisResidencia * PaisResidenciaCreado;
    LocuraCaracteres * locura;

    QString generar_nombre(char genero) override;
    QString generar_paisresidencia(bool valido);
    QString generar_fecha(bool valido) override;
    void CamposLocura(int Probabilidades);
public:
    generador_paisresidencia();
    ~generador_paisresidencia();
    void Inicializar(ReglasNivel1 * rules);
    PaisResidencia * CrearPaisResidencia(Pasaporte * Pasaporte2copy, bool valido, int dificultad);
    void resetRules(ReglasNivel1 * rules);
};

#endif // GENERADOR_PAISRESIDENCIA_H
