#include "../NPC/NPC.h"

#ifndef GENNPC_H
#define GENNPC_H

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
    int topeImagenes;
    char generos[3] = {'M', 'H', 'X'};
};

#endif // !GENNPC_H
