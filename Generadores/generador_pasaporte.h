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
    bool campos_validos[3];    // 0 para la fecha, 1 para la nacionalidad, 2 para el estado civil;
    const int cantcampos = 3;
protected:
    AtributosComunes * atributos;
    QString * nombre_mujeres;
    QString * nombre_hombres;
    QString * nombre_x;
    QString * nacionalidades;
    QString * apellidos;
    ReglasNivel1 * rules;



    Pasaporte * Pasaporte_generado;
    int max_hombres; // tamanio del array de nombres de hombres
    int max_mujeres; // tamanio del array de nombres de mujeres
    int max_x;  // tamanio del array de nombres de x
    int max_nacionalidades; // cantidad total de nacionalidades
    int max_apellidos; // cantidad total de apellidos

    void generar_camposValidos(bool valido, int dificultad, const int cantcampos);

    QString generar_nombre(char genero);
    QString generar_estado_civil(char genero, bool valido);
    QString generar_nacionalidad(bool valido);
    QString generar_fecha(bool valido);
public:
    Generar_pasaporte(ReglasNivel1 * rules, AtributosComunes * atributos); // el constructor va a ser para leer los archivos y para asignar reglas y atributos
    Pasaporte * crear_pasaporte(bool valido, char genero, int dificultad);
    void restartReglas(ReglasNivel1 * rules);
};
#endif // GENERADOR_PASAPORTE_H
