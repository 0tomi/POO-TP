#ifndef RADIOGRAFIA_H
#define RADIOGRAFIA_H
#include <vector>
#include <QString>
using namespace std;
struct ParDatos{
    int ParteCuerpo;
    QString Objeto;
};
class radiografia
{
private:
    vector<ParDatos>Elementos;
public:
    radiografia(vector<ParDatos>&Elements);
};

#endif // RADIOGRAFIA_H
