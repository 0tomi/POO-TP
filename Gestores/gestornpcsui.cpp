#include "gestornpcsui.h"
#include <QLayout>

/// #################################### CONSTRUCTOR ###################################################
GestorNPCsUI::GestorNPCsUI(){
    EntrarNPCsYDocs.setSingleShot(true);
}

GestorNPCsUI::~GestorNPCsUI()
{
    delete NPCcomunUI;
    delete Dialogos;
}
/// #################################### SetUps ###################################################
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

void GestorNPCsUI::setUpDocsIcono(QWidget *escena)
{
    // Spawneamos el documento
    docsIconUI = new DocsIconUI(escena);

    // Establecemos un layout para que el documento se centre y tenga resize.
    QHBoxLayout * layout = new QHBoxLayout(escena);
    layout->addWidget(docsIconUI);
    escena->setLayout(layout);

    // Hacemos que los documentos entren en escena solo cuando se clickea el documento.
    connect(NPCcomunUI, &NPCGenericoUI::animacionEntrarTerminada, docsIconUI, &DocsIconUI::Entrar);
    connect(docsIconUI, &DocsIconUI::Abierto, &GestorDocumentos, &GestorDocumentosUI::Entrar);
    connect(docsIconUI, &DocsIconUI::Cerrado, &GestorDocumentos, &GestorDocumentosUI::Salir);
}

DocsIconUI * GestorNPCsUI::getDocsIcono()
{
    return docsIconUI;
}

void GestorNPCsUI::setUpNuevoNivel(int Nivel)
{
    GestorDocumentos.setUpNivel(Nivel);
}

/// #################################### Empezar ###################################################
void GestorNPCsUI::EmpezarJuego()
{
    RealizarConexionesDeNPCs();
}

/// #################################### Entrar entidades ###################################################
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

void GestorNPCsUI::EntrarEntidades()
{
    disconnect(&EntrarNPCsYDocs, &QTimer::timeout, this, &GestorNPCsUI::EntrarEntidades);
    NPCcomunUI->Entrar();
}

void GestorNPCsUI::ActualizarEstadoNPC()
{
    MostrandoNPC = true;
}

/// #################################### Centrar ###################################################
void GestorNPCsUI::CentrarDocumentos()
{
    GestorDocumentos.Centrar();
}

void GestorNPCsUI::CentrarNPC()
{
    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    NPCcomunUI->Centrar();
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

/// #################################### Salir entidades ###################################################
void GestorNPCsUI::Salir(bool boton)
{
    DetenerAnimacionesDocumentos();

    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.

    if (boton){
        GestorDocumentos.Aprobado();
    } else {
        GestorDocumentos.Rechazar();
        NPCcomunUI->Rechazado();
    }

    docsIconUI->Sacar();
    docsIconUI->BloquearDocumento();
    Dialogos->ForzarSalir();
    NPCcomunUI->Sacar();

    if (ColaNPCs->getSize() == 0)
        emit ColaTerminada();
        //connect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::emitColaTerminada);
    MostrandoNPC = false;
}
void GestorNPCsUI::DetenerAnimacionesDocumentos()
{
    GestorDocumentos.DetenerAnimaciones();
}

/// #################################### Terminar nivel ###################################################
void GestorNPCsUI::TerminoNivel()
{
    RealizarDesconexionesNPC();

    if (ColaNPCs->getSize()){
        Salir(true);
        ColaNPCs->vaciarCola();
    }
    emit ColaTerminada();
}

/// #################################### Dialogos ###################################################
void GestorNPCsUI::Dialogo(const QString &newDialogo)
{
    Dialogos->setMensaje(newDialogo, Escenario->width(), Escenario->height());
}

void GestorNPCsUI::Pausar()
{
    Dialogos->PausarMensaje();
}
void GestorNPCsUI::Reanudar()
{
    Dialogos->ReanudarMensaje();
}
/// #################################### Señales ###################################################
void GestorNPCsUI::emitirNPCTerminoSalir()
{
    emit NPCTerminoSalir();
}

void GestorNPCsUI::emitColaTerminada()
{
    emit ColaTerminada();
}

/// #################################### Conexiones ###################################################
void GestorNPCsUI::RealizarConexionesDeNPCs()
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

void GestorNPCsUI::RealizarDesconexionesNPC()
{
    // Desconectamos la animacion de centrar
    disconnect(NPCcomunUI, &NPCUI::animacionEntrarTerminada, this, &GestorNPCsUI::Centrar);

    disconnect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::emitColaTerminada);
    disconnect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::Entrar);

    // Aca irian las conecciones del NPC especial
}


/// #################################### Getters ###################################################
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
