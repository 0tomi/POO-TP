#ifndef GENERADORNPC_H
#define GENERADORNPC_H

#include "../NPC/npccomun.h"
#include <string>
#include <QRandomGenerator>
#include <QString>

using namespace std;

class GeneradorNPC{
public:
    GeneradorNPC();
    NPC* getNPCgenerico(int tipo , bool Validez);
    NPC *getSimilarNPC(NPC* ejemplo);

    ~GeneradorNPC();
private:
    // Generador de Numeros
    QRandomGenerator* Random;

    // NPC que se va a generar
    NPC* NPC2create;

    // Metodos par armar las selecciones random
    QString getCaraRandom(char Genero);
    QString getCaraRevolucionarioRandom();
    QString getCaraRefugiadoRandom(char Genero);
    QString getCejasRandom();
    QString getOjosRandom();
    QString getBocaRandom();
    QString getNarizRandom();
    QString getBarbaRandom();

    // ArrayS con direcciones donde se encuentran las caras de los npcs
    QString* LinksCarasHombre;
    QString* LinksCarasMujer;
    int topeLinksCaras;

    QString* LinksCarasRevolucionario;
    int topeLinksRevolucionario;

    QString* LinksCarasRefugiadoHombre;
    QString* LinksCarasRefugiadoMujer;
    int topeLinksRefugiado;


    QString* LinksCejas;
    int topeLinksCejas;

    QString* LinksOjos;
    int topeLinksOjos;

    QString* LinksBocas;
    int topeLinksBocas;

    QString* LinksNariz;
    int topeLinksNariz;

    QString* LinksBarbas;
    int topeLinksBarbas;

    char generos[3] = {'M', 'H', 'X'};
};

#endif // GENERADORNPC_H
