#include "generadornpc.h"
#include "generadornpc.h"
#include "../lectorarchivos.h"
#include <stdlib.h>
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
    if (valorCentinela2 > 0){
        int TendraBarba = Random->bounded(10);
        if (TendraBarba < 5 && valorCentinela2 == 1)
            NPCaCrear->setBarbaURL(getBarbaRandom());
        if (TendraBarba < 3 && valorCentinela2 == 2)
            NPCaCrear->setBarbaURL(getBarbaRandom());
    }

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

void GeneradorNPC::GenerarDialogosNivel1(NPC *info)
{
    if (info->getTipo() != 3)    // En esta etapa solo los revolucionarios tendran dialogos
        return;

    int sorteo = Random->bounded(topeDialogosRev);
    info->setDialogo(DialogosRevolucionario[sorteo]);
}

void GeneradorNPC::GenerarDialogosNivel2(NPC *info)
{

}

void GeneradorNPC::GenerarDialogosNivel3(NPC *info)
{

}

void GeneradorNPC::GenerarDialogosNivel4(NPC *info)
{

}

void GeneradorNPC::GenerarDialogosNivel5(NPC *info)
{

}
