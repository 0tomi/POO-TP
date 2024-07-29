#include "generadornpc.h"
#include "generadornpc.h"
#include "../lectorarchivos.h"

#include <ctime>
#include <QDebug>

GeneradorNPC::GeneradorNPC(){
    // # Deus ignoscat factis quae mox faciam. #
    Random = new QRandomGenerator(time(NULL));

    // Lectura de las partes del cuerpo
    LectorArchivos lector(":/Resources/ArchivosTexto/URLCarasHombre.txt");
    LinksCarasHombre = lector.getArray();
    topeLinksCaras = lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLCarasMujer.txt");
    LinksCarasMujer = lector.getArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLCarasRevolucionario.txt");
    LinksCarasRevolucionario = lector.getArray();
    topeLinksRevolucionario = lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLCarasRefugiadoHombre.txt");
    LinksCarasRefugiadoHombre = lector.getArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLCarasRefugiadoMujer.txt");
    LinksCarasRefugiadoMujer = lector.getArray();
    topeLinksRefugiado = lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLBarbas.txt");
    LinksBarbas = lector.getArray();
    topeLinksBarbas = lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLOjos.txt");
    LinksOjos = lector.getArray();
    topeLinksOjos = lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLBocas.txt");
    LinksBocas = lector.getArray();
    topeLinksBocas = lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLCejas.txt");
    LinksCejas = lector.getArray();
    topeLinksCejas = lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLNariz.txt");
    LinksNariz = lector.getArray();
    topeLinksNariz = lector.getTopeArray();

    // Lectura de dialogos
    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/DialogosRevolucionario.txt");
    DialogosRevolucionario = lector.getArray();
    topeDialogosRev = lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/Dialogos/DialogosRefugiadoPolitico.txt");
    DialogosRefugiado = lector.getArray();
    topeDialogosRef = lector.getTopeArray();

    // Lectura de dialogos para nivel 2
    lector.LeerArchivoNuevo(":/Resources/Dialogos/DialogosEstudiante.txt");
    DialogosEstudiante=lector.getArray();
    topeDialogosEstudiante=lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/Dialogos/DialogosTurista.txt");
    DialogosTurista=lector.getArray();
    topeDialogosTurista=lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/Dialogos/DialogosTrabajador.txt");
    DialogosTrabajador=lector.getArray();
    topeDialogosTrabajador=lector.getTopeArray();

    // Lectura de dialogos de nivel 3
    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/dialogosAcompaniantes.txt");
    this->dialogosAcomps = lector.getArray();
    this->topeDialogosAcomp = lector.getTopeArray();
}


// Esto necesita rework a futuro para distinguir entre caras de Mujeres y Hombres
NPC* GeneradorNPC::getNPCgenerico(int tipo, bool Validez){
    NPCcomun* NPCaCrear;
    // 0: Aldeano, 1: Refugiado, 2: Diplomatico, 3: Revolucionario
    if (tipo > 3)
        tipo = Random->bounded(4);

    // Pickeamos un genero
    int valorCentinela2 = Random->bounded(11);
    if (valorCentinela2 < 5)
        valorCentinela2 = 0;
    else if (valorCentinela2 < 10)
        valorCentinela2 = 1;
    else valorCentinela2 = 2;

    // Generamos NPC con los datos basicos
    NPCaCrear = new NPCcomun(this->generos[valorCentinela2], tipo, Validez);

    // si es hombre o X
    /*if (valorCentinela2 > 0){
        int TendraBarba = Random->bounded(10);
        if (TendraBarba < 5 && valorCentinela2 == 1)
            NPCaCrear->setBarbaURL(getBarbaRandom());
        if (TendraBarba < 3 && valorCentinela2 == 2)
            NPCaCrear->setBarbaURL(getBarbaRandom());
    }*/

    QString ojos = getOjosRandom();

    // Decidir skin de revolucionario u otro tipo
    if (tipo == 3)
       NPCaCrear->setCaraURL(getCaraRevolucionarioRandom());
    else
        if (tipo == 1)
            NPCaCrear->setCaraURL(getCaraRefugiadoRandom(generos[valorCentinela2]));
        else
            NPCaCrear->setCaraURL(getCaraRandom(generos[valorCentinela2]));

    // Resto del cuerpo
    NPCaCrear->setCejasURL(getCejasRandom());
    NPCaCrear->setOjosURL(ojos);
    NPCaCrear->setBocaURL(getBocaRandom());
    NPCaCrear->setNarizURL(getNarizRandom());

    NPC2create = NPCaCrear;
    return this->NPC2create;
}

NPC *GeneradorNPC::getSimilarNPC(NPC *ejemplo)
{
    // PLACEHOLDER hasta hacerla posteriormente.
    return ejemplo;
}

GeneradorNPC::~GeneradorNPC()
{
    delete LinksBarbas;
    delete LinksBocas;
    delete LinksCarasHombre;
    delete LinksCarasMujer;
    delete LinksCejas;
    delete LinksNariz;
    delete LinksOjos;
}

// ######## Generadores de dialogos #############
void GeneradorNPC::generarDialogos(NPC *npc, int nivel)
{
    switch (nivel){
    case 1: GenerarDialogosNivel1(npc);
        break;
    case 2: GenerarDialogosNivel2(npc);
        break;
    case 3: GenerarDialogosNivel3(npc);
        break;
    case 4: GenerarDialogosNivel4(npc);
        break;
    default: GenerarDialogosNivel5(npc);
        break;
    }
}

void GeneradorNPC::GenerarDialogosNivel1(NPC *info)
{
    // En esta etapa solo los revolucionarios y los refugiados tendran dialogos
    if (info->getTipo() == 3)
        SortearDialogo(info, DialogosRevolucionario, topeDialogosRev);
    else
        if (info->getTipo() == 1)
            SortearDialogo(info, DialogosRefugiado, topeDialogosRef);
}

