#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QDebug>

/// #################################### CONSTRUCTOR ###################################################
GameScreen::GameScreen(Juego* newJuego, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameScreen)
{
    ui->setupUi(this);

    juego = newJuego;
    Pausado = false;

    setUpLibroReglas();

    pantallaPerdiste = new PantallaPerdiste(this);
    pantallaPerdiste->setFixedSize(1920,1080);
    pantallaPerdiste->hide();

    // Seteamos el juego, y obtenemos la cola de NPCs.
    ColaNPC* Cola = juego->getCola();

    tiempoPartida.setSingleShot(true);

    // Agregamos el NPC y Documentos a la escena
    GestorNPC.setUp(ui->Escritorio, ui->FondoNPC, Cola);
    GestorNPC.setUpTranscriptor(ui->transcBoton);
    GestorDocs.setUp(1, ui->Escritorio);
    setUpIconoDocsUI();

    // Agregamos el libro de reglas
    libroReglasUI = new libroreglas(juego, ui->Escritorio);

    introPantalla = new IntroPantalla(juego, this);
    introPantalla->setFixedSize(1920,1080);
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
}

void GameScreen::setUpLibroReglas()
{
    MostrandoReglas = false;
    bloquearBotonReglas.setSingleShot(true);
    connect(&bloquearBotonReglas, &QTimer::timeout, [this]() {
        ui->reglasBoton->setEnabled(true);
    });
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
}

void GameScreen::BloquearBotones(bool Bloqueo)
{
    this->BotonesBloqueados = Bloqueo;
    BotonCentrar->BloquearBoton(Bloqueo);
    BotonAprobar->BloquearBoton(Bloqueo);
    BotonRechazar->BloquearBoton(Bloqueo);
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
    connect(IconoDocs, &DocsIconUI::animacionSalirTerminada, &GestorNPC, &GestorNPCsUI::SalirEntidades);

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
}

void GameScreen::PrepararJuego(int Nivel, int Dificultad)
{
    juego->PrepararJuego(Nivel, Dificultad);
    libroReglasUI->setUpLevel(Nivel);
    // more stuff to do
    GestorDocs.setUpNivel(Nivel);
}

void GameScreen::PrepararJuego(PlayerStats stats)
{
    juego->PrepararJuego(stats);
    libroReglasUI->setUpLevel(stats.Nivel);
    // more stuff to do
    GestorDocs.setUpNivel(stats.Nivel);
}

void GameScreen::Iniciar()
{
    introPantalla->Mostrar();
}

void GameScreen::arrancarJuego()
{
    qDebug() << "Arranco";
    tiempoPartida.start(8*60*1000); // 8 Minutos

    // Seteamos el pasaje de tiempo en el juego
    TiempoDia.start(52 * 1000); // Cada 52 segundos el tiempo cambia
    TiempoActual = 0;
    ActualizarTiempo();

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
    tiempoRestante = tiempoPartida.remainingTime();
    tiempoPartida.stop();
    Pausado = true;
}

void GameScreen::ReanudarJuego()
{
    GestorNPC.Reanudar();
    tiempoPartida.start(tiempoRestante);

    Pausado = false;
}

/// #################################### FINAL DE PARTIDA ###################################################

void GameScreen::FinalDePartida()
{
    emit LogJugador("Juego terminado");
    // Si queda un NPC en escena, lo hacemos salir junto a sus documentos.
    if (GestorNPC.MostrandoElNPC()){
        if (GestorDocs.getMostrando())
            GestorDocs.Salir();
        IconoDocs->Sacar();
    }

    GestorNPC.TerminoNivel();

    if (MostrandoReglas)
        MostrarReglas();

    if (tiempoPartida.isActive())
        tiempoPartida.stop();
    TiempoDia.stop();


    if (!Pausado){
        if (juego->getTotalSocialCredits() < 0)
           pantallaPerdiste->Iniciar(true);
        else pantallaPerdiste->Iniciar(false);
    } else
        emit LogJugador("Juego terminado forzosamente");
}

void GameScreen::Decidir()
{
    if (juego->getTotalSocialCredits() < 0){
        emit LogJugador("Jugador perdio");
        emit NivelTerminado(true);
    } else {
        emit LogJugador("Jugador perdio");
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
    emit LogJugador("Jugador acepto a la persona");
    SelloDocumento(true);
}

void GameScreen::Rechazo()
{
    juego->addNPCrechazado();
    GestorDocs.Rechazar();
    emit LogJugador("Jugador rechazo a la persona");
    SelloDocumento(false);   
}

void GameScreen::SelloDocumento(bool Boton)
{
    juego->EvaluarDecision(GestorNPC.getTipo(), GestorNPC.getValidez(), Boton);

    if (Boton == GestorNPC.getValidez())
        emit LogJugador("Jugador tomo la decision correcta.");
    else{
        emit LogJugador("Jugador tomo decision equivocada.\nError cometido: ");
        emit LogJugador(GestorNPC.getDatosFalsos());
    }

    IconoDocs->BloquearDocumento();
    GestorNPC.Salir(Boton);

    emit LogJugador("Puntaje actual: " + QString::number(juego->getSocialCreditsEarnedInLevel()));
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
    if (GestorNPC.MostrandoElNPC())
        GestorNPC.Centrar();
    if (pantallaPerdiste->getMostrandoPantalla())
        pantallaPerdiste->setFixedSize(width(), height());
}



