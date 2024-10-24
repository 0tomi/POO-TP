#include "colanpc.h"
#include <QTime>
#include <QDebug>

/// #################################### CONSTRUCTOR ###################################################
ColaNPC::ColaNPC():
    Random(QTime::currentTime().msec()), GenerarNPC(&Random), GenerarDocumentacion()
{
    this->size = 0;
}

void ColaNPC::setSeed(quint32 seed)
{
    this->semillaActual = seed;
    Random.seed(seed);
    GenerarNPC.setSeed(seed);
    GenerarDocumentacion.setSeed(seed);
}

void ColaNPC::Inicializar(int Nivel, int Dificultad, Reglas **rules, quint32 seed)
{
    // Aca irian las reglas que le pase juego al leer los niveles
    this->setSeed(seed);
    GenerarDocumentacion.Inicializar(Nivel, Dificultad, rules, this->semillaActual);
}

void ColaNPC::setUpColaEmpezada(int cantidad_NPCs_pasados)
{
    if (cantidad_NPCs_pasados > this->size)
        return;

    this->size -= cantidad_NPCs_pasados;
}

ColaNPC::~ColaNPC()
{
    this->vaciarCola();
}

/// #################################### Añadir NPCs a cola ###################################################
void ColaNPC::addNPC(int NivelActual, int CantAldeano, int CantRefugiados, int CantDiplos, int CantRevolucionarios, int CantidadInvalidos)
{
    this->vaciarCola();
    this->size = 0;
    this->cantidadNPCsFalsos = CantidadInvalidos;
    // Preparamos que nivel se usara.
    this->nivelActual = NivelActual;
    setNivel(nivelActual);

    int totalNPCs = CantAldeano + CantRefugiados + CantDiplos + CantRevolucionarios;

    // Para simplificar el codigo vamos a usar un array que guarde los contadores de los tipos
    int arrayTipos[] = {CantAldeano, CantRefugiados, CantDiplos, CantRevolucionarios};

    NPCSaGenerar.resize(totalNPCs);
    VectorNPCs.reserve(totalNPCs);

    // Generamos la lista de los NPCs que pasaran.
    int intentos = 1;
    while (!GenerarNPCs(totalNPCs, CantidadInvalidos, arrayTipos)){
        intentos++;
        arrayTipos[0] = CantAldeano; arrayTipos[1] = CantRefugiados;
        arrayTipos[2] = CantDiplos; arrayTipos[3] = CantRevolucionarios;
    }
    qDebug() << "Cantidad de intentos en generar la lista de NPCs: " << intentos;

    // Creamos los NPCs
    for (const auto& NPCs : NPCSaGenerar){
        qDebug() << NPCs.Validez;
        addNPC(NPCs.Tipo, NPCs.Validez);
    }

    NPCSaGenerar.clear();
    NPCSaGenerar.shrink_to_fit();
}

bool ColaNPC::GenerarNPCs(int CantidadTotal, int CantidadFalsos, int CantidadTipos[])
{
    for (int i = 0; i < CantidadTotal; i++)
        NPCSaGenerar[i].Validez = true;

    // Tipos: 0 Aldeano, 1 Refugiado, 2 Diplomatico, 3 Revolucionario
    qDebug() << "Bucle validez";
    int sorteoValidez = Random.bounded(CantidadTotal);
    while (CantidadFalsos){
        if (NPCSaGenerar[sorteoValidez].Validez){
            NPCSaGenerar[sorteoValidez].Validez = false;
            CantidadFalsos--;
        }
        sorteoValidez = Random.bounded(CantidadTotal);
    }

    qDebug() << "Bucle Tipos";
    int sorteo = Random.bounded(4);
    int i = 0, Cant2Generar = CantidadTotal;
    while (Cant2Generar) {
        if (CantidadTipos[sorteo]){
            NPCSaGenerar[i].Tipo = sorteo;
            CantidadTipos[sorteo]--;
            Cant2Generar--;
            i++;
        }
        sorteo = Random.bounded(4);
    }

    if (CantidadTotal == 0 && CantidadFalsos == 0)
        return true;
    else return false;
}

int ColaNPC::getCantidadNPCsFalsos() const
{
    return cantidadNPCsFalsos;
}


void ColaNPC::addNPC(int Tipo, bool Validez){
    // Genero el NPC nuevo
    NPC* newNPC = GenerarNPC.getNPCgenerico(Tipo, Validez, nivelActual); // A futuro actualizar para que reciba el nivel

    // Genero su documentacion
    GenerarDocumentacion.getDocumentos(newNPC, Validez); // A futuro actualizar para que reciba el nivel

    // Generamos el dialogo del npc
    GenerarNPC.generarDialogos(newNPC, nivelActual);

    VectorNPCs.push_back(newNPC);
    size++;
}

/// #################################### Vaciar cola ###################################################
void ColaNPC::vaciarCola()
{
    for (NPC* ptr: VectorNPCs)
        delete ptr;
    VectorNPCs.clear();

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
    NPCaRetornar = VectorNPCs[size-1];
    size--;

    return NPCaRetornar;
}

int ColaNPC::getSize() const
{
    return size;
}


