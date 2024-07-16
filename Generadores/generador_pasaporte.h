#ifndef GENERADOR_PASAPORTE_H
#define GENERADOR_PASAPORTE_H
#include "../Documentos/pasaporte.h"
#include "../AtributosComunes/atributoscomunes.h"
#include "../Reglas/ReglasNivel1.h"
#include "../lectorarchivos.h"


class Generar_pasaporte
{
private:
    QRandomGenerator rand;
    AtributosComunes * atributos;
    QString * nombre_mujeres;
    QString * nombre_hombres;
    QString * nombre_x;
    QString * nacionalidades;
    ReglasNivel1 * rules;
    bool campos_validos[3]; // 0 para la fecha, 1 para la nacionalidad, 2 para el estado civil
    Pasaporte * Pasaporte_generado;
    int max_hombres; // tamanio del array de nombres de hombres
    int max_mujeres; // tamanio del array de nombres de mujeres
    int max_x;  // tamanio del array de nombres de x
    int max_nacionalidades; // cantidad total de nacionalidades

    QString generar_nombre(char genero);
    QString generar_estado_civil(char genero, bool valido);
    QString generar_nacionalidad(bool valido);
    QString generar_fecha(bool valido);
    void generar_camposValidos(bool valido, int dificultad);
public:
    Generar_pasaporte(ReglasNivel1 * rules, AtributosComunes * atributos); // el constructor va a ser para leer los archivos y para asignar reglas y atributos
    Pasaporte * crear_pasaporte(bool valido, char genero, int dificultad);
};
#endif // GENERADOR_PASAPORTE_H
