#ifndef NPCCOMUN_H
#define NPCCOMUN_H
#include "npc.h"
#include <QString>

class NPCcomun: public NPC
{
public:
    NPCcomun(char Genero, char Tipo, bool Validez);

    QString getCaraURL() const;
    void setCaraURL(const string &newCaraURL);

    QString getCejasURL() const;
    void setCejasURL(const string &newCejasURL);

    QString getOjosURL() const;
    void setOjosURL(const string &newOjosURL);

    QString getBocaURL() const;
    void setBocaURL(const string &newBocaURL);

    QString getNarizURL() const;
    void setNarizURL(const string &newNarizURL);

    QString getBarbaURL() const;
    void setBarbaURL(const string &newBarbaURL);

private:
    QString CaraURL;
    QString CejasURL;
    QString OjosURL;
    QString BocaURL;
    QString NarizURL;
    QString BarbaURL;
};

#endif // NPCCOMUN_H
