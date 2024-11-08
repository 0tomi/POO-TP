#include "generadorskin.h"
#include <QDebug>
#include <QPixmap>

void GeneradorSkin::setSeed(quint32 seed)
{
    this->qrand->seed(seed);
    this->randomCuerpos.seed(seed);
}


GeneradorSkin::GeneradorSkin(QRandomGenerator *generador)
{
    // Colocamos el generador
    qrand = generador;

    // Lectura de las partes del cuerpo
    LeerImagenes(LinksCaras, ":/Resources/NPCs/Cuerpo");
    LeerImagenes(LinksPelo[0], ":/Resources/NPCs/PeloH");
    LeerImagenes(LinksPelo[1], ":/Resources/NPCs/PeloM");
    LeerImagenes(LinksCarasRevolucionario, ":/Resources/NPCs/RevolucionarioCuerpo");
    LeerImagenes(LinksCarasRefugiado, ":/Resources/NPCs/CuerpoRefugiado");
    LeerImagenes(LinksBarbas, ":/Resources/Barba");
    LeerImagenes(LinksOjos, ":/Resources/NPCs/Ojos");
    LeerImagenes(LinksBocas, ":/Resources/NPCs/Boca");
    LeerImagenes(LinksCejas, ":/Resources/NPCs/Cejas");
    LeerImagenes(LinksNariz, ":/Resources/NPCs/Nariz");
    LeerImagenes(LinksGorro, ":/Resources/NPCs/Gorro");
}

void GeneradorSkin::LeerImagenes(vector <QString> &Links, QString RutaGenerica)
{
    QPixmap CargadorImagenes;
    QString ruta; int Contador = 1;
    ruta = RutaGenerica + QString::number(Contador) + ".png";
    CargadorImagenes.load(ruta);
    while (!CargadorImagenes.isNull()){
        Links.push_back(ruta);
        ruta = RutaGenerica + QString::number(++Contador) + ".png";
        CargadorImagenes.load(ruta);
    }
}

GeneradorSkin::~GeneradorSkin()
{

}

void GeneradorSkin::Inicializar(int Nivel, int Dificultad)
{
    this->dificultad = Dificultad;
    this->nivel = Nivel;
}

Skin GeneradorSkin::getSkin(int TipoNPC, char Genero)
{
    Skin newSkin;

    int sorteo = qrand->bounded(15);

    switch(TipoNPC){
    case 1: // Refugiado
        newSkin.setCara(pickCuerpo(LinksCarasRefugiado));
        break;
    case 3: // Revolucionario
        if (nivel > 3 || dificultad == 3)
            newSkin.setCara(pickCuerpo(LinksCarasRevolucionario));
        else newSkin.setCara(pickCuerpo(LinksCarasRevolucionario, 10));
        break;
    default:
        newSkin.setCara(pickCuerpo(LinksCaras));
        break;
    }

    if (sorteo < 2 || TipoNPC == 1)
        newSkin.setGorro(pickSkin(LinksGorro));

    newSkin.setPelo(pickSkinConGenero(LinksPelo, Genero));
    newSkin.setCejas(pickSkin(LinksCejas));
    newSkin.setOjos(pickSkin(LinksOjos));
    newSkin.setNariz(pickSkin(LinksNariz));
    newSkin.setBoca(pickSkin(LinksBocas));

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
            newSkin.setCara(pickSkin(this->LinksCaras));
        else{
            sorteo = qrand->bounded(6);
            switch (sorteo){
            case 0: newSkin.setPelo(pickSkinConGenero(this->LinksPelo, Genero));
                break;
            case 1: newSkin.setBoca(pickSkin(LinksBocas));
                break;
            case 2: newSkin.setNariz(pickSkin(LinksNariz));
                break;
            case 3: newSkin.setOjos(pickSkin(LinksOjos));
                break;
            case 4: newSkin.setCejas(pickSkin(LinksCejas));
                break;
            }
        }

        Facciones--;
    }

    return newSkin;
}

QString GeneradorSkin::pickSkinConGenero(vector <QString> listaSkins[], char Genero)
{
    int CaraGeneroX = qrand->bounded(10);
    int sorteo = qrand->bounded(listaSkins[0].size());
    QString LinkCara;

    // Chance 50/50 de que use de mujer o de hombre.
    bool Cara2Usar = (CaraGeneroX < 5);

    if (Genero == 'M' || (Genero == 'X' && Cara2Usar))
        LinkCara = listaSkins[1][sorteo];
    else
        LinkCara = listaSkins[0][sorteo];

    return LinkCara;
}

QString GeneradorSkin::pickSkin(vector <QString> &listaSkins)
{
    // Generamos algunos numeros aleatorios para mejorar la aleateoridad
    for (int i = 0; i < 20; i++)
        qrand->bounded(listaSkins.size());

    int sorteo = qrand->bounded(listaSkins.size());
    return listaSkins[sorteo];
}

QString GeneradorSkin::pickCuerpo(vector<QString> &listaSkins, int max)
{
    // Generamos algunos numeros aleatorios para mejorar la aleateoridad
    for (int i = 0; i < 40; i++)
        randomCuerpos.bounded(max);

    int sorteo = randomCuerpos.bounded(max);
    return listaSkins[sorteo];
}

QString GeneradorSkin::pickCuerpo(vector<QString> &listaSkins)
{
    // Generamos algunos numeros aleatorios para mejorar la aleateoridad
    for (int i = 0; i < 20; i++)
        randomCuerpos.bounded(listaSkins.size());

    int sorteo = randomCuerpos.bounded(listaSkins.size());
    return listaSkins[sorteo];
}
