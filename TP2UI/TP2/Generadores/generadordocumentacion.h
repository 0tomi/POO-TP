#ifndef GENERADORDOCUMENTACION_H
#define GENERADORDOCUMENTACION_H

#include "../AtributosComunes/atributoscomunes.h"
#include "../Documentos/documentacion.h"
#include "../Reglas/reglasnivel5.h"
#include "../NPC/npc.h"
#include "../Generadores/generarestancia.h"

#include <QRandomGenerator>

using namespace std;

class GeneradorDocumentacion{
public:
    GeneradorDocumentacion(AtributosComunes* datos, Reglas** rules); // en ultima instancia se le puede pasar la clase NPC pero no esta definida
    void getDocumentos(NPC* info, bool validez);
    void actualizarReglas(Reglas** rules, int Nivel);
    void nextNivel(int Nivel);
    ~GeneradorDocumentacion();

private:
    // INSERTAR ACA GENERADORES DE DOCUMENTOS
    GenerarEstancia* generadorEstancia;

    // Datos del juego:
    AtributosComunes* datos;
    ReglasNivel1* reglasNivel1;
    ReglasNivel2* reglasNivel2;
    ReglasNivel3* reglasNivel3;
    ReglasNivel4* reglasNivel4;
    ReglasNivel5* reglasNivel5;
    QRandomGenerator NumeroRandom;
    int NivelActual;
<<<<<<< HEAD
=======
    int DificultadJuego; // 1: Facil | 2: Normal | 3: Demonio

>>>>>>> main
    // Datos del Documento a generar:
    NPC* datosDeNPC;
    Documentacion* Doc2Generate;
<<<<<<< HEAD
=======

    // Seleccion de documentos que seran falsos
    bool DocsValidos[10];
    int MaxDocumentosInvalidos;
    void GenerarCantidadDocsInvalidos();

    // Cantidad de documentos invalidos en base a los niveles.
    void SetDificultadNivel();
    int MaxDocumentos;

    // Generadores por niveles
    void GenerarDocumentosNivel1(int &Index);
    void GenerarDocumentosNivel2(int &Index);
    void GenerarDocumentosNivel3(int &Index);
    void GenerarDocumentosNivel4(int &Index);
    void GenerarDocumentosNivel5(int &Index);
>>>>>>> main
};

#endif // GENERADORDOCUMENTACION_H
