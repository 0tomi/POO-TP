#ifndef GENERADORDOCUMENTACION_H
#define GENERADORDOCUMENTACION_H

#include "../AtributosComunes/atributoscomunes.h"
#include "../Documentos/documentacion.h"
#include "../Reglas/reglasnivel5.h"
#include "../NPC/npc.h"

#include <QRandomGenerator>

using namespace std;

class GeneradorDocumentacion{
public:
    GeneradorDocumentacion(AtributosComunes* datos, Reglas** rules); // en ultima instancia se le puede pasar la clase NPC pero no esta definida
    void getDocumentos(NPC* info, bool validez);
    void actualizarReglas(Reglas** rules, int Nivel);
    void nextNivel(int Nivel);

private:
    // INSERTAR ACA GENERADORES DE DOCUMENTOS


    // Datos del juego:
    AtributosComunes* datos;
    Reglas* rules[5];
    QRandomGenerator NumeroRandom;
    int NivelActual;

    // Datos del Documento a generar:
    NPC* NPC2Generate;
    Documentacion* Doc2Generate;

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
};

#endif // GENERADORDOCUMENTACION_H
