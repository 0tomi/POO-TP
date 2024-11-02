#include "pantallafinalnivel.h"
#include "ui_pantallafinalnivel.h"
#include "../lectorarchivos.h"

#include <QDebug>
#include <QFile>
#include <QTime>

PantallaFinalNivel::PantallaFinalNivel(GuardarPartidas* sg, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaFinalNivel)
    , Random(QTime::currentTime().msec()), sonidoBotones(parent), musica(parent)
{
    ui->setupUi(this);

    sonidoBotones.setSource(QUrl("qrc:/Resources/Sonidos/BotonesMenu.WAV"));
    musica.setSource(QUrl(""));
    setMusicVolume(1.0);
    setSoundVolume(1.0);

    saveGame = sg;
    // conecc.signal de salirBtn:
    connect(ui->salirBtn, &QPushButton::clicked, this, &PantallaFinalNivel::onSalirClicked);
    // connec. signal de sigNivelBtn:
    connect(ui->sigNivelBtn, &QPushButton::clicked, this, &PantallaFinalNivel::onSigNivelClicked);
    // Conectamos boton de reintentar
    connect(ui->reintentarBtn, &QPushButton::clicked, this, &PantallaFinalNivel::onReintentarClicked);

    LectorArchivos lector(":/Resources/ArchivosTexto/tips.txt");
    this->tips = lector.getVector();
    
}

PantallaFinalNivel::~PantallaFinalNivel()
{
    delete ui;
}

vector<QString> PantallaFinalNivel::getTips() {
    return this->tips;
}

void PantallaFinalNivel::setSoundVolume(float vol)
{
    this->sonidoBotones.setVolume(vol-0.2);
}

void PantallaFinalNivel::setMusicVolume(float vol)
{
    this->musica.setVolume(vol-0.2);
}

void PantallaFinalNivel::setPantallaFinalUI(Juego* juegoInfo, bool perdio) {
    this->Perdio = perdio;
    PlayerStats actualStats = juegoInfo->getDatosJugador();

    int cantCredsSocsObtDia = juegoInfo->getSocialCreditsEarnedInLevel();
    int maxMultas = juegoInfo->getMaxMultas();

    NivelActual = juegoInfo->getNivelActual();
    Dificultad =  juegoInfo->getDificultad();

    // Seteamos las labels de color blanco
    ui->cantMultasObt_label->setStyleSheet(COLOR_BLANCO);
    ui->credsSocsObtDia_label->setStyleSheet(COLOR_BLANCO);
    ui->credsSocsTot_label->setStyleSheet(COLOR_BLANCO);

    // Coloco los botones y etiquetas dependiendo de si perdio o gano
    if (perdio) {
        ui->TIPLabel->show();
        saveGame->cleanCurrentSlot();
        ui->stackedTitulos->setCurrentIndex(1);
        ui->stackedBotones->setCurrentIndex(1);
        
        QString tipRandom = this->tips[Random.bounded(this->tips.size())];
        qDebug() << "Tipo seleccionado: " << tipRandom;
        ui->tipsLabel->setText(tipRandom);
        
    } else {
        actualStats.Nivel++;
        ui->TIPLabel->hide();
        saveGame->saveCurrentSlot(actualStats);
        ui->stackedTitulos->setCurrentIndex(0);
        ui->stackedBotones->setCurrentIndex(0);
    }

    ui->erroresCometidos_cont->setText(QString::number(actualStats.CantidadErrores));
    ui->cantPersAcept_label->setText(QString::number(actualStats.CantidadNPCsAceptados));
    ui->cantPersRech_label->setText(QString::number(actualStats.CantidadNPCsRechazados));
    ui->cantMultasObt_label->setText(QString::number(actualStats.Multas));

    if (actualStats.Multas == maxMultas) {
        ui->cantMultasObt_label->setStyleSheet(COLOR_ROJO);
    }
    ui->credsSocsObtDia_label->setText(QString::number(cantCredsSocsObtDia));
    if (cantCredsSocsObtDia < 0) {
        ui->credsSocsObtDia_label->setStyleSheet(COLOR_ROJO);
    }
    ui->credsSocsTot_label->setText(QString::number(actualStats.TotalSocialCredits));
    if (cantCredsSocsObtDia < 0) {
        ui->credsSocsTot_label->setStyleSheet(COLOR_ROJO);
    }
}

// Signals
void PantallaFinalNivel::onSalirClicked() {
    sonidoBotones.play();
    emit EnviarLogs("Boton de Salir Presionado");
    emit salirClicked();
}

void PantallaFinalNivel::onSigNivelClicked() {
    sonidoBotones.play();
    emit EnviarLogs("Boton Siguiente Nivel Presionado");
    NivelActual++;
    emit sigNivelClicked(NivelActual, Dificultad);
}

void PantallaFinalNivel::onReintentarClicked()
{
    sonidoBotones.play();
    emit EnviarLogs("Boton Reintentar Presionado");
    emit reintentarClicked(1, Dificultad);
}
