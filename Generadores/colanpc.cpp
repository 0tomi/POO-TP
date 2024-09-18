#include "colanpc.h"
#include <ctime>
#include <QDebug>

/// #################################### CONSTRUCTOR ###################################################
ColaNPC::ColaNPC():
    Random(time(NULL)), GenerarNPC(&Random), GenerarDocumentacion()
{
    this->frente = this->fondo = NULL;
    this->size = 0;
    this->sizeOriginal = 0;
}

void ColaNPC::Inicializar(int Nivel, int Dificultad, Reglas **rules)
{
    // Aca irian las reglas que le pase juego al leer los niveles
    GenerarDocumentacion.Inicializar(Nivel, Dificultad, rules);
}

ColaNPC::~ColaNPC()
{
    this->vaciarCola();
    //delete NPCaRetornar;
}

/// #################################### Añadir NPCs a cola ###################################################
void ColaNPC::addNPC(int NivelActual, int CantAldeano, int CantRefugiados, int CantDiplos, int CantRevolucionarios, int CantidadInvalidos)
{
    this->size = 0;
    this->sizeOriginal = 0;
    // Preparamos que nivel se usara.
    nivelActual = NivelActual;
    setNivel(nivelActual);

    int totalNPCs = CantAldeano + CantRefugiados + CantDiplos + CantRevolucionarios;

    // Para simplificar el codigo vamos a usar un array que guarde los contadores de los tipos
    int arrayTipos[] = {CantAldeano, CantRefugiados, CantDiplos, CantRevolucionarios};

    // Tipos: 0 Aldeano, 1 Refugiado, 2 Diplomatico, 3 Revolucionario
    int sorteo = Random.bounded(4);
    int sorteoValidez = Random.bounded(20);
    bool Validez = true;

    qDebug() << "Bucle de generar NPCs";
    while (totalNPCs){
        // Si hay NPCs invalidos a colocar, sorteamos y decidimos si se generaran en la iteracion.
        if (CantidadInvalidos)
            if (sorteoValidez > 11){
                Validez = false;
                CantidadInvalidos--;
            }
        // Genera el tipo de NPC, basado en si el contador llego a 0; si llega a 0 no genera mas npcs de ese tipo.
        if (arrayTipos[sorteo]){
            addNPC(sorteo, Validez); // Sumamos a la cola el npc con el tipo sorteado.
            arrayTipos[sorteo]--;
            totalNPCs--;            // Restamos el contador de tipos de npc, y el total.
        }
        sorteo = Random.bounded(4);
        sorteoValidez = Random.bounded(20);
        Validez = true;
    }
}

void ColaNPC::addNPC(int Tipo, bool Validez){
    // Genero el NPC nuevo
    NPC* newNPC = GenerarNPC.getNPCgenerico(Tipo, Validez, nivelActual); // A futuro actualizar para que reciba el nivel

    // Genero su documentacion
    GenerarDocumentacion.getDocumentos(newNPC, Validez); // A futuro actualizar para que reciba el nivel

    // Generamos el dialogo del npc
    GenerarNPC.generarDialogos(newNPC, nivelActual);

    // Genero el nodo de la cola donde estara el npc
    nodoNPC* newNode = new nodoNPC;
    newNode->info = newNPC;

    // Acomodamos la cola de NPCs
    if (this->size == 0){
        this->frente = this->fondo = newNode;
    } else {
        this->fondo->link = newNode;
        this->fondo = newNode;
    }

    size++;
    sizeOriginal++;
}
/// #################################### Vaciar cola ###################################################
void ColaNPC::vaciarCola()
{
    nodoNPC* aux = this->frente;
    nodoNPC* aux2;
    while(aux != NULL){
        aux2 = aux->link;
        // Eliminamos el NPC
        delete aux->info;
        delete aux;

        aux = aux2;
    }

    this->sizeOriginal = 0;
    this->size = 0;
}

/// #################################### Setters ###################################################
void ColaNPC::setDificultad(int newDificultad)
{
    GenerarDocumentacion.setDificultad(newDificultad);
}

void ColaNPC::setNivel(int Nivel)
{
    GenerarDocumentacion.setNivel(Nivel);
}

/// #################################### GETTERS ###################################################
NPC* ColaNPC::getNPC(){
    // Si la cola esta vacia
    if (this->size == 0)
        return NULL;

    // Se elimina el NPC anterior, si es que hay anterior.
    if (size < sizeOriginal)
        delete NPCaRetornar;

    nodoNPC* node2remove = frente;
    NPCaRetornar = frente->info;

    frente = frente->link;
    delete node2remove;
    size--;

    return NPCaRetornar;
}

int ColaNPC::getSize() const
{
    return size;
}


