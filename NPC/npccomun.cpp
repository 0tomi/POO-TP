#include "npccomun.h"

NPCcomun::NPCcomun(char newGenero, char newTipo, bool Validez): NPC(newGenero, newTipo, Validez) {

}

Skin NPCcomun::getSkin() const
{
    return skin;
}

void NPCcomun::setSkin(const Skin &newSkin)
{
    skin = newSkin;
}

Skin NPCcomun::getSkinDocs() const
{
    return skinDocs;
}

void NPCcomun::setSkinDocs(const Skin &newSkinDocs)
{
    skinDocs = newSkinDocs;
}




