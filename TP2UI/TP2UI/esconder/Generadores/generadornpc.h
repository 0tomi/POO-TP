#ifndef GENERADORNPC_H
#define GENERADORNPC_H

#include "../NPC/npc.h"
#include <string>
using namespace std;

class GeneradorNPC{
public:
    GeneradorNPC();
    NPC* getNPC();
private:
    // NPC que se va a generar
    NPC* NPC2create;

    // Array con direcciones donde se encuentran las caras de los npcs
    string* LinksImagenesNPCS;
    int topeLinksImagenes;
    char generos[3] = {'M', 'H', 'X'};
};

#endif // GENERADORNPC_H
