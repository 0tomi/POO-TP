#include "generador_radiografia.h"

generador_Radiografia::generador_Radiografia() {

}

void generador_Radiografia::inicializar(ReglasNivel5 * rules, quint32 semilla)
{
    this->rules = rules;
    this->random.seed(semilla);
}
