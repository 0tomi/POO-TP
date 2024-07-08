#include "generadornpc.h"
#include "generadornpc.h"
#include "../lectorarchivos.h"
#include <stdlib.h>
#include <ctime>
#include <QDebug>

GeneradorNPC::GeneradorNPC(){
    // # Deus ignoscat factis quae mox faciam. #
    Random = new QRandomGenerator(time(NULL));

    LectorArchivos lector("../TP2/ArchivosTexto/URLCarasHombre.txt");
    LinksCarasHombre = lector.getArray();
    topeLinksCaras = lector.getTopeArray();

    lector.LeerArchivoNuevo("../TP2/ArchivosTexto/URLCarasMujer.txt");
    LinksCarasMujer = lector.getArray();

    lector.LeerArchivoNuevo("../TP2/ArchivosTexto/URLBarbas.txt");
    LinksBarbas = lector.getArray();
    topeLinksBarbas = lector.getTopeArray();

    lector.LeerArchivoNuevo("../TP2/ArchivosTexto/URLOjos.txt");
    LinksOjos = lector.getArray();
    topeLinksOjos = lector.getTopeArray();

    lector.LeerArchivoNuevo("../TP2/ArchivosTexto/URLBocas.txt");
    LinksBocas = lector.getArray();
    topeLinksBocas = lector.getTopeArray();

    lector.LeerArchivoNuevo("../TP2/ArchivosTexto/URLCejas.txt");
    LinksCejas = lector.getArray();
    topeLinksCejas = lector.getTopeArray();

    lector.LeerArchivoNuevo("../TP2/ArchivosTexto/URLNariz.txt");
    LinksNariz = lector.getArray();
    topeLinksNariz = lector.getTopeArray();

}


// Esto necesita rework a futuro para distinguir entre caras de Mujeres y Hombres
NPC* GeneradorNPC::getNPCgenerico(int tipo, bool Validez){
    NPCcomun* NPCaCrear;

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

    string ojos = getOjosRandom();

    // Resto del cuerpo
    NPCaCrear->setCaraURL(getCaraRandom(generos[valorCentinela2]));
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

string GeneradorNPC::getCaraRandom(char genero)
{
    int CaraGeneroX = Random->bounded(10);
    int sorteo = Random->bounded(topeLinksCaras);
    string LinkCara;

    // Chance 50/50 de que use de mujer o de hombre.
    bool Cara2Usar = (CaraGeneroX < 5);

    if (genero == 'M' || (genero == 'X' && Cara2Usar))
        LinkCara = LinksCarasMujer[sorteo];
    else
        LinkCara = LinksCarasHombre[sorteo];

    return LinkCara;

}

string GeneradorNPC::getCejasRandom()
{
    int sorteo = Random->bounded(topeLinksCejas);
    return LinksCejas[sorteo];
}

string GeneradorNPC::getOjosRandom()
{
    int sorteo = Random->bounded(topeLinksOjos);
    return LinksOjos[sorteo];
}

string GeneradorNPC::getBocaRandom()
{
    int sorteo = Random->bounded(topeLinksBocas);
    return LinksBocas[sorteo];
}

string GeneradorNPC::getNarizRandom()
{
    int sorteo = Random->bounded(topeLinksNariz);
    return LinksNariz[sorteo];
}

string GeneradorNPC::getBarbaRandom()
{
    int sorteo = Random->bounded(topeLinksBarbas);
    return LinksBarbas[sorteo];
}
