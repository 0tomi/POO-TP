#include "npccomun.h"

NPCcomun::NPCcomun(char newGenero, char newTipo, bool Validez): NPC(newGenero, newTipo, Validez) {
    this->BarbaURL = "no";
}

QString NPCcomun::getCaraURL() const
{
    return CaraURL;
}

void NPCcomun::setCaraURL(const string &newCaraURL)
{
    CaraURL = QString::fromStdString(newCaraURL);
}

QString NPCcomun::getCejasURL() const
{
    return CejasURL;
}

void NPCcomun::setCejasURL(const string &newCejasURL)
{
    CejasURL = QString::fromStdString(newCejasURL);
}

QString NPCcomun::getOjosURL() const
{
    return OjosURL;
}

void NPCcomun::setOjosURL(const string &newOjosURL)
{
    OjosURL = QString::fromStdString(newOjosURL);
}

QString NPCcomun::getBocaURL() const
{
    return BocaURL;
}

void NPCcomun::setBocaURL(const string &newBocaURL)
{
    BocaURL = QString::fromStdString(newBocaURL);
}

QString NPCcomun::getNarizURL() const
{
    return NarizURL;
}

void NPCcomun::setNarizURL(const string &newNarizURL)
{
    NarizURL = QString::fromStdString(newNarizURL);
}

QString NPCcomun::getBarbaURL() const
{
    return BarbaURL;
}

void NPCcomun::setBarbaURL(const string &newBarbaURL)
{
    BarbaURL = QString::fromStdString(newBarbaURL);
}
