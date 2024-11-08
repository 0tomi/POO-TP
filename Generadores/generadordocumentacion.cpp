#include "generadordocumentacion.h"
#include <QTime>
#include <QDebug>

/// #################################### CONSTRUCTOR ###################################################
GeneradorDocumentacion::GeneradorDocumentacion():
    NumeroRandom(QTime::currentTime().msec()),
    randomizadorCaracteres(&NumeroRandom)
{
    NivelActual = 1;
    DificultadJuego = 1;
    SetDificultadNivel();

    // Seteamos el randomizador de caracteres
}

void GeneradorDocumentacion::Inicializar(int Nivel, int Dificultad, Reglas **rules, quint32 seed)
{
    this->setSeed(seed);
    this->setNivel(Nivel);
    this->setDificultad(Dificultad);
    this->InicializarGeneradores(rules, Nivel);
}

void GeneradorDocumentacion::setSeed(quint32 seed)
{
    this->semilla = seed;
    this->NumeroRandom.seed(seed);
}

void GeneradorDocumentacion::InicializarGeneradores(Reglas **rules, int nivel)
{
    /// Work in progress
    reglasNivel1 = dynamic_cast<ReglasNivel1*>(rules[0]);
    generadorPasaporte.Inicializar(reglasNivel1, this->semilla, this->DificultadJuego);
    generadorEstancia.Inicializar(reglasNivel1, &randomizadorCaracteres, this->semilla, this->DificultadJuego);

    if (nivel > 1){
        reglasNivel2 = dynamic_cast<ReglasNivel2*>(rules[1]);
        generadorPaisResidencia.Inicializar(reglasNivel1, reglasNivel2, this->semilla, this->DificultadJuego);
    }
    if (nivel > 2){
        reglasNivel3 = dynamic_cast<ReglasNivel3*>(rules[2]);
        generadorListaAcomp.Inicializar(&NumeroRandom, reglasNivel3); // Falta aniadir los requerimientos de nivel 3
    }
    if (nivel > 3){
        reglasNivel4 = dynamic_cast<ReglasNivel4*>(rules[3]);
        generadorNuevaEstancia.inicializadorNivel4(reglasNivel4, this->semilla, this->DificultadJuego);
    }
    if (nivel > 4){
        reglasNivel5 = dynamic_cast<ReglasNivel5*>(rules[4]);
        generadorRadiografia.inicializar(nullptr, this->semilla, this->DificultadJuego);
    }
}

GeneradorDocumentacion::~GeneradorDocumentacion()
{
    // Como mudamos todo a estatico este metodo quedo obsoleto
}

/// #################################### GETTERS ###################################################
void GeneradorDocumentacion::getDocumentos(NPC *npc, bool Validez)
{
    // Index va a ser quien se encargue de decirle a NPC donde guardar los documentos (segun el tipo)
    int Index = 0;
    NPC2Generate = npc;

    // Aca iria el sorteo de cuales documentos seran verdaderos y cuales falsos.
    if (Validez)
        for (int i = 0; i < 10; i++)
            DocsValidos[i] = true;
    else
        GenerarCantidadDocsInvalidos();

    GenerarDocumentosNivel1(Index);

    if (NivelActual >= 2){
        GenerarDocumentosNivel2(Index);
    }
    if (NivelActual >= 3){
        GenerarDocumentosNivel3(Index);
    }
    if (NivelActual >= 4){
        GenerarDocumentosNivel4(Index);
    }
    if (NivelActual >= 5){
        GenerarDocumentosNivel5(Index);
    }

    if (!Validez)
        NPC2Generate->updateDatosFalsos();
}

