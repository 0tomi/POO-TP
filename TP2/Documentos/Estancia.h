#ifndef ESTANCIA_H
#define ESTANCIA_H

#include <string>
using namespace std;

class Estancia {
private:
    int duracionEst;
    string tipoEst;
public:
    Estancia(int, string);

    // getters
    int getDuracEstancia();
    string getTipoEstancia();
};

#endif // ESTANCIA_H
