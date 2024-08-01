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

    Skin getSkinDocs() const;
    void setSkinDocs(const Skin &newSkinDocs);

private:
    Skin skin;
    Skin skinDocs;
};

#endif // NPCCOMUN_H
