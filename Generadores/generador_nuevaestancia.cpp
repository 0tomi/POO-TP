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

void Generador_NuevaEstancia::inicializadorNivel4(ReglasNivel1 *reglasLvl1, ReglasNivel4 *reglasLvl4, Estancia* estanciaOld, quint32 intSeed) {
    random.seed(intSeed); // inicializo semilla
    
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

NuevaEstancia* Generador_NuevaEstancia::getNuevaEstancia(bool valido, int dificultad) {
    // switch(dificultad) {}

    this->paisesPaso = generar_paisesPaso(valido);
    this->bienesTransp = generar_bienesTransp(valido);
    this->ocupacion = generar_ocupacion(valido);
    
    NuevaEstancia* newEst = new NuevaEstancia(this->estancia, this->paisesPaso, this->bienesTransp, this->ocupacion);
    return newEst;
}


vector<QString> Generador_NuevaEstancia::generar_paisesPaso(bool valido) {
    vector<QString> paisesPasoRandom;
    int cant = random.bounded(3);
    
    if (cant == 0) { // NO HAY PAISES DE PASO
        paisesPasoRandom.push_back("No posee paises de paso");
        return paisesPasoRandom;
    }
    
    if (valido) { // genero campos randoms validos
        for (int i = 0; i < cant; i++) {
            paisesPasoRandom.push_back(paisesPaso[random.bounded(paisesPaso.size())]);
        }
    } else { // genero campos randoms incorrectos
        vector<QString> paisesPasoInvalidos = reglasLvl4->getPaisesNoPermitidos();
        for (int i = 0; i < cant; i++) {
            paisesPasoRandom.push_back(paisesPasoInvalidos[random.bounded(paisesPasoInvalidos.size())]);
        }
    }
    
    return paisesPasoRandom;
}

vector<QString> Generador_NuevaEstancia::generar_bienesTransp(bool valido) {
    vector<QString> bienesTranspRandom;
    int cant = random.bounded(5);
    
    if (cant == 0) {
        bienesTranspRandom.push_back("No transporta bienes");
        return bienesTranspRandom;
    }
    
    if (valido) { // genero campos randoms validos
        for (int i = 0; i < cant; i++) {
            bienesTranspRandom.push_back(bienesTransp[random.bounded(bienesTransp.size())]);
        }
    } else {
        vector<QString> bienesTranspInvalidos = reglasLvl4->getBienesTransportadosNoPermitidos();
        for (int i = 0; i < cant; i++) {
            bienesTranspRandom.push_back(bienesTranspInvalidos[random.bounded(bienesTranspInvalidos.size())]);
        }
    }
    
    return bienesTranspRandom;
}

vector<QString> Generador_NuevaEstancia::generar_ocupacion(bool valido) {
    vector<QString> ocupacionesRandom;
    int cant = random.bounded(3);
    
    if (cant == 0) {
        ocupacionesRandom.push_back("Desocupado");
        return ocupacionesRandom;
    }
    
    if (valido) {
        for (int i = 0; i < cant; i++) {
            ocupacionesRandom.push_back(ocupacion[random.bounded(ocupacion.size())]);
        }
    } else {
        vector<QString> ocupacionesInvalidas = reglasLvl4->getOcupacionNoPermitidos();
        for (int i = 0; i < cant; i++) {
            ocupacionesRandom.push_back(ocupacionesInvalidas[random.bounded(ocupacionesInvalidas.size())]);
        }
    }
    
    return ocupacionesRandom;
}