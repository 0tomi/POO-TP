#include "pantallafinalnivel.h"
#include "ui_pantallafinalnivel.h"

#include <QDebug>
#include <QFile>
#include <QTime>

PantallaFinalNivel::PantallaFinalNivel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaFinalNivel)
    , Random(QTime::currentTime().msec())
{
    ui->setupUi(this);
    // conecc.signal de salirBtn:
    connect(ui->salirBtn, &QPushButton::clicked, this, &PantallaFinalNivel::onSalirClicked);
    // connec. signal de sigNivelBtn:
    connect(ui->sigNivelBtn, &QPushButton::clicked, this, &PantallaFinalNivel::onSigNivelClicked);
    // Conectamos boton de reintentar
    connect(ui->reintentarBtn, &QPushButton::clicked, this, &PantallaFinalNivel::onReintentarClicked);
    
}

PantallaFinalNivel::~PantallaFinalNivel()
{
    delete ui;
}

vector<QString> PantallaFinalNivel::getTips() {
    return this->tips;
}

void PantallaFinalNivel::setTips(vector<QString> tipsNew) {
    tips.resize(tipsNew.size());
    for (int q = 0; q < tipsNew.size(); q++) {
        this->tips[q] = tipsNew[q];
    }
}

void leerArch(PantallaFinalNivel* pf) {
    QFile archivo(":/Resources/ArchivosTexto/tips.txt");
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error al abrir archivo tips";
        return;
    }
    
    qDebug() << "Pudo leer el arch tips";
    
    vector<QString> tips = pf->getTips();
    
    while (!archivo.atEnd()) {
        QByteArray linea = archivo.readLine();
        QString tip = QString::fromUtf8(linea).trimmed();
        if (!tip.isEmpty()) {
            tips.push_back(tip);
        }
    }
    archivo.close();
    
    pf->setTips(tips);
    
    for (int i = 0; i < tips.size(); i++) {
        qDebug() << "tip: " << tips[i];
    }
}

void PantallaFinalNivel::setPantallaFinalUI(Juego* juegoInfo, bool perdio) {
    this->Perdio = perdio;
    int cantNpcsAcept = juegoInfo->getCantidadNPCsAceptados();
    int cantNpcsRech = juegoInfo->getCantidadNPCsRechazados();
    int cantMultasObt = juegoInfo->getMultas();
    int maxMultas = juegoInfo->getMaxMultas();
    int cantCredsSocsObtDia = juegoInfo->getSocialCreditsEarnedInLevel();
    int cantCredsSocsTot = juegoInfo->getTotalSocialCredits();

    NivelActual = juegoInfo->getNivelActual();
    Dificultad =  juegoInfo->getDificultad();

    // Seteamos las labels de color blanco
    ui->cantMultasObt_label->setStyleSheet(COLOR_BLANCO);
    ui->credsSocsObtDia_label->setStyleSheet(COLOR_BLANCO);
    ui->credsSocsTot_label->setStyleSheet(COLOR_BLANCO);

    // Coloco los botones y etiquetas dependiendo de si perdio o gano
    if (perdio) {
        ui->stackedTitulos->setCurrentIndex(1);
        ui->stackedBotones->setCurrentIndex(1);
        
        // MOSTRAR TIPS:
        leerArch(this);
        for (int q = 0; q < this->tips.size(); q++) {
            qDebug() << "tip de la clase: " << this->tips[q];
        }
        
        QString tipRandom = this->tips[Random.bounded(this->tips.size())];
        ui->tipsLabel->setText(tipRandom);
        
    } else {
        ui->stackedTitulos->setCurrentIndex(0);
        ui->stackedBotones->setCurrentIndex(0);
    }

    ui->cantPersAcept_label->setText(QString::number(cantNpcsAcept));
    ui->cantPersRech_label->setText(QString::number(cantNpcsRech));
    ui->cantMultasObt_label->setText(QString::number(cantMultasObt));

    if (cantMultasObt == maxMultas) {
        ui->cantMultasObt_label->setStyleSheet(COLOR_ROJO);
    }
    ui->credsSocsObtDia_label->setText(QString::number(cantCredsSocsObtDia));
    if (cantCredsSocsObtDia < 0) {
        ui->credsSocsObtDia_label->setStyleSheet(COLOR_ROJO);
    }
    ui->credsSocsTot_label->setText(QString::number(cantCredsSocsTot));
    if (cantCredsSocsObtDia < 0) {
        ui->credsSocsTot_label->setStyleSheet(COLOR_ROJO);
    }
}

// Signals
void PantallaFinalNivel::onSalirClicked() {
    if (!Perdio)
        guardarPartida();
    emit salirClicked();
}

void PantallaFinalNivel::onSigNivelClicked() {
    NivelActual++;
    emit sigNivelClicked(NivelActual, Dificultad);
}

void PantallaFinalNivel::onReintentarClicked()
{
    emit reintentarClicked(1, Dificultad);
}

// metodos extra
void PantallaFinalNivel::guardarPartida() {
    qDebug() << "partida guardada";
}
