#ifndef LECTORARCHIVOS_H
#define LECTORARCHIVOS_H

#include <string>
using namespace std;

class LectorArchivos{
public:
    LectorArchivos(string direccion);
    void LeerArchivoNuevo(string direccion);
    string* getArray();
    int getTopeArray();
private:
    void rescaleVector(int cont);
    string* archivo;
    int max;
};

#endif // LECTORARCHIVOS_H
