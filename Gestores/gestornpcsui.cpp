#include "gestornpcsui.h"
#include <QLayout>

GestorNPCsUI::GestorNPCsUI(){
    EntrarNPCsYDocs.setSingleShot(true);
}

GestorNPCsUI::~GestorNPCsUI()
{
    delete NPCcomunUI;
    delete Dialogos;
}

void GestorNPCsUI::setUp(QWidget* EscenarioDocumentos, QWidget *EscenarioNPCs, ColaNPC* cola)
{
    GestorDocumentos.setUp(1, EscenarioDocumentos);
    Escenario = EscenarioNPCs;
    ColaNPCs = cola;

    // Spawneamos NPC
    Dialogos = new GlobosDialogoUI(Escenario);
    NPCcomunUI = new NPCGenericoUI(Escenario);
    //Escenario->layout()->addWidget(NPCcomunUI);

    // ## A futuro iria aca el setup del NPC especial. ##


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

void GestorNPCsUI::EmpezarJuego()
{
    RealizarConeccionesDeNPCs();
}

void GestorNPCsUI::Centrar()
{
    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    int centerX = (Escenario->width() - NPCcomunUI->width()) /2;
    int centerY = (Escenario->height()) - (NPCcomunUI->height());
    // Centramos el NPC
    NPCcomunUI->move(centerX,centerY);
    // Centramos los dialogos
    Dialogos->Centrar(Escenario->width(), Escenario->height());
    // Centramos los documentos
    GestorDocumentos.Centrar();
}

void GestorNPCsUI::Entrar()
{
    qDebug() << "Tamanio de cola: " << ColaNPCs->getSize();
    NPCenEscena = ColaNPCs->getNPC();
    GestorDocumentos.setDocumento(NPCenEscena);

    if (ColaNPCs->getSize() == 0){
        // Desconectamos la animacion de entrar
        disconnect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::Entrar);
        emit UltimoNPC();
    }

    // ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ##
    qDebug() << NPCenEscena->getGenero();
    qDebug() << NPCenEscena->getTipo();
    qDebug() << NPCenEscena->getValidez();
    // ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ##

    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    NPCcomunUI->setNPC(NPCenEscena);

    // Hacemos que pasen los NPCs y sus documentos.
    EntrarNPCsYDocs.start(200);
    connect(&EntrarNPCsYDocs, &QTimer::timeout, this, &GestorNPCsUI::EntrarEntidades);
}

void GestorNPCsUI::Salir(bool boton)
{
    DetenerAnimacionesDocumentos();

    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    int SalidaEscena = Escenario->width() + NPCcomunUI->width();
    int centerY = (Escenario->height()) - (NPCcomunUI->height()) + 50;

    if (boton){
        GestorDocumentos.Aprobado();
    } else {
        GestorDocumentos.Rechazar();
        NPCcomunUI->Rechazado();
    }

    GestorDocumentos.Salir();
    Dialogos->ForzarSalir();
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
        Salir(true);
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

void GestorNPCsUI::Pausar()
{
    Dialogos->PausarMensaje();
}

void GestorNPCsUI::Reanudar()
{
    Dialogos->ReanudarMensaje();
}

void GestorNPCsUI::DetenerAnimacionesDocumentos()
{
    GestorDocumentos.DetenerAnimaciones();
}

void GestorNPCsUI::Dialogo(const QString &newDialogo)
{
    Dialogos->setMensaje(newDialogo, Escenario->width(), Escenario->height());
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

void GestorNPCsUI::CentrarNPC()
{
    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    int centerX = (Escenario->width() - NPCcomunUI->width()) /2;
    int centerY = (Escenario->height()) - (NPCcomunUI->height());
    NPCcomunUI->move(centerX,centerY);
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
    // Conectamos cuando el npc habla con el globo de dialogo.
    connect(NPCcomunUI, &NPCUI::QuiereHablar, this, &GestorNPCsUI::Dialogo);

    // Cuando aparezca o desaparezca el dialogo, el npc se centrara
    connect(Dialogos, &GlobosDialogoUI::Hablando, this, &GestorNPCsUI::CentrarNPC);
    connect(Dialogos, &GlobosDialogoUI::MensajeTerminado, this, &GestorNPCsUI::CentrarNPC);

    // Hago que al terminar la animacion de que un NPC se va, entre otro.
    connect(NPCcomunUI, &NPCUI::animacionEntrarTerminada, this, &GestorNPCsUI::ActualizarEstadoNPC);
    connect(NPCcomunUI, &NPCUI::animacionEntrarTerminada, this, &GestorNPCsUI::CentrarNPC);

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

void GestorNPCsUI::ActualizarEstadoNPC()
{
    MostrandoNPC = true;
}
