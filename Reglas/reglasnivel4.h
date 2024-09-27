#ifndef REGLASNIVEL4_H
#define REGLASNIVEL4_H
#include "reglas.h"

#include <vector>
#include <QString>
#include <QRandomGenerator>

using namespace std;

class ReglasNivel4: public Reglas
{
private:
    vector<QString> paisesPasoValidos;
    vector<QString> bienesTranspValidos;
    QString ocupacion;

    QRandomGenerator Random;
public:
    ReglasNivel4();
    void generarPaisesPasoValidos(int cant, vector<QString>& listaPaisesPasoValidos);
    void generarBienesTranspValidos(int cant, vector<QString>& listaBienesTranspValidos);
    void generarOcupacionValida(vector<QString> ocupacionesValidas);

    // getters
    vector<QString> getPaisesPasoValidos() const;
    vector<QString> getBienesTranspValidos() const;
    QString getOcup();
};

#endif // REGLASNIVEL4_H
