#ifndef GENERADORDOCUMENTACION_H
#define GENERADORDOCUMENTACION_H

#include "../AtributosComunes/atributoscomunes.h"
#include "../Documentos/documentacion.h"
#include "../Reglas/reglasnivel1.h"
#include "../NPC/npc.h"

using namespace std;

class GeneradorDocumentacion{
private:
    // Datos del juego:
    AtributosComunes* datos;
    Reglas* rules;
    // Datos del Documento a generar:
    NPC* datosDeNPC;
    Documentacion* Doc2Generate;
public:
    GeneradorDocumentacion(AtributosComunes* datos, Reglas* rules); // en ultima instancia se le puede pasar la clase NPC pero no esta definida
    Documentacion *getDocumentos(NPC* info, bool validez);
};

#endif // GENERADORDOCUMENTACION_H
