#include "generadordocumentacion.h"

GeneradorDocumentacion::GeneradorDocumentacion(AtributosComunes *datos, Reglas *rules)
{
    // Pendiente a implementar
    NivelActual = 0;
}

void GeneradorDocumentacion::getDocumentos(NPC *npc, bool newValidez)
{
    // Index va a ser quien se encargue de decirle a NPC donde guardar los documentos (segun el tipo)
    int Index = 0;
    Validez = newValidez;

    // Aca iria el sorteo de cuales documentos seran verdaderos y cuales falsos.

    GenerarDocumentosNivel1(Index);
    if (NivelActual >= 1){   // Generacion  Documentos de nivel 2

    }
    if (NivelActual >= 2){   // Generacion  Documentos de nivel 3

    }
    if (NivelActual >= 3){   // Generacion  Documentos de nivel 4

    }
    if (NivelActual >= 4){   // Generacion  Documentos de nivel 5

    }
}

void GeneradorDocumentacion::actualizarReglas(Reglas *newRules, int Nivel)
{
    this->rules = newRules;
    NivelActual = Nivel;
}

void GeneradorDocumentacion::GenerarDocumentosNivel1(int &Index)
{

}
