#include "../Reglas/reglasnivel4.h"
#include "../Documentos/radiografia.h"
#ifndef GENERADOR_RADIOGRAFIA_H
#define GENERADOR_RADIOGRAFIA_H

class generador_Radiografia
{
private:
    ReglasNivel4 * rules;
    QRandomGenerator random;
    int dificultad;
    int cantElementos;
    const int MAX_PARTESCUERPO = 10;
    vector<ParDatos>Elementos;
    radiografia * radiografia2Generate;
public:
    generador_Radiografia();
    void inicializar(ReglasNivel4 * rules, quint32 semilla, int dificultad);
    radiografia generar_radiografia(bool validez);
    void generar_validos(int cant2Generate);
    void generar_validos();
};

#endif // GENERADOR_RADIOGRAFIA_H
