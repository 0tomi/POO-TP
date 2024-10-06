#ifndef REGLASNIVEL4_H
#define REGLASNIVEL4_H
#include "reglas.h"
#include <list>

// Las reglas de la estancia se sacaran de las reglas de nivel 1
class ReglasNivel4: public Reglas
{
public:
    ReglasNivel4();
    void generar_Todo(int CantidadPaises, int CantidadOcupaciones, int CantidadBienes);
    void generar_PaisesPaso(int CantPermitida);
    void generar_PaisesPaso(std::vector<QString> ListaPaisesPermitidos);
    void generar_Ocupacion(int CantPermitida);
    void generar_Ocupacion(std::vector<QString> ListaOcupacionPermitidos);
    void generar_BienesTransportados(int CantPermitida);
    void generar_BienesTransportados(std::vector<QString> ListaBienesTransportadosPermitidos);

    std::vector<QString> getPaises() const;
    std::vector<QString> getOcupaciones() const;
    std::vector<QString> getBienes() const;

    std::vector<QString> getPaisesPermitidos() const;
    std::vector<QString> getPaisesNoPermitidos() const;
    std::vector<QString> getOcupacionPermitidos() const;
    std::vector<QString> getOcupacionNoPermitidos() const;
    std::vector<QString> getBienesTransportadosPermitidos() const;
    std::vector<QString> getBienesTransportadosNoPermitidos() const;

private:
    std::vector<parDatos> PaisesPaso;
    std::vector<parDatos> Ocupaciones;
    std::vector<parDatos> Bienes;

    std::list<QString> PaisesPermitidos;
    std::list<QString> PaisesNoPermitidos;
    std::list<QString> OcupacionPermitidos;
    std::list<QString> OcupacionNoPermitidos;
    std::list<QString> BienesPermitidos;
    std::list<QString> BienesNoPermitidos;
};

#endif // REGLASNIVEL4_H
