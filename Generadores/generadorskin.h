#ifndef GENERADORSKIN_H
#define GENERADORSKIN_H
#include <QString>
#include <QRandomGenerator>
#include "../NPC/skin.h"
#include "../lectorarchivos.h"

class GeneradorSkin
{
public:
    GeneradorSkin(QRandomGenerator * generador);
    ~GeneradorSkin();
    Skin getSkin(int TipoNPC, char Genero);
    Skin getSimilarSkin(Skin skinActual, char Genero, int nivel);
private:
    LectorArchivos lector;
    QRandomGenerator * qrand;
    QString pickCuerpo(QString * listaSkins[], int topeSkins, char Genero);
    QString pickSkin(QString * listaSkins, int topeSkins);

    // ArrayS con direcciones donde se encuentran las caras de los npcs
    QString* LinksCaras[2];     // Hombre y Mujer
    QString* LinksCarasRevolucionario;
    QString* LinksCarasRefugiado[2]; // Hombre y Mujer
    QString* LinksCejas;
    QString* LinksOjos;
    QString* LinksBocas;
    QString* LinksNariz;
    QString* LinksBarbas;

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
