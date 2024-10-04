#include "nuevaestanciaui.h"
#include "ui_nuevaestanciaui.h"

NuevaEstanciaUI::NuevaEstanciaUI(QWidget *parent)
    : DocumentosUI(parent)
    , ui(new Ui::NuevaEstanciaUI), Sonidos{QSoundEffect(this), QSoundEffect(this), QSoundEffect(this)}
{
    ui->setupUi(this);
    Sonidos[0].setSource(QUrl("qrc:/Resources/Sonidos/Libro/AbrirLibro.wav"));
    Sonidos[1].setSource(QUrl("qrc:/Resources/Sonidos/Libro/CerrarLibro.wav"));
    Sonidos[2].setSource(QUrl("qrc:/Resources/Sonidos/Libro/PasarPagina.WAV"));
    setVolume(1.0);
    setUpBotones();
    resetearApariencia();
}

void NuevaEstanciaUI::setVolume(float vol)
{
    Sonidos[0].setVolume(vol-0.2);
    Sonidos[1].setVolume(vol-0.2);
    Sonidos[2].setVolume(vol-0.2);
}

void NuevaEstanciaUI::setDocumentacionInfo(Documentacion *documento)
{
    NuevaEstancia * InfoDoc = dynamic_cast<NuevaEstancia*> (documento);
    if (!InfoDoc) {
        qDebug() << "Fallo al castear puntero de Nueva Estancia";
        return;
    }

    setUpPaginaEstancia(dynamic_cast<Estancia*>(InfoDoc->getEstancia()));
    setUpPagina(InfoDoc->getPaisesPaso(), ui->DescPaisPaso);
    setUpPagina(InfoDoc->getBienesTransp(), ui->DescBienes);
    setUpPagina(InfoDoc->getOcupacion(), ui->DescOcupacion);

    resetearApariencia();
}

void NuevaEstanciaUI::setUpPaginaEstancia(Estancia *info)
{
    if (!info) {
        qDebug() << "Fallo al castear puntero de Estancia (Proveniente de NuevaEstancia)";
        return;
    }

    ui->DescTipoEstancia->setText(info->getTipoEstancia());
    ui->DescDuracEstancia->setText(QString::number(info->getDuracEstancia()));
}

void NuevaEstanciaUI::setUpBotones()
{
    connect(ui->BotonAbrirLibro, &QPushButton::clicked, [this](){ this->pasarPagina(0); });
    connect(ui->BotonAvanzar, &QPushButton::clicked, [this](){ pasarPagina(ui->Documentos->currentIndex()+1); });
    connect(ui->BotonRetroceder, &QPushButton::clicked, [this](){ pasarPagina(ui->Documentos->currentIndex()-1); });
}

void NuevaEstanciaUI::resetearApariencia()
{
    ui->Libro->setCurrentWidget(ui->Cerrado);
    ui->Documentos->setCurrentIndex(0);
}

void NuevaEstanciaUI::pasarPagina(int pag)
{
    qDebug() << pag;
    if (pag == -1){
        Sonidos[1].play();
        ui->Libro->setCurrentWidget(ui->Cerrado);
        return;
    }

    if (pag == 0 && ui->Documentos->currentIndex() == 0){
        Sonidos[0].play();
        ui->Libro->setCurrentWidget(ui->Abierto);
        ui->Documentos->setCurrentIndex(0);
        return;
    }

    if (pag == ui->Documentos->count())
        return;

    Sonidos[2].play();
    ui->Documentos->setCurrentIndex(pag);
}

void NuevaEstanciaUI::setUpPagina(const vector<QString>& Datos, QLabel *&LabelSetUp)
{
    QString Texto;
    for (const auto& linea: Datos)
        Texto += "- " + linea + "\n";

    LabelSetUp->setText(Texto);
}

NuevaEstanciaUI::~NuevaEstanciaUI()
{
    delete ui;
}
