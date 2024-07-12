#ifndef GENERADOR_PASAPORTE_H
#define GENERADOR_PASAPORTE_H
#include "../Documentos/pasaporte.h"
#include <stdlib.h>
#include "../AtributosComunes/atributoscomunes.h"
#include "../Reglas/ReglasNivel1.h"
#include "../lectorarchivos.h"


class generar_pasaporte
{
private:
    //NPC * data_npc; // para poder incluit foto dni y genero
    AtributosComunes * atributos;
    QString * nombre_mujeres;
    QString * nombre_hombres;
    QString * nombre_x;
    QString * nacionalidades;
    ReglasNivel1 * rules;
    QWidget cara;
    Pasaporte * Pasaporte_generado;
    int max_hombres; // tamanio del array de nombres de hombres
    int max_mujeres; // tamanio del array de nombres de mujeres
    int max_x;  // tamanio del array de nombres de x
    int max_nacionalidades; // cantidad total de nacionalidades

    QString generar_nombre(char genero);
    QString generar_estado_civil(char genero, bool valido);
    QString generar_nacionalidad(bool valido);
    QString generar_fecha(bool valido);
public:
    generar_pasaporte(ReglasNivel1 * rules, AtributosComunes * atributos); // el constructor va a ser para leer los archivos y para asignar reglas y atributos
    Pasaporte * crear_pasaporte(bool valido, char genero);
};
#endif // GENERADOR_PASAPORTE_H
