#ifndef NPCCOMUN_H
#define NPCCOMUN_H
#include "npc.h"

class NPCcomun: public NPC
{
public:
    NPCcomun(char Genero, char Tipo);

    string getCaraURL() const;
    void setCaraURL(const string &newCaraURL);

    string getCejasURL() const;
    void setCejasURL(const string &newCejasURL);

    string getOjosURL() const;
    void setOjosURL(const string &newOjosURL);

    string getBocaURL() const;
    void setBocaURL(const string &newBocaURL);

    string getNarizURL() const;
    void setNarizURL(const string &newNarizURL);

    string getBarbaURL() const;
    void setBarbaURL(const string &newBarbaURL);

private:
    string CaraURL;
    string CejasURL;
    string OjosURL;
    string BocaURL;
    string NarizURL;
    string BarbaURL;
};

#endif // NPCCOMUN_H
