#include "generador_radiografia.h"

generador_Radiografia::generador_Radiografia() {

}

void generador_Radiografia::inicializar(ReglasNivel4 * rules, quint32 semilla, int dificultad)
{
    this->dificultad = dificultad;
    this->rules = rules;
    this->random.seed(semilla);
}

radiografia generador_Radiografia::generar_radiografia(bool validez)
{
    switch (this->dificultad){
        // Modo facil
    case 1: this->cantElementos = this->random.bounded(2);
        break;
        // Modo demonio
    case 3: this->cantElementos = this->random.bounded(5);
        break;
        // Modo normal
    default: this->cantElementos = this->random.bounded(3);
        break;
    }
    int cantValida; int cantInvalida;
    if (this->cantElementos == 0 && validez){
        this->radiografia2Generate = new radiografia(this->Elementos);
    }else{
        if (validez){ // si es valido
            generar_validos();
        } else{ //si es invalido

        }
    }

}

void generador_Radiografia::generar_validos()
{
    std::vector<QString> Permitidos = this->rules->getBienesTransportadosPermitidos();

    std::vector<bool> ObjetosUsados(Permitidos.size(), false);

    std::vector<bool> partesCuerpoUsadas(this->MAX_PARTESCUERPO, false);

    for (int i = 0; i < this->cantElementos; ++i) {
        ParDatos nuevoElemento;
        int sorteo;
        do {
            sorteo = this->random.bounded(Permitidos.size());
        } while (ObjetosUsados[sorteo]);
        nuevoElemento.Objeto = Permitidos[sorteo];
        ObjetosUsados[sorteo] = true;
        do {
            nuevoElemento.ParteCuerpo = this->random.bounded(this->MAX_PARTESCUERPO);
        } while (partesCuerpoUsadas[nuevoElemento.ParteCuerpo]);
        partesCuerpoUsadas[nuevoElemento.ParteCuerpo] = true;
        this->Elementos.push_back(nuevoElemento);
    }
}

void generador_Radiografia::generar_validos(int cant2Generate)
{
    std::vector<QString> Permitidos = this->rules->getBienesTransportadosPermitidos();

    std::vector<bool> ObjetosUsados(Permitidos.size(), false);

    std::vector<bool> partesCuerpoUsadas(this->MAX_PARTESCUERPO, false);

    for (int i = 0; i < cant2Generate; ++i) {
        ParDatos nuevoElemento;
        int sorteo;
        do {
            sorteo = this->random.bounded(Permitidos.size());
        } while (ObjetosUsados[sorteo]);
        nuevoElemento.Objeto = Permitidos[sorteo];
        ObjetosUsados[sorteo] = true;
        do {
            nuevoElemento.ParteCuerpo = this->random.bounded(this->MAX_PARTESCUERPO);
        } while (partesCuerpoUsadas[nuevoElemento.ParteCuerpo]);
        partesCuerpoUsadas[nuevoElemento.ParteCuerpo] = true;
        this->Elementos.push_back(nuevoElemento);
    }
}

