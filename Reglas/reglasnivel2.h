#ifndef REGLASNIVEL2_H
#define REGLASNIVEL2_H
#include "reglas.h"
#include <vector>
#include <QString>
#include <QRandomGenerator>


class ReglasNivel2: public Reglas
{
public:
    ReglasNivel2();
    void generar_PaisesPermitidos(int Cantidad);
    void generar_PaisesPermitidos(std::vector<QString>& Lista_PaisesPermitidos);

    QString * getPaisesValidos(int &Max);
    QString* getPaisesInvalidos(int &Max);
private:
    std::vector<QString> paisesValidos;
    std::vector<QString> paisesInvalidos;
    QRandomGenerator Random;

};

#endif // REGLASNIVEL2_H
