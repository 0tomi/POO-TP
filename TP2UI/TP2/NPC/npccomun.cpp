#include "npccomun.h"

NPCcomun::NPCcomun(char newGenero, char newTipo): NPC(newGenero, newTipo) {
    this->BarbaURL = "no";
}

string NPCcomun::getCaraURL() const
{
    return CaraURL;
}

void NPCcomun::setCaraURL(const string &newCaraURL)
{
    CaraURL = newCaraURL;
}

string NPCcomun::getCejasURL() const
{
    return CejasURL;
}

void NPCcomun::setCejasURL(const string &newCejasURL)
{
    CejasURL = newCejasURL;
}

string NPCcomun::getOjosURL() const
{
    return OjosURL;
}

void NPCcomun::setOjosURL(const string &newOjosURL)
{
    OjosURL = newOjosURL;
}

string NPCcomun::getBocaURL() const
{
    return BocaURL;
}

void NPCcomun::setBocaURL(const string &newBocaURL)
{
    BocaURL = newBocaURL;
}

string NPCcomun::getNarizURL() const
{
    return NarizURL;
}

void NPCcomun::setNarizURL(const string &newNarizURL)
{
    NarizURL = newNarizURL;
}

string NPCcomun::getBarbaURL() const
{
    return BarbaURL;
}

void NPCcomun::setBarbaURL(const string &newBarbaURL)
{
    BarbaURL = newBarbaURL;
}
