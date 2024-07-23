#include "generador_pasaporte.h"
#include "../Reglas/reglasnivel1.h"
#include "../AtributosComunes/atributoscomunes.h"
#include "../Documentos/paisderesidencia.h"
#ifndef GENERADORPAISRESIDENCIA_H
#define GENERADORPAISRESIDENCIA_H

class generadorPaisResidencia : public Generar_pasaporte
{
private:
    QRandomGenerator rand;
    bool camposValidos[4];
    PaisDeResidencia * PaisResidenciaGenerado;


    QString GenerarPaisDeResidencia(bool valido);

public:
    generadorPaisResidencia(ReglasNivel1 * rules, AtributosComunes * atributos);
    PaisDeResidencia * crear_PaisResidencia(bool valido, char genero, int dificultad);

};

#endif // GENERADORPAISRESIDENCIA_H
