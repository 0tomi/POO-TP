#include "../Reglas/reglasnivel4.h"
#include "../Documentos/radiografia.h"
#include "../lectorarchivos.h"
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
    vector<QString>ObjetosValidos;
    vector<QString>ObjetosInvalidos;
    radiografia * radiografia2Generate;
    void SetDatosFalsos(bool Validez, radiografia* doc);
public:
    generador_Radiografia();
    void inicializar(ReglasNivel4 * rules, quint32 semilla, int dificultad);
    radiografia* generar_radiografia(bool validez);
    void generar_validos(int cant2Generate);
    void generar_validos();
    void generar_invalidos(int cant2Generate);
};

#endif // GENERADOR_RADIOGRAFIA_H
