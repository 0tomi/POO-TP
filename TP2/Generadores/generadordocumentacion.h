#ifndef GENERADORDOCUMENTACION_H
#define GENERADORDOCUMENTACION_H

#include "../AtributosComunes/atributoscomunes.h"
#include "../Documentos/documentacion.h"
#include "../Reglas/reglas.h"
#include "../NPC/npc.h"

using namespace std;

class GeneradorDocumentacion{
private:
    // Datos del juego:
    AtributosComunes* datos;
    reglas* rules;
    // Datos del Documento a generar:
    NPC* datosDeNPC;
    Documentacion* Doc2Generate;
public:
    GeneradorDocumentacion(AtributosComunes* datos, reglas* rules); // en ultima instancia se le puede pasar la clase NPC pero no esta definida
    Documentacion *getDocumentos(NPC* info);
};

#endif // GENERADORDOCUMENTACION_H