/// #################################### GENERADORES SEGUN NIVEL ############################################
/// La estructura para añadir un documento nuevo al generador es la siguiente, una vez se haya seteado su
/// new en el constructor, y su actualizacion de reglas en el actualizarReglas, van al respectivo nivel que
/// se debe utilizar el generador y usan la siguiente sintaxis:
///
/// Documento * nuevoDocumento = generadorDocumento->getDocumento(parametros requeridos)
/// NPC2Generate->addDocumento(nuevoDocumento, Index);
///
/// Y dejan el Index++ de abajo para tener los generadores coordinados. Obvivamente en Documento lo
/// cambian por el documento respectivo que estan queriendo añadir.
/// #########################################################################################################
void GeneradorDocumentacion::GenerarDocumentosNivel1(int &Index)
{
    // Generador de pasaportes - DNI
    pasaporteActual = generadorPasaporte.generar(DocsValidos[Index], dynamic_cast<NPCcomun*>(NPC2Generate));
    NPC2Generate->addDocumento(pasaporteActual, Index);
    Index++;

    // Generador de Estancias
    Estancia* nuevaEstancia = generadorEstancia.generar(DocsValidos[Index]);
    NPC2Generate->addDocumento(nuevaEstancia, Index);
    estanciaActual = nuevaEstancia;
    Index++;
}

void GeneradorDocumentacion::GenerarDocumentosNivel2(int &Index)
{
    // Generador de Residencia
    PaisResidencia * nuevoPaisResidencia = generadorPaisResidencia.generar(pasaporteActual, DocsValidos[Index]);
    NPC2Generate->addDocumento(nuevoPaisResidencia,Index);
    Index++;
}

void GeneradorDocumentacion::GenerarDocumentosNivel3(int &Index)
{
    // Generador de Lista de Acompañantes
    ListaAcompaniantes * nuevaLista = generadorListaAcomp.generar(DocsValidos[Index]);
    NPC2Generate->addDocumento(nuevaLista, Index);
    listaAcompActual = nuevaLista;
    Index++;
}

void GeneradorDocumentacion::GenerarDocumentosNivel4(int &Index)
{
    // Nuevo documento de estancia
    auto nuevaEstancia = generadorNuevaEstancia.generar(estanciaActual ,DocsValidos[Index]);
    NPC2Generate->addDocumento(nuevaEstancia, Index);
    Index++;
}

void GeneradorDocumentacion::GenerarDocumentosNivel5(int &Index)
{
    // Xray y Antecedentes
    auto Radiografia = generadorRadiografia.generar_radiografia(DocsValidos[Index]);
    NPC2Generate->addDocumento(Radiografia,Index);
    Index++; //Y otro index++ por si hacemos los antecedentes.
}

/// #################################### DOCUMENTOS INVALIDOS ###################################################
void GeneradorDocumentacion::GenerarCantidadDocsInvalidos()
{
    int CantDocumentosInvalidos = 0;
    int ValorCentinela;

    // Si es el primer nivel hacemos que esto pueda variar para hacerla mas facil.
    if (NivelActual == 1)
        MaxDocumentosInvalidos = NumeroRandom.bounded(2) + 1;

    // Lo repetimos hasta que nos genere la cantidad necesaria de documentos invalidos.
    while (CantDocumentosInvalidos < MaxDocumentosInvalidos){
        for (int i = 0; i < MaxDocumentos; i++){
            ValorCentinela = NumeroRandom.bounded(0,10);
            if (ValorCentinela < 4){
                DocsValidos[i] = false;
                CantDocumentosInvalidos++;
            } else
                DocsValidos[i] = true;
        }
    }

    // Dejamos el resto de documentos en true para los logs.
    for (int i = MaxDocumentos; i < 10; i++)
        DocsValidos[i] = true;
}

/// #################################### SETTERS ###################################################
void GeneradorDocumentacion::setNivel(int Nivel)
{
    NivelActual = Nivel;
    SetDificultadNivel();
}

void GeneradorDocumentacion::setDificultad(int Dificultad)
{
    DificultadJuego = Dificultad;
}

void GeneradorDocumentacion::SetDificultadNivel()
{
    switch (NivelActual) {
    case 1:
        MaxDocumentos = 2;
        MaxDocumentosInvalidos = 1;
        break;
    case 2:
        MaxDocumentos = 3;
        MaxDocumentosInvalidos = 2;
        break;
    case 3:
        MaxDocumentos = 4;
        MaxDocumentosInvalidos = 2;
        break;
    case 4:
        MaxDocumentos = 5;
        MaxDocumentosInvalidos = 2;
        break;
    default:
        MaxDocumentos = 6;
        MaxDocumentosInvalidos = 3;
        break;
    }
}
