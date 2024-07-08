#ifndef GENERADORNPC_H
#define GENERADORNPC_H

#include "../NPC/npccomun.h"
#include <string>
#include <QRandomGenerator>
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
    string getCaraRandom(char Genero);
    string getCejasRandom();
    string getOjosRandom();
    string getBocaRandom();
    string getNarizRandom();
    string getBarbaRandom();

    // ArrayS con direcciones donde se encuentran las caras de los npcs
    string* LinksCarasHombre;
    string* LinksCarasMujer;
    int topeLinksCaras;

    string* LinksCejas;
    int topeLinksCejas;

    string* LinksOjos;
    int topeLinksOjos;

    string* LinksBocas;
    int topeLinksBocas;

    string* LinksNariz;
    int topeLinksNariz;

    string* LinksBarbas;
    int topeLinksBarbas;

    char generos[3] = {'M', 'H', 'X'};
};

#endif // GENERADORNPC_H
