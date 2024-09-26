#include "generador_pasaporte.h"
#include "../Reglas/ReglasNivel2.h"
#include "../Documentos/paisresidencia.h"
#include "locuracaracteres.h"

#ifndef GENERADOR_PAISRESIDENCIA_H
#define GENERADOR_PAISRESIDENCIA_H

class generador_paisresidencia : public Generar_pasaporte
{
private:
    int dificultad;
    int Probabilidades;
    ReglasNivel2 * ruleslvl2;
    ReglasNivel1 * rules;
    Pasaporte * Pasaporte2Copy;

    bool camposValidos[3]; // 1 nombre, 2 fecha, 3 pais de residencia
    bool camposLocura[3]; // 1 nombre , 2 fecha, 3 pais de residencia
    //campos locura es para ver si se usa locura caracteres o no, si es false no se usa locura si es true si

    PaisResidencia * PaisResidenciaCreado;
    LocuraCaracteres * locura;

    QString * paisesValidos; QString * paisesInvalidos;
    int maxValidos, maxInvalidos;

    QString generar_nombre(char genero) override;
    QString generar_paisresidencia(bool valido);
    QString generar_fecha(bool valido) override;
    void CamposLocura(int Probabilidades);

public:
    generador_paisresidencia();
    QString generarPaisValido();
    QString generarPaisInvalido();
    ~generador_paisresidencia();
    void Inicializar(ReglasNivel1*, ReglasNivel2*);
    PaisResidencia * CrearPaisResidencia(Pasaporte * Pasaporte2copy, bool valido, int dificultad);
};

#endif // GENERADOR_PAISRESIDENCIA_H
