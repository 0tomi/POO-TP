#ifndef ATRIBUTOSCOMUNES_H
#define ATRIBUTOSCOMUNES_H
#include <string>
using namespace std;

class AtributosComunes{
public:
    AtributosComunes();
    void setAtributos(string* paises, int maxPaises);

    string* getPaises(int &maxPaises);
    string* getVisitas(int &maxVisitas);
    string* getEstadosCiviles(int &maxEC);

private:
    string* paises; int maxPaises;
    string tipoVisitas[3] = {"Turismo", "Trabajo", "Estudios"};
    string EstadosCiviles[4] = {"Solter", "Casad", "Divorciad", "Viud"};
};

#endif // ATRIBUTOSCOMUNES_H
