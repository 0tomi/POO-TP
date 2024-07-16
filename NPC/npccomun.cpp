#include "npccomun.h"

NPCcomun::NPCcomun(char newGenero, char newTipo, bool Validez): NPC(newGenero, newTipo, Validez) {
    this->BarbaURL = "no";
}

QString NPCcomun::getCaraURL() const
{
    return CaraURL;
}

void NPCcomun::setCaraURL(const QString &newCaraURL)
{
    CaraURL = newCaraURL;
}

QString NPCcomun::getCejasURL() const
{
    return CejasURL;
}

void NPCcomun::setCejasURL(const QString &newCejasURL)
{
    CejasURL = newCejasURL;
}

QString NPCcomun::getOjosURL() const
{
    return OjosURL;
}

void NPCcomun::setOjosURL(const QString &newOjosURL)
{
    OjosURL = newOjosURL;
}

QString NPCcomun::getBocaURL() const
{
    return BocaURL;
}

void NPCcomun::setBocaURL(const QString &newBocaURL)
{
    BocaURL = newBocaURL;
}

QString NPCcomun::getNarizURL() const
{
    return NarizURL;
}

void NPCcomun::setNarizURL(const QString &newNarizURL)
{
    NarizURL = newNarizURL;
}

QString NPCcomun::getBarbaURL() const
{
    return BarbaURL;
}

void NPCcomun::setBarbaURL(const QString &newBarbaURL)
{
    BarbaURL = newBarbaURL;
}
