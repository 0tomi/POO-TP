#ifndef GENERADORSKIN_H
#define GENERADORSKIN_H
#include <QString>
#include <QRandomGenerator>
#include "../NPC/skin.h"
#include "../lectorarchivos.h"

class GeneradorSkin
{
public:
    void setSeed(quint32 seed);
    GeneradorSkin(QRandomGenerator * generador);
    ~GeneradorSkin();
    Skin getSkin(int TipoNPC, char Genero);
    Skin getSimilarSkin(Skin skinActual, char Genero, int nivel);
private:
    LectorArchivos lector;
    QRandomGenerator * qrand;
    QString pickSkinConGenero(QString * listaSkins[], int topeSkins, char Genero);
    QString pickSkin(QString * listaSkins, int topeSkins);

    // ArrayS con direcciones donde se encuentran las caras de los npcs
    QString LinksGorro[4] = {
        ":/Resources/NPCs/Gorro1.png", ":/Resources/NPCs/Gorro2.png", ":/Resources/NPCs/Gorro3.png", ":/Resources/NPCs/Gorro4.png"
    };
    QString * LinksPelo[2];
    QString* LinksCaras;     // Hombre y Mujer
    QString* LinksCarasRevolucionario;
    QString* LinksCarasRefugiado; // Hombre y Mujer
    QString* LinksCejas;
    QString* LinksOjos;
    QString* LinksBocas;
    QString* LinksNariz;
    QString* LinksBarbas;

    int topeLinksGorro = 4;
    int topeLinksPelo;
    int topeLinksCaras;
    int topeLinksRevolucionario;
    int topeLinksRefugiado;
    int topeLinksCejas;
    int topeLinksOjos;
    int topeLinksBocas;
    int topeLinksNariz;
    int topeLinksBarbas;
};

#endif // GENERADORSKIN_H
