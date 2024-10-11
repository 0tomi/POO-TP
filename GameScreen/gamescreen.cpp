#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QDebug>

/// #################################### CONSTRUCTOR ###################################################
GameScreen::GameScreen(Juego* newJuego, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameScreen), Musica{ QSoundEffect(this), QSoundEffect(this), QSoundEffect(this)}
    , random(QTime::currentTime().msec()), currentMusic(0)
{
    ui->setupUi(this);

    juego = newJuego;
    Pausado = false;

    setUpLibroReglas();
    setUpSonidos();

    pantallaPerdiste = new PantallaPerdiste(this);
    pantallaPerdiste->resize(this->size());
    pantallaPerdiste->hide();

    // Seteamos el juego, y obtenemos la cola de NPCs.
    ColaNPC* Cola = juego->getCola();

    tiempoPartida.setSingleShot(true);
    volumenActual = 1.0;

    // Agregamos el NPC y Documentos a la escena
    GestorNPC.setUp(ui->Escritorio, ui->FondoNPC, Cola);
    GestorNPC.setUpTranscriptor(ui->transcBoton);
    GestorDocs.setUp(1, ui->Escritorio);
    setUpIconoDocsUI();

    // Agregamos el libro de reglas
    libroReglasUI = new libroreglas(juego, ui->Escritorio);

    introPantalla = new IntroPantalla(juego, this);
    introPantalla->acomodarPantalla();
    introPantalla->hide();

    SpawnearBotones();
    RealizarConexionesPrincipales();
    BloquearBotones(true);
}

GameScreen::~GameScreen()
{
    delete ui;
    delete BotonAprobar;
    delete BotonRechazar;
    delete BotonCentrar;
    delete pantallaPerdiste;
    delete BotonScanner;
}

void GameScreen::setUpLibroReglas()
{
    MostrandoReglas = false;
    bloquearBotonReglas.setSingleShot(true);
    connect(&bloquearBotonReglas, &QTimer::timeout, [this]() {
        ui->reglasBoton->setEnabled(true);
    });
}

void GameScreen::setUpSonidos()
{
    Musica[0].setSource(QUrl("qrc:/Resources/Musica/MusicaJuego1.WAV"));
    Musica[1].setSource(QUrl("qrc:/Resources/Musica/MusicaJuego2.WAV"));
    Musica[2].setSource(QUrl("qrc:/Resources/Musica/MusicaJuego3.WAV"));
    for (int i = 0; i < 3; i++){
        Musica[i].setLoopCount(QSoundEffect::Infinite);
        Musica[i].setVolume(0.3);
    }
}
/// #################################### BOTONES ###################################################
void GameScreen::SpawnearBotones()
{
    // Añadimos los botones a la escena
    QString BotonAceptarDesbloqueado = ":/Resources/MaterialPantallas/BotonAprobarSinApretar.png";
    QString BotonAceptarBloqueado = ":/Resources/MaterialPantallas/BotonAprobarApretado.png";
    QString BotonRechazarDesbloqueado = ":/Resources/MaterialPantallas/BotonDesaprobarNoApretado .png";
    QString BotonRechazarBloqueado = ":/Resources/MaterialPantallas/BotonDesaprobarApretado.png";
    QString BotonCentrarBlock = ":/Resources/MaterialPantallas/BotonCentrarBloqueado.png";
    QString BotonCentrarDesblock = ":/Resources/MaterialPantallas/BotonCentrarDesbloqueado.png";

    BotonAprobar = new BotonesCustom(BotonAceptarDesbloqueado, BotonAceptarBloqueado, ui->ContenedorBotones);
    BotonRechazar = new BotonesCustom(BotonRechazarDesbloqueado, BotonRechazarBloqueado, ui->ContenedorBotones);
    BotonCentrar = new BotonesCustom(BotonCentrarDesblock, BotonCentrarBlock,ui->ContenedorBotones);
    EspaciadorBotones = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    BotonAprobar->resize(200,125);
    BotonRechazar->resize(200,125);

    BotonAprobar->SetTiempoBloqueo(2500);
    BotonRechazar->SetTiempoBloqueo(2500);
    BotonCentrar->SetTiempoBloqueo(1000);

    ui->ContenedorBotones->layout()->addWidget(BotonCentrar);
    ui->ContenedorBotones->layout()->addItem(EspaciadorBotones);
    ui->ContenedorBotones->layout()->addWidget(BotonAprobar);
    ui->ContenedorBotones->layout()->addWidget(BotonRechazar);
    setUpBotonEscanner();
}

