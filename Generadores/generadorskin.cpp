#include "generadorskin.h"
#include <QDebug>

void GeneradorSkin::setSeed(quint32 seed)
{
    this->qrand->seed(seed);
}


GeneradorSkin::GeneradorSkin(QRandomGenerator *generador): lector(":/Resources/ArchivosTexto/URLCaras.txt")
{
    // Colocamos el generador
    qrand = generador;

    // Lectura de las partes del cuerpo
    LinksCaras = lector.getArray();
    topeLinksCaras = lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLPeloH.txt");
    QString * LinksPeloHombre = lector.getArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLPeloM.txt");
    QString * LinksPeloM = lector.getArray();
    topeLinksPelo = lector.getTopeArray();

    LinksPelo[0] = LinksPeloHombre;
    LinksPelo[1] = LinksPeloM;

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLCarasRevolucionario.txt");
    LinksCarasRevolucionario = lector.getArray();
    topeLinksRevolucionario = lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLCarasRefugiado.txt");
    LinksCarasRefugiado = lector.getArray();
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
}

GeneradorSkin::~GeneradorSkin()
{
    // No hay nada por ahora que deletear
}

Skin GeneradorSkin::getSkin(int TipoNPC, char Genero)
{
    Skin newSkin;

    int sorteo = qrand->bounded(15);

    switch(TipoNPC){
    case 1: // Refugiado
        newSkin.setCara(pickSkin(LinksCarasRefugiado, topeLinksRefugiado));
        break;
    case 3: // Revolucionario
        newSkin.setCara(pickSkin(LinksCarasRevolucionario, topeLinksRevolucionario));
        break;
    default:
        newSkin.setCara(pickSkin(LinksCaras, topeLinksCaras));
        break;
    }

    if (sorteo < 2 || TipoNPC == 1)
        newSkin.setGorro(pickSkin(LinksGorro, topeLinksGorro));

    newSkin.setPelo(pickSkinConGenero(LinksPelo, topeLinksPelo, Genero));
    newSkin.setCejas(pickSkin(LinksCejas, topeLinksCejas));
    newSkin.setOjos(pickSkin(LinksOjos, topeLinksOjos));
    newSkin.setNariz(pickSkin(LinksNariz, topeLinksNariz));
    newSkin.setBoca(pickSkin(LinksBocas, topeLinksBocas));

    return newSkin;
}

// En desarrollo
Skin GeneradorSkin::getSimilarSkin(Skin SkinActual, char Genero, int nivel)
{
    Skin newSkin;
    newSkin = SkinActual;

    int Facciones;
    int sorteo;

    switch(nivel){
    case 1: Facciones = 3;
        break;
    case 2: Facciones = 3;
        break;
    case 3: Facciones = 2;
        break;
    case 4: Facciones = 2;
        break;
    default: Facciones = 1;
        break;
    }

    while (Facciones){
        sorteo = qrand->bounded(20);
        if (sorteo > 17)
            newSkin.setCara(pickSkin(this->LinksCaras, this->topeLinksCaras));
        else{
            sorteo = qrand->bounded(6);
            switch (sorteo){
            case 0: newSkin.setPelo(pickSkinConGenero(this->LinksPelo, this->topeLinksPelo, Genero));
                break;
            case 1: newSkin.setBoca(pickSkin(LinksBocas, topeLinksBocas));
                break;
            case 2: newSkin.setNariz(pickSkin(LinksNariz, topeLinksNariz));
                break;
            case 3: newSkin.setOjos(pickSkin(LinksOjos, topeLinksOjos));
                break;
            case 4: newSkin.setCejas(pickSkin(LinksCejas, topeLinksCejas));
                break;
            }
        }

        Facciones--;
    }

    return newSkin;
}

QString GeneradorSkin::pickSkinConGenero(QString * listaSkins[], int topeSkins, char Genero)
{
    int CaraGeneroX = qrand->bounded(10);
    int sorteo = qrand->bounded(topeSkins);
    QString LinkCara;

    // Chance 50/50 de que use de mujer o de hombre.
    bool Cara2Usar = (CaraGeneroX < 5);

    if (Genero == 'M' || (Genero == 'X' && Cara2Usar))
        LinkCara = listaSkins[1][sorteo];
    else
        LinkCara = listaSkins[0][sorteo];

    return LinkCara;
}

QString GeneradorSkin::pickSkin(QString *listaSkins, int topeSkins)
{
    int sorteo = qrand->bounded(topeSkins);
    return listaSkins[sorteo];
}
