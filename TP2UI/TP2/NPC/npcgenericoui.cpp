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

    parpadeo = new QTimer;
}

NPCGenericoUI::~NPCGenericoUI()
{
    delete ui;
}

void NPCGenericoUI::setNPC(NPC *newNPCenEscena)
{
    parpadeo->start(1000);
    parpadeando = false;
    connect(parpadeo, &QTimer::timeout, this, &NPCGenericoUI::Parpadear);

    NPCenEscena = dynamic_cast<NPCcomun*>(newNPCenEscena);

    ojos = new QPixmap(NPCenEscena->getOjosURL());

    ui->Cuerpo->setPixmap(QPixmap(NPCenEscena->getCaraURL()));
    ui->Boca->setPixmap(QPixmap(NPCenEscena->getBocaURL()));
    ui->Ojos->setPixmap(*ojos);
    ui->Cejas->setPixmap(QPixmap(NPCenEscena->getCejasURL()));
    ui->Nariz->setPixmap(QPixmap(NPCenEscena->getNarizURL()));
}

void NPCGenericoUI::Rechazado()
{
    disconnect(parpadeo, &QTimer::timeout, this, &NPCGenericoUI::Parpadear);
    parpadeo->stop();
    ui->Boca->setPixmap(QPixmap(":Resources/NPCs/BocaTriste.png"));
    ui->Ojos->setPixmap(QPixmap(":/Resources/NPCs/OjosCerrados.png"));
}

void NPCGenericoUI::Parpadear()
{
    if (parpadeando){
        ui->Ojos->setPixmap(*ojos);
        parpadeo->start(tiempoParpadeo->bounded(1000,2000));
        parpadeando = false;
    } else {
        ui->Ojos->setPixmap(QPixmap(":/Resources/NPCs/OjosCerrados.png"));
        parpadeo->start(tiempoParpadeo->bounded(200,400));
        parpadeando = true;
    }
}



