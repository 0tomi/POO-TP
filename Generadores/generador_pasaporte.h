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
    vector<QString>  nombre_mujeres;
    vector<QString>  nombre_hombres;
    vector<QString>  nombre_x;
    vector<QString>  nacionalidades;
    vector<QString>  PaisesValidos;
    vector<QString>  PaisesInvalidos;
    vector<QString>  apellidos;
    vector<QString>  estados_civiles_invalidos;
    vector<QString>  estados_civiles_validos;
    ReglasNivel1 * rules;
    QRandomGenerator rand;


    Pasaporte * Pasaporte_generado;

    int Probabilidades;
    int obt_dias(int mes, int año);
    void generar_camposValidos(bool valido, int dificultad);

    virtual QString generar_nombre(char genero);
    QString generar_estado_civil(char genero, bool valido);
    virtual QString generar_nacionalidad(bool valido);
    virtual QString generar_fecha(bool valido);
public:
    void setSeed(quint32 seed);
    Generar_pasaporte(); // el constructor va a ser para leer los archivos
    void Inicializar(ReglasNivel1 * rules, quint32 seed, int dificultad);
    Pasaporte * generar(bool Validez, NPCcomun * InfoNPC);
};
#endif // GENERADOR_PASAPORTE_H
