#ifndef REGLASNIVEL2_H
#define REGLASNIVEL2_H
#include "reglas.h"
#include <vector>
#include <QString>


class ReglasNivel2: public Reglas
{
public:
    ReglasNivel2();
    void generar_PaisesPermitidos(int Cantidad);
    void generar_PaisesPermitidos(std::vector<QString>& Lista_PaisesPermitidos);

    std::vector<QString> getPaisesValidos() const;
    std::vector<QString> getPaisesInvalidos() const;


private:
    std::vector<parDatos> paisesPar;
    std::list<QString> paisesValidos;
    std::list<QString> paisesInvalidos;

};

#endif // REGLASNIVEL2_H
