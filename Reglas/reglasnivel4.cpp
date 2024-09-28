#include "reglasnivel4.h"
#include <QTime>

ReglasNivel4::ReglasNivel4(): Reglas(), Random(QTime::currentTime().msec()) {}

void ReglasNivel4::generarPaisesPasoValidos(int cant, vector<QString>& listaPaisesPasoValidos) {
    //if (!ValidarDatos())
    paisesPasoValidos.clear();
    
    if (cant < 1)
        cant = Random.bounded(listaPaisesPasoValidos.size()) + 1;
    
    paisesPasoValidos.resize(cant);
    
    for (int i = 0; i < cant; i++) {
        int listLeng = listaPaisesPasoValidos.size();
        paisesPasoValidos[i] = listaPaisesPasoValidos[Random.bounded(listLeng)];
    }
}

void ReglasNivel4::generarBienesTranspValidos(int cant, vector<QString> &listaBienesTranspValidos) {
    bienesTranspValidos.clear();
    
    if (cant < 1)
        cant = Random.bounded(listaBienesTranspValidos.size()) + 1;
    
    bienesTranspValidos.resize(cant);
    
    for (int i = 0; i < cant; i++) {
        int listLeng = listaBienesTranspValidos.size();
        bienesTranspValidos[i] = listaBienesTranspValidos[Random.bounded(listLeng)];
    }
}

void ReglasNivel4::generarOcupacionValida(vector<QString> ocupacionesValidas) {
    ocupacion = ocupacionesValidas[Random.bounded(ocupacionesValidas.size())];
}

// getters
vector<QString> ReglasNivel4::getPaisesPasoValidos() const {
    return paisesPasoValidos;
}

vector<QString> ReglasNivel4::getBienesTranspValidos() const {
    return bienesTranspValidos;
}

QString ReglasNivel4::getOcup() {
    return ocupacion;
}