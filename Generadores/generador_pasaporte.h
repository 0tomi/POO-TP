#ifndef GENERADOR_PASAPORTE_H
#define GENERADOR_PASAPORTE_H
#include "../Documentos/pasaporte.h"
#include "../Reglas/ReglasNivel1.h"
#include "../lectorarchivos.h"
#include "../NPC/npccomun.h"


class Generar_pasaporte
{
private:
    bool campos_validos[3];    // 0 para la fecha, 1 para la nacionalidad, 2 para el estado civil;
protected:
    QString * nombre_mujeres;
    QString * nombre_hombres;
    QString * nombre_x;
    QString * nacionalidades;
    QString * apellidos;
    ReglasNivel1 * rules;
    QRandomGenerator rand;


    Pasaporte * Pasaporte_generado;
    int max_hombres; // tamanio del array de nombres de hombres
    int max_mujeres; // tamanio del array de nombres de mujeres
    int max_x;  // tamanio del array de nombres de x
    int max_nacionalidades; // cantidad total de nacionalidades
    int max_apellidos; // cantidad total de apellidos
    int obt_dias(int mes, int año);
    void generar_camposValidos(bool valido, int dificultad);

    virtual QString generar_nombre(char genero);
    QString generar_estado_civil(char genero, bool valido);
    virtual QString generar_nacionalidad(bool valido);
    virtual QString generar_fecha(bool valido);
public:
    void setSeed(quint32 seed);
    Generar_pasaporte(); // el constructor va a ser para leer los archivos y para asignar reglas y atributos
    void Inicializar(ReglasNivel1 * rules, quint32 seed);
    Pasaporte * crear_pasaporte(bool Validez, NPCcomun * InfoNPC, int dificultad);
};
#endif // GENERADOR_PASAPORTE_H
