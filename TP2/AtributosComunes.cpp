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
    string* paises;
    int maxPaises;
    string tipoVisitas[3] = {"Turismo", "Trabajo", "Estudios"};
    string EstadosCiviles[4] = {"Solter", "Casad", "Divorciad", "Viud"};
};

AtributosComunes::AtributosComunes(){
    this->paises = NULL;
    this->maxPaises = 0;
}

void AtributosComunes::setAtributos(string* pais, int maxPais){
    this->paises = pais;
    this->maxPaises = maxPais;
}

string* AtributosComunes::getPaises(int &max){
    max = this->maxPaises;
    return this->paises;
}

string* AtributosComunes::getVisitas(int &max){
    max = 3;
    return this->tipoVisitas;
}

string* AtributosComunes::getEstadosCiviles(int &max){
    max = 4;
    return this->EstadosCiviles;
}