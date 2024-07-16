#include "generadordocumentacion.h"
#include <ctime>
#include <QDebug>

GeneradorDocumentacion::GeneradorDocumentacion(AtributosComunes *datos, Reglas **newRules)
{
    NivelActual = 1;
    DificultadJuego = 1;
    SetDificultadNivel();

    // Asignamos las reglas correspondientes
    reglasNivel1 = dynamic_cast<ReglasNivel1*>(newRules[0]);
    reglasNivel2 = dynamic_cast<ReglasNivel2*>(newRules[1]);
    reglasNivel3 = dynamic_cast<ReglasNivel3*>(newRules[2]);
    reglasNivel4 = dynamic_cast<ReglasNivel4*>(newRules[3]);
    reglasNivel5 = dynamic_cast<ReglasNivel5*>(newRules[4]);

    // Semilla para el generador
    quint32 Semilla = static_cast<quint32>(time(NULL));
    NumeroRandom.seed(Semilla);

    // Pendiente a implementar
    // News de generadores

    // Generador pasaportes
    generadorPasaporte = new Generar_pasaporte(reglasNivel1, datos);

    // Generador estancia
    int maxVisitas, maxVisitasValidas;
    QString* Visitas = datos->getVisitas(maxVisitas);
    QString* VisitasValidas = reglasNivel1->getTipoDeVisitaValida();
    maxVisitasValidas = reglasNivel1->getMaxVisitasPermitidas();
    generadorEstancia = new GenerarEstancia(Visitas,
                                            maxVisitas,
                                            VisitasValidas,
                                            maxVisitasValidas,
                                            reglasNivel1->getDuracionEstanciaPermitida());

    // Siguientes generadores
}

GeneradorDocumentacion::~GeneradorDocumentacion()
{
    delete generadorEstancia;
}

void GeneradorDocumentacion::getDocumentos(NPC *npc, bool Validez)
{
    // Index va a ser quien se encargue de decirle a NPC donde guardar los documentos (segun el tipo)
    int Index = 0;
    NPC2Generate = npc;

    // Aca iria el sorteo de cuales documentos seran verdaderos y cuales falsos.
    if (Validez)
        for (int i = 0; i < 10; i++)
            DocsValidos[i] = true;
    else
        GenerarCantidadDocsInvalidos();


    GenerarDocumentosNivel1(Index);

    if (NivelActual >= 2){
        GenerarDocumentosNivel2(Index);
    }
    if (NivelActual >= 3){
        GenerarDocumentosNivel3(Index);
    }
    if (NivelActual >= 4){
        GenerarDocumentosNivel4(Index);
    }
    if (NivelActual >= 5){
        GenerarDocumentosNivel5(Index);
    }
}

void GeneradorDocumentacion::actualizarReglas(Reglas **newRules, int Nivel)
{
    reglasNivel1 = dynamic_cast<ReglasNivel1*>(newRules[0]);
    reglasNivel2 = dynamic_cast<ReglasNivel2*>(newRules[1]);
    reglasNivel3 = dynamic_cast<ReglasNivel3*>(newRules[2]);
    reglasNivel4 = dynamic_cast<ReglasNivel4*>(newRules[3]);
    reglasNivel5 = dynamic_cast<ReglasNivel5*>(newRules[4]);
    NivelActual = Nivel;
}

void GeneradorDocumentacion::nextNivel(int Nivel)
{
    NivelActual = Nivel;
    SetDificultadNivel();
}

void GeneradorDocumentacion::GenerarCantidadDocsInvalidos()
{
    int CantDocumentosInvalidos = 0;
    int ValorCentinela;

    // Si es el primer nivel hacemos que esto pueda variar para hacerla mas facil.
    if (NivelActual == 1)
        MaxDocumentosInvalidos = NumeroRandom.bounded(1,3);

    // Lo repetimos hasta que nos genere la cantidad necesaria de documentos invalidos.
    while (CantDocumentosInvalidos != MaxDocumentosInvalidos){
        for (int i = 0; i < MaxDocumentos; i++){
            ValorCentinela = NumeroRandom.bounded(0,10);
            if (ValorCentinela < 4){
                DocsValidos[i] = false;
                CantDocumentosInvalidos++;
            } else
                DocsValidos[i] = true;
        }
    }
}

void GeneradorDocumentacion::SetDificultadNivel()
{
    switch (NivelActual) {
    case 1:
        MaxDocumentos = 2;
        MaxDocumentosInvalidos = 1;
        break;
    case 2:
        MaxDocumentos = 4;
        MaxDocumentosInvalidos = 2;
        break;
    case 3:
        MaxDocumentos = 6;
        MaxDocumentosInvalidos = 3;
        break;
    case 4:
        MaxDocumentos = 8;
        MaxDocumentosInvalidos = 4;
        break;
    default:
        MaxDocumentos = 10;
        MaxDocumentosInvalidos = 2;
        break;
    }
}

void GeneradorDocumentacion::GenerarDocumentosNivel1(int &Index)
{
    // Generador de pasaportes - DNI
    Pasaporte* nuevoPasaporte = generadorPasaporte->crear_pasaporte(DocsValidos[Index], NPC2Generate->getGenero(), DificultadJuego);
    NPC2Generate->addDocumento(nuevoPasaporte, Index);
    Index++;

    // Generador de Estancias
    Estancia* nuevaEstancia = generadorEstancia->getEstancia(DocsValidos[Index], DificultadJuego);
    NPC2Generate->addDocumento(nuevaEstancia, Index);
    Index++;
}

void GeneradorDocumentacion::GenerarDocumentosNivel2(int &Index)
{

}

void GeneradorDocumentacion::GenerarDocumentosNivel3(int &Index)
{

}

void GeneradorDocumentacion::GenerarDocumentosNivel4(int &Index)
{

}

void GeneradorDocumentacion::GenerarDocumentosNivel5(int &Index)
{

}
