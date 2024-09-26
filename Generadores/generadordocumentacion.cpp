#include "generadordocumentacion.h"
#include <ctime>
#include <QDebug>

/// #################################### CONSTRUCTOR ###################################################
GeneradorDocumentacion::GeneradorDocumentacion():
    NumeroRandom(static_cast<quint32>(time(NULL))),
    randomizadorCaracteres(&NumeroRandom)
{
    NivelActual = 1;
    DificultadJuego = 1;
    SetDificultadNivel();

    // Seteamos el randomizador de caracteres
}

void GeneradorDocumentacion::Inicializar(int Nivel, int Dificultad, Reglas **rules)
{
    this->setNivel(Nivel);
    this->setDificultad(Dificultad);
    this->InicializarGeneradores(rules);
}

void GeneradorDocumentacion::InicializarGeneradores(Reglas **rules)
{
    /// Work in progress
    reglasNivel1 = dynamic_cast<ReglasNivel1*>(rules[0]);
    reglasNivel2 = dynamic_cast<ReglasNivel2*>(rules[1]);
    reglasNivel3 = dynamic_cast<ReglasNivel3*>(rules[2]);
    reglasNivel4 = dynamic_cast<ReglasNivel4*>(rules[3]);
    reglasNivel5 = dynamic_cast<ReglasNivel5*>(rules[4]);

    generadorPasaporte.Inicializar(reglasNivel1);
    generadorEstancia.Inicializar(reglasNivel1, &randomizadorCaracteres);
    generadorListaAcomp.Inicializar(&NumeroRandom);
    generadorPaisResidencia.Inicializar(reglasNivel1, reglasNivel2);
}

GeneradorDocumentacion::~GeneradorDocumentacion()
{
    // delete de los siguientes generadores
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

    if (!Validez)
        NPC2Generate->setDatosFalsos(logDatosFalsos());

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
}

QString GeneradorDocumentacion::logDatosFalsos()
{
    QString log = "";
    if (!DocsValidos[0])
        log = "Documento de de identificacion invalido\n";
    if (!DocsValidos[1])
        log += "Documento de estancia invalido\n";
    if (!DocsValidos[2])
        log += "Pais de residencia invalido\n";
    if (!DocsValidos[3])
        log += "Lista de acompañantes invalida\n";

    return log;
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
    Pasaporte* nuevoPasaporte = generadorPasaporte.crear_pasaporte(DocsValidos[Index], dynamic_cast<NPCcomun*>(NPC2Generate), DificultadJuego);
    NPC2Generate->addDocumento(nuevoPasaporte, Index);
    Index++;

    // Generador de Estancias
    Estancia* nuevaEstancia = generadorEstancia.getEstancia(DocsValidos[Index], DificultadJuego);
    NPC2Generate->addDocumento(nuevaEstancia, Index);
    Index++;
}

void GeneradorDocumentacion::GenerarDocumentosNivel2(int &Index)
{
    // Generador de Residencia
    PaisResidencia * nuevoPaisResidencia = generadorPaisResidencia.CrearPaisResidencia(NPC2Generate->getPasaporte(),DocsValidos[Index], DificultadJuego);
    NPC2Generate->addDocumento(nuevoPaisResidencia,Index);
    Index++;
}

void GeneradorDocumentacion::GenerarDocumentosNivel3(int &Index)
{
    // Generador de Lista de Acompañantes
    ListaAcompaniantes * nuevaLista = generadorListaAcomp.getListaAcompaniantes(DocsValidos[Index]);
    NPC2Generate->addDocumento(nuevaLista, Index);
    Index++;
}

void GeneradorDocumentacion::GenerarDocumentosNivel4(int &Index)
{
    // Nuevo documento de estancia
    Index++;
}

void GeneradorDocumentacion::GenerarDocumentosNivel5(int &Index)
{
    // Xray y Antecedentes
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
        MaxDocumentos = 4;
        MaxDocumentosInvalidos = 2;
        break;
    default:
        MaxDocumentos = 6;
        MaxDocumentosInvalidos = 3;
        break;
    }
}
