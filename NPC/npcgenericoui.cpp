#include "ui_npcgenericoui.h"
#include "npcgenericoui.h"
#include <ctime>

NPCGenericoUI::NPCGenericoUI(QWidget *parent)
    : NPCUI(parent)
    , ui(new Ui::NPCGenericoUI)
{
    ui->setupUi(this);
    //setFixedSize(300,300);

    tiempoParpadeo = new QRandomGenerator(time(NULL));

    ojosCerrados.load(":/Resources/NPCs/OjosCerrados.png");
    bocaCerrada.load(":/Resources/NPCs/BocaTriste.png");

    ojosPos = ui->Ojos->pos();
    bocaPos = ui->Boca->pos();
    cejasPos = ui->Cejas->pos();
    narizPos = ui->Nariz->pos();
}

NPCGenericoUI::~NPCGenericoUI()
{
    delete ui;
}

void NPCGenericoUI::setNPC(NPC *newNPCenEscena)
{
    NPCrepresentado = newNPCenEscena;   // Necesario para los dialogos
    NPCenEscena = dynamic_cast<NPCcomun*>(newNPCenEscena);

    // Obtenemos las partes del cuerpo del npc
    ojos.load(NPCenEscena->getSkin().getOjosURL());
    cuerpo.load(NPCenEscena->getSkin().getCaraURL());
    boca.load(NPCenEscena->getSkin().getBocaURL());
    cejas.load(NPCenEscena->getSkin().getCejasURL());
    nariz.load(NPCenEscena->getSkin().getNarizURL());

    //QPixmap cuerpoRescalado = cuerpo.scaled(padre->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Colocamos la textura de cada parte donde debe.
    ui->Cuerpo->setPixmap(cuerpo);
    ui->Boca->setPixmap(boca);
    ui->Ojos->setPixmap(ojos);
    ui->Cejas->setPixmap(cejas);
    ui->Nariz->setPixmap(nariz);

    // Por ahora solo lo hago en el documento
    int X = width();
    if (X < 150)
        ReescalarNPC();
}

void NPCGenericoUI::Rechazado()
{
    disconnect(&parpadeo, &QTimer::timeout, this, &NPCGenericoUI::Parpadear);
    parpadeo.stop();
    ui->Boca->setPixmap(bocaCerrada);
    ui->Ojos->setPixmap(ojosCerrados);
}

void NPCGenericoUI::Entrar()
{
    setearParpadear(false);
    NPCUI::Entrar();
}

void NPCGenericoUI::Sacar()
{
    // Desconectamos el parpadeo anterior para setear uno nuevo
    disconnect(&parpadeo, &QTimer::timeout, this, &NPCGenericoUI::Parpadear);
    parpadeo.stop();

    NPCUI::Sacar();
}


void NPCGenericoUI::ReescalarNPC()
{
    QSize nuevoSize = size();
    QSize escalaOriginal = cuerpo.size();

    QPixmap cuerpoEscalado = cuerpo.scaled(nuevoSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    double escalaFactorW = static_cast<double>(cuerpoEscalado.width()) / escalaOriginal.width();
    double escalaFactorH = static_cast<double>(cuerpoEscalado.height()) / escalaOriginal.height();

    ui->Cuerpo->setPixmap(cuerpoEscalado);
    ui->Cuerpo->resize(cuerpoEscalado.size());

    ReescalarLabel(ui->Boca, boca, escalaFactorW, escalaFactorH);
    ReescalarLabel(ui->Cejas, cejas, escalaFactorW, escalaFactorH);
    ReescalarLabel(ui->Nariz, nariz, escalaFactorW, escalaFactorH);
    if (parpadeando)
        ReescalarLabel(ui->Ojos, ojosCerrados, escalaFactorW, escalaFactorH);
    else
        ReescalarLabel(ui->Ojos, ojos, escalaFactorW, escalaFactorH);

    reposicionarLabels(escalaFactorW, escalaFactorH);
    qDebug() << nuevoSize;
}

void NPCGenericoUI::ReescalarLabel(QLabel *Label, QPixmap &ImagenLabel, double factorW, double factorH)
{
    QSize nuevoTamanio(ImagenLabel.size().width() * factorW, ImagenLabel.size().height() * factorH);
    QPixmap imagenEscalada = ImagenLabel.scaled(nuevoTamanio, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Label->setPixmap(imagenEscalada);
    Label->resize(imagenEscalada.size());
}

void NPCGenericoUI::reposicionarLabels(double factorW, double factorH)
{
    reposLabel(ojosPos, ui->Ojos, factorW, factorH, 3);
    reposLabel(bocaPos, ui->Boca, factorW, factorH, 5);
    reposLabel(narizPos, ui->Nariz, factorW, factorH, 5);
    reposLabel(cejasPos, ui->Cejas, factorW, factorH, 5);
}

void NPCGenericoUI::reposLabel(QPoint pos, QLabel *label, double factorW, double factorH, int margen)
{
    QPoint nuevaPos(pos.x() * factorW, pos.y() * factorH - margen);
    label->move(nuevaPos);
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
    // Armamos denuevo parpadeo (Todo esto es para evitar bugs)
    parpadeo.start(1000);
    parpadeando = estado;
    connect(&parpadeo, &QTimer::timeout, this, &NPCGenericoUI::Parpadear);
}



