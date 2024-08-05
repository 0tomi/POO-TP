#include "skin.h"

Skin::Skin() {}

Skin::~Skin()
{
    pelo = cara = boca = cejas = ojos = nariz = "";
}

QString Skin::getCaraURL() const
{
    return cara;
}

void Skin::setCara(const QString &newCara)
{
    cara = newCara;
}

QString Skin::getCejasURL() const
{
    return cejas;
}

void Skin::setCejas(const QString &newCejas)
{
    cejas = newCejas;
}

QString Skin::getOjosURL() const
{
    return ojos;
}

void Skin::setOjos(const QString &newOjos)
{
    ojos = newOjos;
}

QString Skin::getNarizURL() const
{
    return nariz;
}

void Skin::setNariz(const QString &newNariz)
{
    nariz = newNariz;
}

QString Skin::getBocaURL() const
{
    return boca;
}

void Skin::setBoca(const QString &newBoca)
{
    boca = newBoca;
}

QString Skin::getPelo() const
{
    return pelo;
}

void Skin::setPelo(const QString &newPelo)
{
    pelo = newPelo;
}

QString Skin::getGorro() const
{
    return gorro;
}

void Skin::setGorro(const QString &newGorro)
{
    gorro = newGorro;
}
