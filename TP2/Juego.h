#include "Niveles/reglas.cpp"
#include "AtributosComun/AtributosComunes.cpp"

// Falta completar
class Juego{
public:
    Juego();
    void start();
    void set();

    // Esto despues lo eliminamos
    reglas* getReglas();
    
private:
    // Atributos
    AtributosComunes* atributos;

    // Reglas
    reglas* rules;

    // Metodos auxiliares
    string* rescaleVector(string* oldVector, int max, int cont);
    void LeerPaises();
};