void GameScreen::setUpBotonEscanner()
{
    QString EscanerSinApretar = ":/Resources/MaterialPantallas/BotonEscanerSinApretar.png";
    QString EscanerApretado = ":/Resources/MaterialPantallas/BotonEscanerApretado.png";
    QString SonidoEscanner = "qrc:/Resources/Sonidos/SonidoScanner.wav";

    BotonScanner = new BotonesCustom(EscanerSinApretar, EscanerApretado, BotonesCustom::Normal, SonidoEscanner, 0.6, ui->BotonEscannerUI);
    BotonScanner->copyFormat();
    ui->BotonEscannerUI->layout()->addWidget(BotonScanner);

    // Falta implementar mas cosas de la radiografia
    RadiografiaUI = new radiografiaui(ui->Escritorio);
    GestorDocs.addRadiografia(RadiografiaUI);

    //dejo esto aca para que se bugee el codigo porque quedan cosas que hacer:
    //hacer que radiografia tenga estado de mostrandose o no, para que el boton pueda operar
    //hacer que radiografia se actualize cada vez que pasa un npc nuevo.

    connect(BotonScanner, &BotonesCustom::BotonApretado, [this](){
        if (RadiografiaUI->getMostrando())
            RadiografiaUI->Sacar();
        else RadiografiaUI->Entrar();
    });
}

void GameScreen::BloquearBotones(bool Bloqueo)
{
    this->BotonesBloqueados = Bloqueo;
    BotonCentrar->BloquearBoton(Bloqueo);
    BotonAprobar->BloquearBoton(Bloqueo);
    BotonRechazar->BloquearBoton(Bloqueo);
    if (this->nivelActual >= 5)
        BotonScanner->BloquearBoton(Bloqueo);
}

void GameScreen::DesbloquearBotones()
{
    BloquearBotones(false);
}

/// Icono documentos
void GameScreen::setUpIconoDocsUI()
{
    IconoDocs = new DocsIconUI(ui->MesaAzul);

    // Establecemos un layout para que el documento se centre y tenga resize.
    QHBoxLayout * layout = new QHBoxLayout(ui->MesaAzul);
    layout->addWidget(IconoDocs);
    ui->MesaAzul->setLayout(layout);

    // Hacemos que los documentos entren en escena solo cuando se clickea el documento.
    connect(&GestorNPC, &GestorNPCsUI::NPCTerminoEntrar, IconoDocs, &DocsIconUI::Entrar);
    connect(IconoDocs, &DocsIconUI::Abierto, &GestorDocs, &GestorDocumentosUI::Entrar);
    connect(IconoDocs, &DocsIconUI::Cerrado, &GestorDocs, &GestorDocumentosUI::Salir);

    // Cuando entregamos el documento, sale el npc.
    connect(IconoDocs, &DocsIconUI::animacionSalirTerminada, [this](bool FinalPartida){
        if (!FinalPartida){
            GestorNPC.SalirEntidades();
            SelloDocumento(this->DecisionJugador);
        }
    });

    SetearConexionesDocumentos();
}

void GameScreen::SetearConexionesDocumentos()
{
    // Bloqueamos los botones al estar el documento cerrado o abierto.
    connect(IconoDocs, &DocsIconUI::Abierto, [this]() {
        this->DesbloquearBotones();
    });

    connect(IconoDocs, &DocsIconUI::Cerrado, [this]() {
        this->BloquearBotones(true);
    });
}

/// #################################### CONEXIONES ###################################################
void GameScreen::setVolumenes(float volumen)
{
    this->volumenActual = volumen;
    introPantalla->setVolumenes(volumen);
    BotonAprobar->setVolumen(volumen);
    BotonCentrar->setVolumen(volumen);
    BotonRechazar->setVolumen(volumen);
    BotonScanner->setVolumen(volumen);
    libroReglasUI->setVolume(volumen);
    GestorNPC.setVolumen(volumen);
    for (int i = 0; i < Notificaciones.size(); ++i)
        if (Notificaciones[i])
            Notificaciones[i]->setVolume(volumen);
    IconoDocs->setVolumenes(volumen);
}

void GameScreen::setMusicVolume(float vol)
{
    Musica[0].setVolume(vol-0.3);
    Musica[1].setVolume(vol-0.3);
    Musica[2].setVolume(vol-0.3);
}

