#include "generadorskin.h"

GeneradorSkin::GeneradorSkin(QRandomGenerator *generador): lector(":/Resources/ArchivosTexto/URLCarasHombre.txt")
{
    // Colocamos el generador
    qrand = generador;

    // Lectura de las partes del cuerpo
    QString * LinksCarasHombre = lector.getArray();
    topeLinksCaras = lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLCarasMujer.txt");
    QString * LinksCarasMujer = lector.getArray();

    LinksCaras[0] = LinksCarasHombre;
    LinksCaras[1] = LinksCarasMujer;

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLCarasRevolucionario.txt");
    LinksCarasRevolucionario = lector.getArray();
    topeLinksRevolucionario = lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLCarasRefugiadoHombre.txt");
    QString * LinksCarasRefugiadoHombre = lector.getArray();

    lector.LeerArchivoNuevo(":/Resources/ArchivosTexto/URLCarasRefugiadoMujer.txt");
    QString * LinksCarasRefugiadoMujer = lector.getArray();
    topeLinksRefugiado = lector.getTopeArray();

    LinksCarasRefugiado[0] = LinksCarasRefugiadoHombre;
    LinksCarasRefugiado[1] = LinksCarasRefugiadoMujer;

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

    switch(TipoNPC){
    case 1: // Refugiado
        newSkin.setCara(pickCuerpo(LinksCarasRefugiado, topeLinksRefugiado, Genero));
        break;
    case 3: // Revolucionario
        newSkin.setCara(pickSkin(LinksCarasRevolucionario, topeLinksRevolucionario));
        break;
    default:
        newSkin.setCara(pickCuerpo(LinksCaras, topeLinksCaras, Genero));
        break;
    }

    newSkin.setCejas(pickSkin(LinksCejas, topeLinksCejas));
    newSkin.setOjos(pickSkin(LinksOjos, topeLinksOjos));
    newSkin.setNariz(pickSkin(LinksNariz, topeLinksNariz));
    newSkin.setBoca(pickSkin(LinksBocas, topeLinksBocas));

    return newSkin;
}

// En desarrollo
Skin GeneradorSkin::getSimilarSkin(Skin SkinActual, char Genero, int nivel)
{
    /* int Facciones;       En proceso pa dsps
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
    } */

    return getSkin(qrand->bounded(4), Genero);
}

QString GeneradorSkin::pickCuerpo(QString * listaSkins[], int topeSkins, char Genero)
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
