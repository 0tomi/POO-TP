#ifndef REGLASNIVEL4_H
#define REGLASNIVEL4_H
#include "reglas.h"
#include <QRandomGenerator>

// Las reglas de la estancia se sacaran de las reglas de nivel 1
class ReglasNivel4: public Reglas
{
public:
    ReglasNivel4();
    void setSeed (int Seed);
    void generar_PaisesPaso(int CantPermitida);
    void generar_PaisesPaso(std::vector<QString> ListaPaisesPermitidos);
    void generar_Ocupacion(int CantPermitida);
    void generar_Ocupacion(std::vector<QString> ListaOcupacionPermitidos);
    void generar_BienesTransportados(int CantPermitida);
    void generar_BienesTransportados(std::vector<QString> ListaBienesTransportadosPermitidos);

    std::vector<QString> getPaisesPermitidos() const;
    std::vector<QString> getPaisesNoPermitidos() const;
    std::vector<QString> getOcupacionPermitidos() const;
    std::vector<QString> getOcupacionNoPermitidos() const;
    std::vector<QString> getBienesTransportadosPermitidos() const;
    std::vector<QString> getBienesTransportadosNoPermitidos() const;

private:
    std::vector<QString> PaisesPermitidos;
    std::vector<QString> PaisesNoPermitidos;
    std::vector<QString> OcupacionPermitidos;
    std::vector<QString> OcupacionNoPermitidos;
    std::vector<QString> BienesTransportadosPermitidos;
    std::vector<QString> BienesTransportadosNoPermitidos;
    QRandomGenerator Random;
};

#endif // REGLASNIVEL4_H
