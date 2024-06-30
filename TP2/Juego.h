#include "Niveles/reglas.cpp"
#include "AtributosComunes.cpp"

// Falta completar
class Juego{
public:
    Juego();
    void start();
    void set();

    // Esto despues lo eliminamos
    string* getPaises(int &maxPaises);
    reglas* getReglas();
    
private:
    // Atributos
    AtributosComunes* atributos;
    
    string* paises;
    int maxPaises;

    // Reglas
    reglas* rules;

    // Metodos auxiliares
    void rescaleVector(int cont);
    void LeerPaises();
};