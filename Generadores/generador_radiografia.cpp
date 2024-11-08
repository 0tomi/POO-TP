#include "generador_radiografia.h"

void generador_Radiografia::SetDatosFalsos(bool Validez, radiografia *doc)
{
    if (Validez)
        return;

    doc->addDatosFalsos(this->DatosFalsos);
}

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
}

radiografia* generador_Radiografia::generar_radiografia(bool validez)
{
    if (!this->Elementos.empty())
        this->Elementos.clear();

    if (this->cantElementos == 0 && validez){
        this->radiografia2Generate = new radiografia(this->Elementos);
    }else{
        if (validez){ // si es valido
            generar_validos();
        } else{ //si es invalido
            qDebug() << "Cantidad de elementos del generador: " << cantElementos;
            if (this->cantElementos == 0){
                this->cantElementos++; // para que al menos se genere un elemento invalido
            }
            int cantValida; int cantInvalida;
            cantInvalida = this->random.bounded(this->cantElementos) + 1;
            generar_invalidos(cantInvalida);
            if (cantInvalida != this->cantElementos){
                cantValida = this->cantElementos - cantInvalida;
                generar_validos(cantValida);
            }

        }
    }
    this->radiografia2Generate = new radiografia(this->Elementos);
    SetDatosFalsos(validez, radiografia2Generate);
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
            sorteo = this->random.bounded(this->ObjetosInvalidos.size());
        } while (ObjetosUsados[sorteo]);
        nuevoElemento.Objeto = this->ObjetosInvalidos[sorteo];
        this->DatosFalsos += nuevoElemento.Objeto + ", ";
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

