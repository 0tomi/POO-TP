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

    std::vector<QString> getPaisesValidos() const;
    std::vector<QString> getPaisesInvalidos() const;
    QString* getPaisesValidos(int &Max) const;
    QString* getPaisesInvalidos(int &Max) const;
private:
    std::vector<QString> paisesValidos;
    std::vector<QString> paisesInvalidos;
    QRandomGenerator Random;

};

#endif // REGLASNIVEL2_H
