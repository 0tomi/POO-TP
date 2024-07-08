#include "generadordocumentacion.h"

GeneradorDocumentacion::GeneradorDocumentacion(AtributosComunes *datos, Reglas *rules)
{
    // Pendiente a implementar
    NivelActual = 0;
}

void GeneradorDocumentacion::getDocumentos(NPC *npc, bool validez)
{
    // Generacion Documentos de nivel 1

    if (NivelActual >= 1){   // Generacion  Documentos de nivel 2

    }
    if (NivelActual >= 2){   // Generacion  Documentos de nivel 3

    }
    if (NivelActual >= 3){   // Generacion  Documentos de nivel 4

    }
    if (NivelActual >= 4){   // Generacion  Documentos de nivel 5

    }
    // A futuro, los nombres se deben decidir aca.

    // Aca iria el sorteo de cuales documentos seran verdaderos y cuales falsos.

    // Devuelve los documentos, pendiente a implementar
    npc->setEstancia(nullptr);
    npc->setPasaporte(nullptr);
}

void GeneradorDocumentacion::actualizarReglas(Reglas *newRules, int Nivel)
{
    this->rules = newRules;
    NivelActual = Nivel;
}
