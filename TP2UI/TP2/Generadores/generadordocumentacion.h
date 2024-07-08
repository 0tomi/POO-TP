#ifndef GENERADORDOCUMENTACION_H
#define GENERADORDOCUMENTACION_H

#include "../AtributosComunes/atributoscomunes.h"
#include "../Documentos/documentacion.h"
#include "../Reglas/reglasnivel5.h"
#include "../NPC/npc.h"

using namespace std;

class GeneradorDocumentacion{
public:
    GeneradorDocumentacion(AtributosComunes* datos, Reglas* rules); // en ultima instancia se le puede pasar la clase NPC pero no esta definida
    void getDocumentos(NPC* info, bool validez);
    void actualizarReglas(Reglas* rules, int Nivel);

private:
    // Datos del juego:
    AtributosComunes* datos;
    Reglas* rules;
    int NivelActual;
    // Datos del Documento a generar:
    NPC* datosDeNPC;
    Documentacion* Doc2Generate;
};

#endif // GENERADORDOCUMENTACION_H
