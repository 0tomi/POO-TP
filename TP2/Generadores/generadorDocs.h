#include "generadorNPC.h" // a futuro para que tengan las cosas de los npcs
#include "../Documentos/Estancia.h"
#include "../Documentos/Pasaporte.h"
#include "../AtributosComun/AtributosComunes.h"
#include "../Documentos/Documentacion.h"
#include "../Niveles/reglas.h"

#include <string>
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
        Documentacion* getDocumentos();
};

