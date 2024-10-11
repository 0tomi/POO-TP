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

ColaNPC::~ColaNPC()
{
    this->vaciarCola();
}

/// #################################### Añadir NPCs a cola ###################################################
void ColaNPC::addNPC(int NivelActual, int CantAldeano, int CantRefugiados, int CantDiplos, int CantRevolucionarios, int CantidadInvalidos)
{
    this->size = 0;
    this->cantidadNPCsFalsos = CantidadInvalidos;
    // Preparamos que nivel se usara.
    this->nivelActual = NivelActual;
    setNivel(nivelActual);

    int totalNPCs = CantAldeano + CantRefugiados + CantDiplos + CantRevolucionarios;

    // Para simplificar el codigo vamos a usar un array que guarde los contadores de los tipos
    int arrayTipos[] = {CantAldeano, CantRefugiados, CantDiplos, CantRevolucionarios};

    while (!GenerarNPCs(totalNPCs, CantidadInvalidos, arrayTipos)){
        arrayTipos[0] = CantAldeano; arrayTipos[1] = CantRefugiados; arrayTipos[2] = CantDiplos; arrayTipos[3] = CantRevolucionarios;
    }
}

bool ColaNPC::GenerarNPCs(int CantidadTotal, int CantidadFalsos, int CantidadTipos[])
{
    qDebug() << "Cantidad recibida para generar: " << CantidadTotal;
    qDebug() << "Cantidad recibida de falsos para generar: " << CantidadFalsos;
    this->vaciarCola();

    // Tipos: 0 Aldeano, 1 Refugiado, 2 Diplomatico, 3 Revolucionario
    int sorteo = Random.bounded(4);
    int sorteoValidez = Random.bounded(20);
    bool Validez = true;

    while (CantidadTotal){
        if (CantidadFalsos)
            if (sorteoValidez > 9)
                Validez = false;

        if (CantidadTipos[sorteo]){
            addNPC(sorteo, Validez);
            CantidadTipos[sorteo]--;
            CantidadTotal--;
            if (!Validez)
                CantidadFalsos--;
        }

        sorteo = Random.bounded(4);
        sorteoValidez = Random.bounded(20);
        Validez = true;
    }

    qDebug() << "Cantidad generada: " << CantidadTotal;
    qDebug() << "Cantidad falsa generada: " << CantidadFalsos;

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


