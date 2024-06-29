#include "reglas.cpp"

// Falta completar
class Juego{
public:
    Juego();
    void start();
    void set();

    // Esto despues lo eliminamos
    string* getPaises(int &maxPaises);
    string* getVisitas(int &maxVisitas);
    reglas* getReglas();
private:
    // Atributos
    string* paises;
    int maxPaises;
    string tipoVisitas[3] = {"Turismo", "Trabajo", "Estudios"};

    // Reglas
    reglas* rules;

    // Metodos auxiliares
    void rescaleVector(int cont);
    void LeerPaises();
};