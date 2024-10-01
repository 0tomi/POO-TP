#ifndef REGLASNIVEL5_H
#define REGLASNIVEL5_H
#include "reglas.h"

class ReglasNivel5: public Reglas
{
public:
    ReglasNivel5();
    void generar_ObjetosPermitidos(int Cantidad);
    void generar_ObjetosPermitidos(std::vector<QString> ListaPermitidos);
    std::vector<QString> getObjetos() const;
    std::vector<QString> getObjetosPermitidos() const;
    std::vector<QString> getObjetosNoPermitidos() const;

private:
    std::vector<parDatos> Objetos;
    std::list<QString> ObjetosPermitidos;
    std::list<QString> ObjetosNoPermitidos;
};

#endif // REGLASNIVEL5_H