void GameScreen::RealizarConexionesPrincipales()
{
    // Conecto los botones para que segun lo que haga el usuario, se evalue una cosa u otra.
    connect(BotonAprobar, &BotonesCustom::BotonApretado, this, &GameScreen::Acepto);
    connect(BotonRechazar, &BotonesCustom::BotonApretado, this, &GameScreen::Rechazo);

    // Conectamos boton de centrar para centrar el documento.
    connect(BotonCentrar, &BotonesCustom::BotonApretado, &GestorDocs, &GestorDocumentosUI::Centrar);

    connect(pantallaPerdiste, &PantallaPerdiste::AnimacionTermino, this, &GameScreen::Decidir);

    // Conectamos nuestro cronometro rustico
    connect(&TiempoDia, &QTimer::timeout, this, &GameScreen::ActualizarTiempo);

    // Conectamos el temporizador de partida para terminar la partida.
    connect(&tiempoPartida, &QTimer::timeout, this, &GameScreen::FinalDePartida);

    // Conectamos el quedarse sin npcs con el final de la partida
    connect(&GestorNPC, &GestorNPCsUI::ColaTerminada, this, &GameScreen::FinalDePartida);

    // Conectmaos el boton de reglas
    connect(ui->reglasBoton, &QPushButton::clicked, this, &GameScreen::MostrarReglas);

    // Conectamos el gestor de NPCs al gestor de Documentos
    connect(&GestorNPC, &GestorNPCsUI::setDocsInfo, &GestorDocs, &GestorDocumentosUI::setDocumento);

    connect(introPantalla, &IntroPantalla::ClickeoEmpezar, this, &GameScreen::arrancarJuego);
}

/// #################################### PREPRARAR JUEGO ###################################################

void GameScreen::PrepararJuego(int Dificultad)
{
    juego->PrepararJuego(Dificultad);
    libroReglasUI->setUpLevel(1);
    GestorDocs.setUpNivel(1);
    introPantalla->setUp(1);
    this->nivelActual = 1;
}

void GameScreen::PrepararJuego(int Nivel, int Dificultad)
{
    juego->PrepararJuego(Nivel, Dificultad);
    libroReglasUI->setUpLevel(Nivel);
    // more stuff to do
    GestorDocs.setUpNivel(Nivel);
    introPantalla->setUp(Nivel);
    this->nivelActual = Nivel;
}

void GameScreen::PrepararJuegoCheat(int LvL, int Dificultad, quint32 seed)
{
    juego->PrepararJuego(LvL, Dificultad, seed);
    libroReglasUI->setUpLevel(LvL);
    // more stuff to do
    GestorDocs.setUpNivel(LvL);
    introPantalla->setUp(LvL);
    this->nivelActual = LvL;
}

void GameScreen::PrepararJuego(PlayerStats stats)
{
    juego->PrepararJuego(stats);
    libroReglasUI->setUpLevel(stats.Nivel);
    // more stuff to do
    GestorDocs.setUpNivel(stats.Nivel);
    introPantalla->setUp(stats.Nivel);
    this->nivelActual = stats.Nivel;
}

void GameScreen::Iniciar()
{
    if (nivelActual >= 5){
        BotonScanner->show();
        currentMusic = 2;
        Musica[2].setVolume(0.4);
    } else {
        BotonScanner->hide();
        currentMusic = random.bounded(2);
        Musica[currentMusic].setVolume(0.3);
    }

    IconoDocs->setFinalPartida(false);
    Notificaciones.clear();
    introPantalla->Mostrar();
}

void GameScreen::arrancarJuego()
{
    tiempoPartida.start(8*60*1000); // 8 Minutos

    // Seteamos el pasaje de tiempo en el juego
    TiempoDia.start(52 * 1000); // Cada 52 segundos el tiempo cambia
    TiempoActual = 0;
    ActualizarTiempo();

    Musica[currentMusic].play();
    GestorNPC.EmpezarJuego();
    GestorNPC.Entrar();
}

/// #################################### REINICIAR ###################################################

void GameScreen::Restart()
{
    juego->setDefaultStats();
    /// A futuro un reset donde cambiamos las reglas
}

/// #################################### PAUSAR JUEGO ###################################################

void GameScreen::PausarJuego()
{
    GestorNPC.Pausar();
    Musica[currentMusic].stop();
    tiempoRestante = tiempoPartida.remainingTime();
    tiempoPartida.stop();
    Pausado = true;
}

void GameScreen::ReanudarJuego()
{
    GestorNPC.Reanudar();
    Musica[currentMusic].play();
    tiempoPartida.start(tiempoRestante);

    Pausado = false;
}

/// #################################### FINAL DE PARTIDA ###################################################

void GameScreen::FinalDePartida()
{
    Musica[currentMusic].stop();
    MatarNotificaciones();
    GestorNPC.TerminoNivel();
    GestorDocs.TerminoNivel();
    IconoDocs->setFinalPartida(true);
    IconoDocs->Sacar();

    if (MostrandoReglas)
        MostrarReglas();

    if (tiempoPartida.isActive())
        tiempoPartida.stop();
    TiempoDia.stop();

    if (!Pausado){
        emit EnviarLogs("Juego terminado");
        if (juego->getTotalSocialCredits() < 0)
           pantallaPerdiste->Iniciar(true);
        else pantallaPerdiste->Iniciar(false);
    } else
        emit EnviarLogs("Juego terminado forzosamente");
}

void GameScreen::Decidir()
{
    if (juego->getTotalSocialCredits() < 0){
        emit EnviarLogs("Jugador perdio");
        emit NivelTerminado(true);
    } else {
        emit EnviarLogs("Jugador gano");
        emit NivelTerminado(false);
    }
}