void GeneradorNPC::GenerarDialogosNivel2(NPC *info)
{
    GenerarDialogosNivel1(info);
    Estancia * infoEstancia = info->getEstancia();

    QString TipoEstancia = infoEstancia->getTipoEstancia();
    QString * DialogosSegunTipo = nullptr; int TopeDialogos, tipoEst = 1;

    // Decidimos que tipo es el NPC
    if (TipoEstancia == "Turismo"){
        tipoEst = 1;
        DialogosSegunTipo = obtenerTipoEstancia(tipoEst, TopeDialogos);

    } else if (TipoEstancia == "Trabajo") {
        tipoEst = 2;
        DialogosSegunTipo = obtenerTipoEstancia(tipoEst, TopeDialogos);

    }   else if (TipoEstancia == "Estudios") {
        tipoEst = 3;
        DialogosSegunTipo = obtenerTipoEstancia(tipoEst, TopeDialogos);
    }

    if (info->getValidez()){
        SortearDialogo(info, DialogosSegunTipo, TopeDialogos);
    } else {
        // Obtenemos un dialogo de otro tipo de estancia
        int DialogoDiferente = Random->bounded(4) + 1;
        while (DialogoDiferente == tipoEst)
            DialogoDiferente = Random->bounded(4) + 1;

        DialogosSegunTipo = obtenerTipoEstancia(DialogoDiferente, TopeDialogos);
        SortearDialogo(info, DialogosSegunTipo, TopeDialogos);
    }
    // Dialogos segun estancia

}

void GeneradorNPC::GenerarDialogosNivel3(NPC *info)
{
    GenerarDialogosNivel2(info);
    QString dialogo;
    bool validez = info->getListaAcompaniantes()->getValidez();
    int CantidadAcompaniantes = info->getListaAcompaniantes()->getCantAcompaniantes();

    if (validez) { // si el documento es valido.. genero dialogos validos
        dialogo = dialogosAcomps[CantidadAcompaniantes];
        info->setDialogo(dialogo);
    } else { // genero dialogos invalidos
        dialogo = generarDialogosAcomps(CantidadAcompaniantes);
        info->setDialogo(dialogo);
    }
}

QString GeneradorNPC::generarDialogosAcomps(int CantidadRealAcomp)
{
    int sorteo = Random->bounded(topeDialogosAcomp);
    while(sorteo == CantidadRealAcomp)
        sorteo = Random->bounded(topeDialogosAcomp);

    return dialogosAcomps[sorteo];
}

void GeneradorNPC::GenerarDialogosNivel4(NPC *info)
{
    GenerarDialogosNivel1(info);
}

void GeneradorNPC::GenerarDialogosNivel5(NPC *info)
{
    GenerarDialogosNivel1(info);
}

void GeneradorNPC::SortearDialogo(NPC *info, QString * dialogos, int &tope)
{
    int sorteo = Random->bounded(tope);
    QString dialogo = dialogos[sorteo] + "\n";
    info->setDialogo(dialogo);
}

QString *GeneradorNPC::obtenerTipoEstancia(int tipo, int &tope)
{
    if (tipo == 1){
        tope = topeDialogosTurista;
        return DialogosTurista;
    } else if (tipo == 2) {
        tope = topeDialogosTrabajador;
        return DialogosTrabajador;
    } else if (tipo == 3) {
        tope = topeDialogosEstudiante;
        return DialogosEstudiante;
    }

    return nullptr;
}
/// ################# GETTERS ##########################
QString GeneradorNPC::getCaraRandom(char genero)
{
    int CaraGeneroX = Random->bounded(10);
    int sorteo = Random->bounded(topeLinksCaras);
    QString LinkCara;

    // Chance 50/50 de que use de mujer o de hombre.
    bool Cara2Usar = (CaraGeneroX < 5);

    if (genero == 'M' || (genero == 'X' && Cara2Usar))
        LinkCara = LinksCarasMujer[sorteo];
    else
        LinkCara = LinksCarasHombre[sorteo];

    return LinkCara;

}

QString GeneradorNPC::getCaraRevolucionarioRandom()
{
    int sorteo = Random->bounded(topeLinksRevolucionario);
    QString LinkCara = LinksCarasRevolucionario[sorteo];

    return LinkCara;
}

QString GeneradorNPC::getCaraRefugiadoRandom(char Genero)
{
    int CaraGeneroX = Random->bounded(10);
    int sorteo = Random->bounded(topeLinksRefugiado);
    QString LinkCara;

    // Chance 50/50 de que use de mujer o de hombre.
    bool Cara2Usar = (CaraGeneroX < 5);

    if (Genero == 'M' || (Genero == 'X' && Cara2Usar))
        LinkCara = LinksCarasRefugiadoMujer[sorteo];
    else
        LinkCara = LinksCarasRefugiadoHombre[sorteo];

    return LinkCara;
}

QString GeneradorNPC::getCejasRandom()
{
    int sorteo = Random->bounded(topeLinksCejas);
    return LinksCejas[sorteo];
}

QString GeneradorNPC::getOjosRandom()
{
    int sorteo = Random->bounded(topeLinksOjos);
    return LinksOjos[sorteo];
}

QString GeneradorNPC::getBocaRandom()
{
    int sorteo = Random->bounded(topeLinksBocas);
    return LinksBocas[sorteo];
}

QString GeneradorNPC::getNarizRandom()
{
    int sorteo = Random->bounded(topeLinksNariz);
    return LinksNariz[sorteo];
}

QString GeneradorNPC::getBarbaRandom()
{
    int sorteo = Random->bounded(topeLinksBarbas);
    return LinksBarbas[sorteo];
}

