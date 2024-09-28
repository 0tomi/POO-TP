#include "generador_nuevaestancia.h"

#include <QTime>

Generador_NuevaEstancia::Generador_NuevaEstancia(): random(QTime::currentTime().msec()) {}

Generador_NuevaEstancia::~Generador_NuevaEstancia() {
    this->estancia = nullptr;
    this->paisesPaso.clear();
    //this->paisesPasoInvalidos.clear();
    this->bienesTransp.clear();
    //this->bienesTranspInvalidos.clear();
    ocupacion.clear();
    //ocupacionInvalida.clear();
    this->reglasLvl1 = nullptr;
    this->reglasLvl4 = nullptr;
}

void Generador_NuevaEstancia::inicializadorNivel4(ReglasNivel1 *reglasLvl1, ReglasNivel4 *reglasLvl4, Estancia* estanciaOld) {
    this->estancia = estanciaOld;
    this->paisesPaso = reglasLvl4->getPaisesPermitidos();
    //this->paisesPasoInvalidos = reglasLvl4->getPaisesNoPermitidos();
    this->bienesTransp = reglasLvl4->getBienesTransportadosPermitidos();
    //this->bienesTranspInvalidos = reglasLvl4->getBienesTransportadosNoPermitidos();
    this->ocupacion = reglasLvl4->getOcupacionPermitidos();
    //this->ocupacionInvalida = reglasLvl4->getOcupacionNoPermitidos();
    this->reglasLvl1 = reglasLvl1;
    this->reglasLvl4 = reglasLvl4;
}

NuevaEstancia *Generador_NuevaEstancia::getNuevaEstancia(bool valido, int dificultad) {
    // switch(dificultad) {}
    
    if (valido) {
        // generar campos randoms validos
    } else {
        // vector campos invalidos ...
    }
}

vector<QString> Generador_NuevaEstancia::generar_paisesPaso(bool valido) {
    vector<QString> paisesPasoRandom;
    int cant = random.bounded(3);
    
    if (cant == 0) { // NO HAY PAISES DE PASO
        paisesPasoRandom.push_back("");
        return paisesPasoRandom;
    }
    
    if (valido) { // genero campos randoms validos
        for (int i = 0; i < cant; i++) {
            paisesPasoRandom.push_back(paisesPaso[random.bounded(cant)]);
        }
    } else { // genero campos randoms incorrectos
        vector<QString> paisesPasoInvalidos = reglasLvl4->getPaisesNoPermitidos();
        for (int i = 0; i < cant; i++) {
            paisesPasoRandom.push_back(paisesPasoInvalidos[random.bounded(cant)]);
        }
    }
    
    return paisesPasoRandom;
}

vector<QString> Generador_NuevaEstancia::generar_bienesTransp(bool valido) {
    vector<QString> bienesTranspRandom;
    int cant = random.bounded(4);
    
    if (cant == 0) {
        bienesTranspRandom.push_back("");
        return bienesTranspRandom;
    }
    
    if (valido) {
        // ...
    } else {
        //...
    }
}
