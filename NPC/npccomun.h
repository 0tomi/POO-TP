#ifndef NPCCOMUN_H
#define NPCCOMUN_H
#include "npc.h"
#include <QString>

class NPCcomun: public NPC
{
public:
    NPCcomun(char Genero, char Tipo, bool Validez);

    QString getCaraURL() const;
    void setCaraURL(const QString &newCaraURL);

    QString getCejasURL() const;
    void setCejasURL(const QString &newCejasURL);

    QString getOjosURL() const;
    void setOjosURL(const QString &newOjosURL);

    QString getBocaURL() const;
    void setBocaURL(const QString &newBocaURL);

    QString getNarizURL() const;
    void setNarizURL(const QString &newNarizURL);

    QString getBarbaURL() const;
    void setBarbaURL(const QString &newBarbaURL);

private:
    QString CaraURL;
    QString CejasURL;
    QString OjosURL;
    QString BocaURL;
    QString NarizURL;
    QString BarbaURL;
};

#endif // NPCCOMUN_H
