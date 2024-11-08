#ifndef GENERADORDOCUMENTACION_H
#define GENERADORDOCUMENTACION_H

#include <QRandomGenerator>

#include "../Documentos/documentacion.h"

#include "../Reglas/reglasnivel1.h"
#include "../Reglas/reglasnivel2.h"
#include "../Reglas/reglasnivel3.h"
#include "../Reglas/reglasnivel4.h"
#include "../Reglas/reglasnivel5.h"

#include "../NPC/npc.h"
#include "generarestancia.h"
#include "generador_pasaporte.h"
#include "generadorlistaacompaniantes.h"
#include "locuracaracteres.h"
#include "generador_paisresidencia.h"
#include "generador_nuevaestancia.h"
#include "generador_radiografia.h"

using namespace std;

class GeneradorDocumentacion{
public:
    void setSeed(quint32 seed);
    GeneradorDocumentacion(); // en ultima instancia se le puede pasar la clase NPC pero no esta definida
    void Inicializar(int Nivel, int Dificultad, Reglas** rules, quint32 seed);
    void getDocumentos(NPC* info, bool validez);
    void setNivel(int Nivel);
    void setDificultad(int Dificultad);
    ~GeneradorDocumentacion();

private:
    quint32 semilla;
    void InicializarGeneradores(Reglas **rules, int nivel);

    // INSERTAR ACA GENERADORES DE DOCUMENTOS
    GenerarEstancia generadorEstancia;
    Generar_pasaporte generadorPasaporte;
    GeneradorListaAcompaniantes generadorListaAcomp;
    LocuraCaracteres randomizadorCaracteres;
    generador_paisresidencia generadorPaisResidencia;
    Generador_NuevaEstancia generadorNuevaEstancia;
    generador_Radiografia generadorRadiografia;
    // Datos del juego:
    ReglasNivel1* reglasNivel1;
    ReglasNivel2* reglasNivel2;
    ReglasNivel3* reglasNivel3;
    ReglasNivel4* reglasNivel4;
    ReglasNivel5* reglasNivel5;
    QRandomGenerator NumeroRandom;
    int NivelActual;

    int DificultadJuego; // 1: Facil | 2: Normal | 3: Demonio

    // Datos del Documento a generar:
    NPC* NPC2Generate;
    Documentacion* Doc2Generate;

    ListaAcompaniantes * listaAcompActual;
    Estancia* estanciaActual;
    Pasaporte* pasaporteActual;

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
