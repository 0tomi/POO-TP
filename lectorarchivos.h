#ifndef LECTORARCHIVOS_H
#define LECTORARCHIVOS_H
#include <QTextStream>
#include <vector>
#include <list>

using namespace std;

class LectorArchivos{
public:
    LectorArchivos();
    LectorArchivos(QString direccion);
    void LeerArchivoNuevo(QString direccion);
    std::vector<QString> getVector(QString direccion);
    std::vector<QString> getVector() const;
    std::list<QString> getList(QString direccion);
    std::list<QString> getList() const;
    QString* getArray();
    int getTopeArray();

private:
    void rescaleVector(int cont);
    QString* archivo;
    int max;
};

#endif // LECTORARCHIVOS_H
