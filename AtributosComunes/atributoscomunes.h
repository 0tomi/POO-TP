#ifndef ATRIBUTOSCOMUNES_H
#define ATRIBUTOSCOMUNES_H
#include <QString>
using namespace std;

class AtributosComunes{
public:
    AtributosComunes();
    void setAtributos(QString* paises, int maxPaises);

    QString* getPaises(int &maxPaises);
    QString* getVisitas(int &maxVisitas);
    QString* getEstadosCiviles(int &maxEC);

    ~AtributosComunes();

private:
    QString* paises; int maxPaises;
    QString tipoVisitas[3] = {"Turismo", "Trabajo", "Estudios"};
    QString EstadosCiviles[4] = {"Solter", "Casad", "Divorciad", "Viud"};
};

#endif // ATRIBUTOSCOMUNES_H
