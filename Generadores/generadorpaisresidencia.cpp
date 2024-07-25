/*#include "generadorpaisresidencia.h"


generadorPaisResidencia::generadorPaisResidencia(ReglasNivel1 *rules, AtributosComunes *atributos)
    : Generar_pasaporte(rules, atributos){
}

PaisDeResidencia *generadorPaisResidencia::crear_PaisResidencia(bool valido, char genero, int dificultad){
    int Probabilidades;
    switch (dificultad){
        // Modo facil
    case 1: Probabilidades = 7;
        break;
        // Modo demonio
    case 3: Probabilidades = 3;
        break;
        // Modo normal
    default: Probabilidades = 5;
        break;
    }
    generar_camposValidos(valido,Probabilidades, this->cantcampos);
    QString Nombre = generar_nombre(genero);
    QString Fecha = generar_fecha(this->camposValidos[0]);
    QString Nacionalidad = generar_nacionalidad(this->camposValidos[1]);
    QString PaisDeResidenciaGenerado = GenerarPaisDeResidencia(this->camposValidos[2]);
    this->PaisResidenciaGenerado = new PaisDeResidencia(Nombre,Fecha,genero,Nacionalidad,PaisDeResidenciaGenerado);
    return this->PaisResidenciaGenerado;
}

QString generadorPaisResidencia::GenerarPaisDeResidencia(bool valido){
    QString PaisResidenciaGenerado;
    int maxPaisesResidencia, maxPaisesResidenciaValidos;
    QString * PaisesDeResidencia = this->atributos->getPaisesResidencia(maxPaisesResidencia);
    int * PaisesDeResidenciaValidos = this->ReglasDeNivel2->getPaisesDeResidenciaValidos(maxPaisesResidenciaValidos);
    int valorCentinela;
    if (valido){
        valorCentinela = this->rand.bounded(maxPaisesResidenciaValidos);
        PaisResidenciaGenerado = PaisesDeResidencia[PaisesDeResidenciaValidos[valorCentinela]];
    } else{
        valorCentinela = this->rand.bounded(this->max_nacionalidades - maxPaisesResidenciaValidos);
        PaisResidenciaGenerado = PaisesDeResidencia[valorCentinela];
    }
    return PaisResidenciaGenerado;
}
*/ //ESTO ME QUEDA HACERLO DENUEVO
