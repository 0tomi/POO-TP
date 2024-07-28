#include "gestornpcsui.h"
#include <QLayout>

/// #################################### CONSTRUCTOR ###################################################
GestorNPCsUI::GestorNPCsUI(){

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

    RealizarConexionesDeNPCs();
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
    // Cuando sale un npc entra otro.
    connect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::Entrar);
    NPCConectado = true;
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

    // Avisamos que termina de salir un NPC
    connect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::emitirNPCTerminoSalir);

    // Cuando entregamos el documento, sale el npc.
    connect(docsIconUI, &DocsIconUI::animacionSalirTerminada, this, &GestorNPCsUI::SalirEntidades);

    // Aca irian las conecciones del NPC especial
}

void GestorNPCsUI::DesconectarNPCs()
{
    if (NPCConectado)
        disconnect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::Entrar);
    NPCConectado = false;
}

/// #################################### Entrar entidades ###################################################
void GestorNPCsUI::Entrar()
{
    qDebug() << "Tamanio de cola: " << ColaNPCs->getSize();

    NPCenEscena = ColaNPCs->getNPC();
    GestorDocumentos.setDocumento(NPCenEscena);

    if (ColaNPCs->getSize() == 0){
        // Desconectamos la animacion de entrar
        DesconectarNPCs();
        emit UltimoNPC();
    }

    // ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ##
    qDebug() << NPCenEscena->getGenero();
    qDebug() << NPCenEscena->getTipo();
    qDebug() << NPCenEscena->getValidez();
    // ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ## ## DEBUG ##

    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    NPCcomunUI->setNPC(NPCenEscena);

    // Hacemos que pasen los NPC.
    NPCcomunUI->Entrar();
}

void GestorNPCsUI::ActualizarEstadoNPC()
{
    MostrandoNPC = true;
    Centrar();
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
        Rechazado = false;
    } else {
        GestorDocumentos.Rechazar();
        Rechazado = true;
    }

    docsIconUI->BloquearDocumento();
}

void GestorNPCsUI::DetenerAnimacionesDocumentos()
{
    GestorDocumentos.DetenerAnimaciones();
}

void GestorNPCsUI::SalirEntidades()
{
    if (Rechazado)
        NPCcomunUI->Rechazado();

    Dialogos->ForzarSalir();
    NPCcomunUI->Sacar();

    MostrandoNPC = false;

    if (ColaNPCs->getSize() == 0)
        emit ColaTerminada();
}

/// #################################### Terminar nivel ###################################################
void GestorNPCsUI::TerminoNivel()
{
    DesconectarNPCs();
    // Si hay NPCs presentes, retiramos los documentos y el NPC.
    if (MostrandoNPC || ColaNPCs->getSize()){
        SalirEntidades();
        GestorDocumentos.Salir();
        docsIconUI->Sacar();

        ColaNPCs->vaciarCola();
    }
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
