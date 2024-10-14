#include "ui_npcgenericoui.h"
#include "npcgenericoui.h"
#include <ctime>

NPCGenericoUI::NPCGenericoUI(QWidget *parent)
    : NPCUI(parent)
    , ui(new Ui::NPCGenericoUI), Rechazo(parent)
{
    ui->setupUi(this);
    Rechazo.setSource(QUrl("qrc:/Resources/Sonidos/NPCRechazado.wav"));
    setSoundVolume(1.0);

    tiempoParpadeo = new QRandomGenerator(time(NULL));
    quejarse.setSingleShot(true);
    parpadeando = false;
    connect(&parpadeo, &QTimer::timeout, this, &NPCGenericoUI::Parpadear);
    connect(&quejarse, &QTimer::timeout, this, &NPCGenericoUI::emitQuejarse);

    ojosCerrados.load(":/Resources/NPCs/OjosCerrados.png");
    bocaCerrada.load(":/Resources/NPCs/BocaTriste.png");
    // Usamos esto en vez del metodo clear, porque este se bugea.
    nada.load(":/Resources/NPCs/Nada.png");

    LimpiarHojaCSS();

    ojosPos = ui->Ojos->pos();
    bocaPos = ui->Boca->pos();
    cejasPos = ui->Cejas->pos();
    narizPos = ui->Nariz->pos();
    peloPos = ui->Pelo->pos();
}

NPCGenericoUI::~NPCGenericoUI()
{
    delete ui;
    delete tiempoParpadeo;
}

void NPCGenericoUI::LimpiarHojaCSS()
{
    ui->Boca->setStyleSheet("");
    ui->Pelo->setStyleSheet("");
    ui->Cuerpo->setStyleSheet("");
    ui->Ojos->setStyleSheet("");
    ui->Cejas->setStyleSheet("");
    ui->Nariz->setStyleSheet("");
    ui->Gorro->setStyleSheet("");
}

void NPCGenericoUI::setNPC(NPC *newNPCenEscena)
{
    NPCrepresentado = newNPCenEscena;   // Necesario para los dialogos
    NPCenEscena = dynamic_cast<NPCcomun*>(newNPCenEscena);

    setSkinNPC(NPCenEscena->getSkin());
}

void NPCGenericoUI::setSkinNPC(Skin skinNPC)
{
    // Obtenemos las partes del cuerpo del npc
    ojos.load(skinNPC.getOjosURL());
    cuerpo.load(skinNPC.getCaraURL());
    boca.load(skinNPC.getBocaURL());
    cejas.load(skinNPC.getCejasURL());
    nariz.load(skinNPC.getNarizURL());
    pelo.load(skinNPC.getPelo());

    // Colocamos la textura de cada parte donde debe.
    ui->Gorro->hide();
    ui->Cuerpo->setPixmap(cuerpo);
    ui->Boca->setPixmap(boca);
    ui->Ojos->setPixmap(ojos);
    ui->Cejas->setPixmap(cejas);
    ui->Nariz->setPixmap(nariz);
    ui->Pelo->setPixmap(pelo);

    // Gorro
    if (skinNPC.getGorro() != ""){
        gorro.load(skinNPC.getGorro());
        ui->Gorro->setPixmap(gorro);
        ui->Gorro->show();
    }

    // Por ahora solo lo hago en el documento
    int X = width();
    if (X < 150)
        ReescalarNPC();

    // Mostramos el NPC
    show();
}

void NPCGenericoUI::Rechazado()
{
    parpadeo.stop();
    Rechazo.play();
    ui->Boca->setPixmap(bocaCerrada);
    ui->Ojos->setPixmap(ojosCerrados);
}

void NPCGenericoUI::Entrar()
{
    quejarse.start(60 * 1000);
    setearParpadear(false);
    NPCUI::Entrar();
}

void NPCGenericoUI::Salir(bool Aceptado)
{
    quejarse.stop();
    parpadeo.stop();

    if (!Aceptado)
        this->Rechazado();
    NPCUI::Salir(Aceptado);
}

void NPCGenericoUI::setSoundVolume(float vol)
{
    Rechazo.setVolume(vol-0.2);
}

void NPCGenericoUI::Finalizar()
{
    parpadeo.stop();
    quejarse.stop();

    NPCUI::Finalizar();
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
    ReescalarLabel(ui->Pelo, pelo, escalaFactorW, escalaFactorH);
    ReescalarLabel(ui->Gorro, gorro, escalaFactorW, escalaFactorH);
    if (parpadeando)
        ReescalarLabel(ui->Ojos, ojosCerrados, escalaFactorW, escalaFactorH);
    else
        ReescalarLabel(ui->Ojos, ojos, escalaFactorW, escalaFactorH);

    reposicionarLabels(escalaFactorW, escalaFactorH);
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
    reposLabel(peloPos, ui->Pelo, factorW, factorH, 0);
    reposLabel(peloPos, ui->Gorro, factorW, factorH, 0);
}

void NPCGenericoUI::reposLabel(QPoint pos, QLabel *label, double factorW, double factorH, int margen)
{
    QPoint nuevaPos(pos.x() * factorW, pos.y() * factorH - margen);
    label->move(nuevaPos);
}

void NPCGenericoUI::emitQuejarse()
{
    emit QuiereHablar("¿Cuánto más te vas a demorar?");
    quejarse.start(tiempoParpadeo->bounded(15000,75000));
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
}



