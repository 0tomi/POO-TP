#include "ui_npcgenericoui.h"
#include "npcgenericoui.h"
#include <ctime>

NPCGenericoUI::NPCGenericoUI(QWidget *parent)
    : NPCUI(parent)
    , ui(new Ui::NPCGenericoUI)
{
    ui->setupUi(this);
    setFixedSize(300,300);

    tiempoParpadeo = new QRandomGenerator(time(NULL));

    ojosCerrados.load(":/Resources/NPCs/OjosCerrados.png");
    bocaCerrada.load(":Resources/NPCs/BocaTriste.png");
}

NPCGenericoUI::~NPCGenericoUI()
{
    delete ui;
}

void NPCGenericoUI::setNPC(NPC *newNPCenEscena)
{
    setearParpadear(true);
    qDebug() << "Nuevo NPC";

    NPCenEscena = dynamic_cast<NPCcomun*>(newNPCenEscena);

    // Obtenemos las partes del cuerpo del npc
    ojos.load(NPCenEscena->getOjosURL());
    cuerpo.load(NPCenEscena->getCaraURL());
    boca.load(NPCenEscena->getBocaURL());
    cejas.load(NPCenEscena->getCejasURL());
    nariz.load(NPCenEscena->getNarizURL());

    // Colocamos la textura de cada parte donde debe.
    ui->Cuerpo->setPixmap(cuerpo);
    ui->Boca->setPixmap(boca);
    ui->Ojos->setPixmap(ojos);
    ui->Cejas->setPixmap(cejas);
    ui->Nariz->setPixmap(nariz);
}

void NPCGenericoUI::Rechazado()
{
    disconnect(&parpadeo, &QTimer::timeout, this, &NPCGenericoUI::Parpadear);
    parpadeo.stop();
    ui->Boca->setPixmap(bocaCerrada);
    ui->Ojos->setPixmap(ojosCerrados);
}

void NPCGenericoUI::Parpadear()
{
    if (parpadeando){
        ui->Ojos->setPixmap(ojos);
        parpadeo.start(tiempoParpadeo->bounded(1000,2000));
        parpadeando = false;
    } else {
        ui->Ojos->setPixmap(ojosCerrados);
        parpadeo.start(tiempoParpadeo->bounded(200,400));
        parpadeando = true;
    }
}

void NPCGenericoUI::setearParpadear(bool estado)
{
    // Desconectamos el parpadeo anterior para setear uno nuevo
    disconnect(&parpadeo, &QTimer::timeout, this, &NPCGenericoUI::Parpadear);
    parpadeo.stop();

    // Armamos denuevo parpadeo (Todo esto es para evitar bugs)
    parpadeo.start(1000);
    parpadeando = estado;
    connect(&parpadeo, &QTimer::timeout, this, &NPCGenericoUI::Parpadear);
}



