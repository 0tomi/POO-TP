#include "generadornpc.h"
#include "generadornpc.h"
#include "../lectorarchivos.h"
#include <stdlib.h>

GeneradorNPC::GeneradorNPC(){
    // # Deus ignoscat factis quae mox faciam. #

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

    lector.LeerArchivoNuevo("../TP2/ArchivosTexto/URLCaras.txt");
    LinksCejas = lector.getArray();
    topeLinksCejas = lector.getTopeArray();

    lector.LeerArchivoNuevo("../TP2/ArchivosTexto/URLCaras.txt");
    LinksNariz = lector.getArray();
    topeLinksNariz = lector.getTopeArray();
}


// Esto necesita rework a futuro para distinguir entre caras de Mujeres y Hombres
NPC* GeneradorNPC::getNPCgenerico(char tipo){
    NPCcomun* NPCaCrear;
    srand(1); // luego esto hay que cambiarlo por time null

    if (tipo > 3)
        tipo = rand()%4;

    // Pickeamos un genero
    int valorCentinela2 = rand()%3;

    // Generamos NPC con los datos basicos
    NPCaCrear = new NPCcomun(this->generos[valorCentinela2], tipo);

    // si es hombre o X
    if (valorCentinela2 > 0){
        int TendraBarba = rand()%10;
        if (TendraBarba < 5 && valorCentinela2 == 1)
            NPCaCrear->setBarbaURL(getBarbaRandom());
        if (TendraBarba < 3 && valorCentinela2 == 2)
            NPCaCrear->setBarbaURL(getBarbaRandom());
    }

    // Resto del cuerpo
    NPCaCrear->setCaraURL(getCaraRandom(generos[valorCentinela2]));
    NPCaCrear->setCejasURL(getCejasRandom());
    NPCaCrear->setOjosURL(getOjosRandom());
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
    int CaraGeneroX = rand()% 10;
    int sorteo = rand()% topeLinksCaras;
    string LinkCara;

    // Chance 50/50 de que use de mujer o de hombre.
    bool Cara2Usar = (CaraGeneroX < 5);

    if (genero == 'M' || Cara2Usar)
        LinkCara = LinksCarasMujer[sorteo];
    else
        LinkCara = LinksCarasHombre[sorteo];

    return LinkCara;

}

string GeneradorNPC::getCejasRandom()
{
    int sorteo = rand() % topeLinksCejas;
    return LinksCejas[sorteo];
}

string GeneradorNPC::getOjosRandom()
{
    int sorteo = rand() % topeLinksOjos;
    return LinksOjos[sorteo];
}

string GeneradorNPC::getBocaRandom()
{
    int sorteo = rand() % topeLinksBocas;
    return LinksBocas[sorteo];
}

string GeneradorNPC::getNarizRandom()
{
    int sorteo = rand() % topeLinksNariz;
    return LinksNariz[sorteo];
}

string GeneradorNPC::getBarbaRandom()
{
    int sorteo = rand() % topeLinksBarbas;
    return LinksBarbas[sorteo];
}
