#ifndef RADIOGRAFIA_H
#define RADIOGRAFIA_H
#include "documentacion.h"
#include <vector>
#include <QString>
using namespace std;
struct ParDatos{
    int ParteCuerpo;
    QString Objeto;
};
class radiografia : public Documentacion
{
private:
    vector<ParDatos>Elementos;
public:
    radiografia(vector<ParDatos>&Elements);
    vector<ParDatos>& GetVector();
};

#endif // RADIOGRAFIA_H