void GameScreen::ActualizarTiempo()
{
    ui->Pasillo->setCurrentIndex(TiempoActual);
    TiempoActual++;
    if (TiempoActual > 9)
        TiempoActual = 0;
}

/// #################################### DECISIONES DEL JUGADOR ###################################################

void GameScreen::Acepto()
{
    juego->addNPCaceptado();
    GestorDocs.Aprobado();
    emit EnviarLogs("Jugador acepto a la persona");
    DecisionJugador = true;
    IconoDocs->BloquearDocumento();
    GestorNPC.Salir(true);
}

void GameScreen::Rechazo()
{
    juego->addNPCrechazado();
    GestorDocs.Rechazar();
    emit EnviarLogs("Jugador rechazo a la persona");
    DecisionJugador = false;
    IconoDocs->BloquearDocumento();
    GestorNPC.Salir(false);
}

void GameScreen::SelloDocumento(bool Boton)
{
    bool Veredicto;
    bool Multa = juego->EvaluarDecision(Veredicto, GestorNPC.getTipo(), GestorNPC.getValidez(), Boton);

    if (Veredicto)
        emit EnviarLogs("Jugador tomo la decision correcta.");
    else{
        QString ErrorCometido = GestorNPC.getDatosFalsos();
        CrearNotificacion(Multa, ErrorCometido);
        emit EnviarLogs("Jugador tomo decision equivocada.\nError cometido: ");
         emit EnviarLogs(GestorNPC.getDatosFalsos());
    }

    emit EnviarLogs("Puntaje actual: " + QString::number(juego->getSocialCreditsEarnedInLevel()));
}

/// #################################### Libro de Reglas ###################################################
void GameScreen::MostrarReglas()
{
    ui->reglasBoton->setEnabled(false);
    bloquearBotonReglas.start(500);

    if (MostrandoReglas){
        libroReglasUI->Sacar();
        MostrandoReglas = false;
    } else {
        libroReglasUI->Entrar();
        MostrandoReglas = true;
    }
}

/// #################################### NOTIFICACIONES ####################################
void GameScreen::CrearNotificacion(bool Multa, QString& Motivo)
{
    Notificacion* nuevaNotificacion = new Notificacion(CantidadNotificaciones, Multa, Motivo, this->volumenActual, ui->Escritorio);
    nuevaNotificacion->Entrar();
    connect(nuevaNotificacion, &Notificacion::QuiereCerrarNotificacion, this, &GameScreen::MatarNotificacion);
    Notificaciones.push_back(nuevaNotificacion);
    CantidadNotificaciones++;
}

void GameScreen::MatarNotificaciones()
{
    if (CantidadNotificaciones){
        emit EnviarLogs( "Cantidad de notificaciones: " + QString::number(Notificaciones.size()));
        for (int i = 0; i < Notificaciones.size(); ++i)
            if (Notificaciones[i])
                delete Notificaciones[i];
    }
    CantidadNotificaciones = 0;
}

void GameScreen::MatarNotificacion(int Numero)
{
    delete Notificaciones[Numero];
    Notificaciones[Numero] = nullptr;
}
/// #################################### EVENTOS DE VENTANA ###################################################

void GameScreen::keyPressEvent(QKeyEvent *event)
{
    if (!BotonesBloqueados){
        if (event->key() == Qt::Key_A){
            BotonAprobar->Accion();
        } else
            if (event->key() == Qt::Key_D) {
                BotonRechazar->Accion();
            } else
                if (event->key() == Qt::Key_C)
                    BotonCentrar->Accion();
    }

    // Abre los documentos con el espacio.
    if (event->key() == Qt::Key_Space)
        if (this->IconoDocs->Mostrando())
            this->IconoDocs->accionar();

    // Apreta el boton de transcripcion
    if (event->key() == Qt::Key_T)
        ui->transcBoton->click();

    // Apreta el boton de reglas
    if (event->key() == Qt::Key_N)
        ui->reglasBoton->click();

    QWidget::keyPressEvent(event);
}

void GameScreen::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::WindowStateChange){
        if (GestorNPC.MostrandoElNPC())
            GestorNPC.Centrar();
        if (pantallaPerdiste->getMostrandoPantalla())
            pantallaPerdiste->setFixedSize(width(), height());
    }
}

void GameScreen::resizeEvent(QResizeEvent *event)
{
    // En caso de cambiar la ventana, ajustamos el tamaño del NPC
    QWidget::resizeEvent(event);
    this->introPantalla->acomodarPantalla();
    if (GestorNPC.MostrandoElNPC())
        GestorNPC.Centrar();
    if (pantallaPerdiste->getMostrandoPantalla())
        pantallaPerdiste->resize(this->size());
}



