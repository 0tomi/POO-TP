#ifndef NPCCOMUN_H
#define NPCCOMUN_H
#include "npc.h"
#include "skin.h"
#include <QString>

class NPCcomun: public NPC
{
public:
    NPCcomun(char Genero, char Tipo, bool Validez);

    Skin getSkin() const;
    void setSkin(const Skin &newSkin);

private:
    Skin skin;
};

#endif // NPCCOMUN_H
