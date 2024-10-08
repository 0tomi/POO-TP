#include "generador_radiografia.h"

generador_Radiografia::generador_Radiografia() {
    LectorArchivos archivo(":/Niveles/Nivel5/ObjetosValidos.txt");
    this->ObjetosValidos = archivo.getVector();
    archivo.LeerArchivoNuevo(":/Niveles/Nivel5/ObjetosInvalidos.txt");
    this->ObjetosInvalidos = archivo.getVector();
}

void generador_Radiografia::inicializar(ReglasNivel4 * rules, quint32 semilla, int dificultad)
{
    this->dificultad = dificultad;
    this->rules = rules;
    this->random.seed(semilla);
}

radiografia* generador_Radiografia::generar_radiografia(bool validez)
{
    this->Elementos.clear();
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

    if (this->cantElementos == 0 && validez){
        this->radiografia2Generate = new radiografia(this->Elementos);
    }else{
        if (validez){ // si es valido
            generar_validos();
        } else{ //si es invalido
            if (this->cantElementos == 0){
                this->cantElementos++; // para que al menos se genere un elemento invalido
            }
            int cantValida; int cantInvalida;
            cantInvalida = this->random.bounded(1,this->cantElementos);
            generar_invalidos(cantInvalida);
            if (cantInvalida != this->cantElementos) cantValida = this->cantElementos - cantInvalida;

        }
    }
    this->radiografia2Generate = new radiografia(this->Elementos);
    return this->radiografia2Generate;
}

void generador_Radiografia::generar_validos()
{

    std::vector<bool> ObjetosUsados(this->ObjetosValidos.size(), false);

    std::vector<bool> partesCuerpoUsadas(this->MAX_PARTESCUERPO, false);

    for (int i = 0; i < this->cantElementos; ++i) {
        ParDatos nuevoElemento;
        int sorteo;
        do {
            sorteo = this->random.bounded(this->ObjetosValidos.size());
        } while (ObjetosUsados[sorteo]);
        nuevoElemento.Objeto = this->ObjetosValidos[sorteo];
        ObjetosUsados[sorteo] = true;
        do {
            nuevoElemento.ParteCuerpo = this->random.bounded(this->MAX_PARTESCUERPO);
        } while (partesCuerpoUsadas[nuevoElemento.ParteCuerpo]);
        partesCuerpoUsadas[nuevoElemento.ParteCuerpo] = true;
        this->Elementos.push_back(nuevoElemento);
    }
}

void generador_Radiografia::generar_invalidos(int cant2Generate)
{
    std::vector<bool> ObjetosUsados(this->ObjetosValidos.size(), false);

    std::vector<bool> partesCuerpoUsadas(this->MAX_PARTESCUERPO, false);

    for (int i = 0; i < cant2Generate; ++i) {
        ParDatos nuevoElemento;
        int sorteo;
        do {
            sorteo = this->random.bounded(this->ObjetosValidos.size());
        } while (ObjetosUsados[sorteo]);
        nuevoElemento.Objeto = this->ObjetosValidos[sorteo];
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
    std::vector<bool> ObjetosUsados(this->ObjetosValidos.size(), false);

    std::vector<bool> partesCuerpoUsadas(this->MAX_PARTESCUERPO, false);

    for (int i = 0; i < cant2Generate; ++i) {
        ParDatos nuevoElemento;
        int sorteo;
        do {
            sorteo = this->random.bounded(this->ObjetosValidos.size());
        } while (ObjetosUsados[sorteo]);
        nuevoElemento.Objeto = this->ObjetosValidos[sorteo];
        ObjetosUsados[sorteo] = true;
        do {
            nuevoElemento.ParteCuerpo = this->random.bounded(this->MAX_PARTESCUERPO);
        } while (partesCuerpoUsadas[nuevoElemento.ParteCuerpo]);
        partesCuerpoUsadas[nuevoElemento.ParteCuerpo] = true;
        this->Elementos.push_back(nuevoElemento);
    }
}

