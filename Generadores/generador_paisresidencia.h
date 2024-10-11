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

    vector<QString> paisesValidos;
    vector<QString> paisesInvalidos;

    QString generarPaisValido();
    QString generarPaisInvalido();
    QString generar_nombre(char genero) override;
    QString generar_paisresidencia(bool valido);
    QString generar_fecha(bool valido) override;
    void CamposLocura(int Probabilidades);
    void SetDatosFalsos(bool validez, PaisResidencia* doc);

public:
    void setSeed(quint32 seed);
    bool checkearSiEsValido(QString pais);
    generador_paisresidencia();
    ~generador_paisresidencia();
    void Inicializar(ReglasNivel1*, ReglasNivel2*, quint32 seed, int dificultad);
    PaisResidencia * generar(Pasaporte * Pasaporte2copy, bool valido);
};

#endif // GENERADOR_PAISRESIDENCIA_H
