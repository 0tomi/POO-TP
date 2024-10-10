#ifndef GENERADOR_NUEVAESTANCIA_H
#define GENERADOR_NUEVAESTANCIA_H

#include "../Reglas/reglasnivel1.h"
#include "../Reglas/reglasnivel4.h"
#include "../Documentos/estancia.h"
#include "../Documentos/nuevaestancia.h"

#include <vector>
#include <QString>
#include <QRandomGenerator>

class Generador_NuevaEstancia
{
public:
    Generador_NuevaEstancia();
    ~Generador_NuevaEstancia();
    void inicializadorNivel4(ReglasNivel4* reglasLvl4, int dificultad, quint32 intSeed);
    NuevaEstancia* generar(Estancia*, bool valido);
private:
    struct trioDatos{
        QString dato;
        bool Permitido;
        bool Insertado;
    };

    const int MAX_OBJETOS = 4;

    vector<trioDatos> paisesPaso;
    int maxPaisesValidos;
    vector<trioDatos> bienesTransp;
    int maxBienesValidos;
    vector<trioDatos> ocupacion;
    int maxOcupacionesValidas;

    ReglasNivel4* reglasLvl4;
    Estancia * estanciaActual;
    QRandomGenerator random;

    int Dificultad;
    bool ValidezPaginas[3];
    void SortearPaginasFalsas(bool Validez);

    vector<trioDatos> makeTrio(const vector<QString>& listaOriginal, const vector<QString>& listaPermit);
    void resetTrio(vector<trioDatos>& trio);
    bool esPermitido(QString dato,const vector<QString>& listaPermit);

    vector<QString> generarDocumento(vector<trioDatos>& listaOriginal, QString& fraseCaso0,int MaxPermitido ,bool Validez);
    void generarListaConDatosVerdaderos(vector<QString>& lista2Generar, vector<trioDatos>& listaOriginal, QString& fraseCaso0, int MaxPermitido);
    void generarListaConDatosFalsos(vector<QString>& lista2Generar, vector<trioDatos>& listaOriginal, QString& fraseCaso0, int MaxPermitido);
    bool checkSiHayObjetosNoPermitidos(vector<QString>& lista2Generar, vector<trioDatos>& listaOriginal);
};

#endif // GENERADOR_NUEVAESTANCIA_H
