#include "generador_nuevaestancia.h"

Generador_NuevaEstancia::Generador_NuevaEstancia() {}

Generador_NuevaEstancia::~Generador_NuevaEstancia() {
    this->estancia = nullptr;
    this->paisesPaso.clear();
    this->bienesTransp.clear();
    ocupacion = "";
}

void Generador_NuevaEstancia::inicializadorNivel4(ReglasNivel1 *reglasLvl1, ReglasNivel4 *reglasLvl4, Estancia* estanciaOld) {
    this->estancia = estanciaOld;
    this->paisesPaso = reglasLvl4->getPaisesPasoValidos();
    this->bienesTransp = reglasLvl4->getBienesTranspValidos();
    this->ocupacion = reglasLvl4->getOcup();
}

NuevaEstancia *Generador_NuevaEstancia::getNuevaEstancia(bool valido, int dificultad) {
    // switch(dificultad) {}
    
    if (valido) {
        // vector campos validos ...
    } else {
        // vector campos invalidos ...
    }
}
