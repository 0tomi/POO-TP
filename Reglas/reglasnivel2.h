#ifndef REGLASNIVEL2_H
#define REGLASNIVEL2_H
#include "reglasnivel1.h"
#include <vector>


class ReglasNivel2: public Reglas
{
public:
    ReglasNivel2();
    void generar_PaisesPermitidos(int Cantidad);
    void generar_PaisesPermitidos(std::vector<QString> Lista_PaisesPermitidos);

    QString* getPaisesValidos(int &Max);
    QString* getPaisesInvalidos(int &Max);
private:
    std::vector<QString> paisesValidos;
    std::vector<QString> paisesInvalidos;

};

#endif // REGLASNIVEL2_H
