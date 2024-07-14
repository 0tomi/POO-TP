#include "gestornpcsui.h"
#include <QLayout>

GestorNPCsUI::GestorNPCsUI(){
    EntrarNPCsYDocs.setSingleShot(true);
}

void GestorNPCsUI::setUp(QWidget* EscenarioDocumentos, QWidget *EscenarioNPCs, ColaNPC* cola)
{
    GestorDocumentos.setUp(1, EscenarioDocumentos);
    Escenario = EscenarioNPCs;
    ColaNPCs = cola;

    // Spawneamos NPC
    NPCcomunUI = new NPCGenericoUI(Escenario);
    Escenario->layout()->addWidget(NPCcomunUI);

    // ## A futuro iria aca el setup del NPC especial. ##

    RealizarConeccionesDeNPCs();
    // Colocamos al NPC fuera del escenario para iniciar la cinematica.
    NPCcomunUI->hide();
    NPCcomunUI->move(-(NPCcomunUI->width()),0);
    MostrandoNPC = false;
}

void GestorNPCsUI::setUpNuevoNivel(int Nivel)
{
    RealizarConeccionesDeNPCs();
    GestorDocumentos.nextNivel(Nivel);
}

void GestorNPCsUI::Centrar()
{
    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    int centerX = (Escenario->width() - NPCcomunUI->width()) /2;
    int centerY = (Escenario->height()) - (NPCcomunUI->height());
    NPCcomunUI->move(centerX,centerY);

    GestorDocumentos.Centrar();
}

void GestorNPCsUI::Entrar()
{
    NPCenEscena = ColaNPCs->getNPC();
    GestorDocumentos.setDocumento(NPCenEscena);

    if (ColaNPCs->getSize() == 0){
        // Desconectamos la animacion de entrar
        disconnect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::Entrar);
        emit UltimoNPC();
    }

    // ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ##
    qDebug() << "Tamanio de cola: " << ColaNPCs->getSize();
    qDebug() << NPCenEscena->getGenero();
    qDebug() << NPCenEscena->getTipo();
    qDebug() << NPCenEscena->getValidez();
    // ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ##

    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    NPCcomunUI->setNPC(NPCenEscena);

    // Hacemos que pasen los NPCs y sus documentos.
    EntrarNPCsYDocs.start(200);
    connect(&EntrarNPCsYDocs, &QTimer::timeout, this, &GestorNPCsUI::EntrarEntidades);
    //GestorDocumentos.Entrar();
    //NPCcomunUI->Entrar(centerX, centerY);

    MostrandoNPC = true;
}

void GestorNPCsUI::Salir()
{
    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    int SalidaEscena = Escenario->width() + NPCcomunUI->width();
    int centerY = (Escenario->height()) - (NPCcomunUI->height()) + 50;

    GestorDocumentos.Salir();
    NPCcomunUI->Sacar(SalidaEscena, centerY);

    if (ColaNPCs->getSize() == 0)
        emit ColaTerminada();
        //connect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::emitColaTerminada);
    MostrandoNPC = false;
}

void GestorNPCsUI::TerminoNivel()
{
    RealizarDesconeccionesNPC();

    if (ColaNPCs->getSize()){
        Salir();
        ColaNPCs->vaciarCola();
    }
    emit ColaTerminada();
}

bool GestorNPCsUI::MostrandoElNPC() const
{
    return MostrandoNPC;
}

int GestorNPCsUI::NPCsRestantes()
{
    int Restantes = ColaNPCs->getSize();
    return Restantes;
}

bool GestorNPCsUI::getValidez()
{
    return NPCenEscena->getValidez();
}

int GestorNPCsUI::getTipo()
{
    return NPCenEscena->getTipo();
}

void GestorNPCsUI::DetenerAnimacionesDocumentos()
{
    GestorDocumentos.DetenerAnimaciones();
}

void GestorNPCsUI::Rechazado()
{
    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    NPCcomunUI->Rechazado();
}

void GestorNPCsUI::emitirNPCTerminoSalir()
{
    emit NPCTerminoSalir();
}

void GestorNPCsUI::emitColaTerminada()
{
    emit ColaTerminada();
}

void GestorNPCsUI::CentrarDocumentos()
{
    GestorDocumentos.Centrar();
}

void GestorNPCsUI::EntrarEntidades()
{
    disconnect(&EntrarNPCsYDocs, &QTimer::timeout, this, &GestorNPCsUI::EntrarEntidades);
    int centerX = (Escenario->width() - NPCcomunUI->width()) / 2;
    int centerY = Escenario->height() - NPCcomunUI->height();
    GestorDocumentos.Entrar();
    NPCcomunUI->Entrar(centerX, centerY);
}

void GestorNPCsUI::RealizarConeccionesDeNPCs()
{
    // Hago que al terminar la animacion de que un NPC se va, entre otro.
    connect(NPCcomunUI, &NPCUI::animacionEntrarTerminada, this, &GestorNPCsUI::Centrar);

    // Hago que al terminar la animacion de que un NPC se va, entre otro.
    connect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::emitirNPCTerminoSalir);
    connect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::Entrar);

    // Aca irian las conecciones del NPC especial
}

void GestorNPCsUI::RealizarDesconeccionesNPC()
{
    // Desconectamos la animacion de centrar
    disconnect(NPCcomunUI, &NPCUI::animacionEntrarTerminada, this, &GestorNPCsUI::Centrar);

    disconnect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::emitColaTerminada);
    disconnect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::Entrar);

    // Aca irian las conecciones del NPC especial
}
