#include "gestornpcsui.h"
#include <QLayout>

/// #################################### CONSTRUCTOR ###################################################
GestorNPCsUI::GestorNPCsUI(){

}

GestorNPCsUI::~GestorNPCsUI()
{
    delete NPCcomunUI;
    delete Dialogos;
    delete transcriptorDialogos;
}
/// #################################### SetUps ###################################################
void GestorNPCsUI::setUp(QWidget * EscenarioTranscriptor, QWidget *EscenarioNPCs, ColaNPC* cola)
{
    Escenario = EscenarioNPCs;
    ColaNPCs = cola;
    ColaVacia = true;

    // Spawneamos NPC
    Dialogos = new GlobosDialogoUI(Escenario);
    NPCcomunUI = new NPCGenericoUI(Escenario);
    //Escenario->layout()->addWidget(NPCcomunUI);

    // Spawneamos el transcriptor
    transcriptorDialogos = new TranscriptorDialogos(EscenarioTranscriptor);
    connect(Dialogos, &GlobosDialogoUI::Hablando, transcriptorDialogos, &TranscriptorDialogos::CaptarMensaje);
    connect(NPCcomunUI, &NPCGenericoUI::animacionSalirTerminada, transcriptorDialogos, &TranscriptorDialogos::LimpiarDialogo);

    // ## A futuro iria aca el setup del NPC especial. ##


    // Colocamos al NPC fuera del escenario para iniciar la cinematica.
    NPCcomunUI->hide();
    NPCcomunUI->move(-(NPCcomunUI->width()),0);
    MostrandoNPC = false;

    RealizarConexionesDeNPCs();
}

void GestorNPCsUI::setUpTranscriptor(QPushButton *boton)
{
    connect(boton, &QPushButton::clicked, transcriptorDialogos, &TranscriptorDialogos::MostrarOcultar);
}

/// #################################### Empezar ###################################################
void GestorNPCsUI::EmpezarJuego()
{
    // Cuando sale un npc entra otro.
    Dialogos->InterrumpirMensaje(false);
    connect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::Entrar);
    NPCConectado = true;
    ColaVacia = false;
}

/// #################################### Conexiones ###################################################
void GestorNPCsUI::RealizarConexionesDeNPCs()
{
    // Conectamos cuando el npc habla con el globo de dialogo.
    connect(NPCcomunUI, &NPCUI::QuiereHablar, Dialogos, &GlobosDialogoUI::setMensaje);

    // Hago que al terminar la animacion de que un NPC se va, entre otro.
    connect(NPCcomunUI, &NPCUI::animacionEntrarTerminada, this, &GestorNPCsUI::ActualizarEstadoNPC);

    // Avisamos que termina de salir un NPC
    connect(NPCcomunUI, &NPCUI::animacionSalirTerminada, this, &GestorNPCsUI::emitirNPCTerminoSalir);

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
    qDebug() << "Cantidad de npcs falsos: " << ColaNPCs->getCantidadNPCsFalsos();

    NPCenEscena = ColaNPCs->getNPC();
    emit setDocsInfo(NPCenEscena);

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

NPC *GestorNPCsUI::getNPC()
{
    return NPCenEscena;
}

void GestorNPCsUI::ActualizarEstadoNPC()
{
    MostrandoNPC = true;
    emit NPCTerminoEntrar();
}

/// #################################### Salir entidades ###################################################
void GestorNPCsUI::Salir(bool boton)
{
    // ### Aca iria un IF para checkear si el NPC es de tipo especial o comun, y decidir cual setear.
    if (boton){
        Rechazado = false;
    } else {
        Rechazado = true;
    }
}

void GestorNPCsUI::SalirEntidades()
{
    NPCcomunUI->Salir(!this->Rechazado);
    Dialogos->ForzarSalir();

    MostrandoNPC = false;

    if (ColaNPCs->getSize() == 0)
        ColaVacia = true;
}

/// #################################### Terminar nivel ###################################################
void GestorNPCsUI::TerminoNivel()
{
    Dialogos->ForzarSalir();
    Dialogos->InterrumpirMensaje(true);
    DesconectarNPCs();
    if (transcriptorDialogos->getMostrando())
        transcriptorDialogos->Sacar();
    transcriptorDialogos->hide();

    // Si hay NPCs presentes, retiramos los documentos y el NPC.
    if (MostrandoNPC || ColaNPCs->getSize()){
        SalirEntidades();

        ColaNPCs->vaciarCola();
    }
}

/// #################################### Dialogos ###################################################
void GestorNPCsUI::Pausar()
{
    Dialogos->PausarMensaje();
    NPCcomunUI->Pausar(true);
}
void GestorNPCsUI::Reanudar()
{
    Dialogos->ReanudarMensaje();
    NPCcomunUI->Pausar(false);
}
/// #################################### Señales ###################################################
void GestorNPCsUI::emitirNPCTerminoSalir()
{
    emit NPCTerminoSalir();
    if (ColaVacia)
        emit ColaTerminada();
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

QString GestorNPCsUI::getDatosFalsos()
{
    return NPCenEscena->getDatosFalsos();
}

void GestorNPCsUI::Centrar()
{
    Dialogos->Centrar();
    NPCcomunUI->Centrar();
}

void GestorNPCsUI::setVolumen(float vol)
{
    NPCcomunUI->setSoundVolume(vol);
    Dialogos->setVolume(vol);
    transcriptorDialogos->setVolume(vol);
}
