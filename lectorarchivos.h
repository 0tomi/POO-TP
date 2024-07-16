#ifndef LECTORARCHIVOS_H
#define LECTORARCHIVOS_H
#include <QTextStream>

using namespace std;

class LectorArchivos{
public:
    LectorArchivos(QString direccion);
    void LeerArchivoNuevo(QString direccion);
    QString* getArray();
    int getTopeArray();
private:
    void rescaleVector(int cont);
    QString* archivo;
    int max;
};

#endif // LECTORARCHIVOS_H
