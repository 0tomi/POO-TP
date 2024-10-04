#ifndef GUARDARPARTIDA_H
#define GUARDARPARTIDA_H
#include <QMessageBox>
#include "PlayerStats.h"
#include <QString>

using namespace std;
class GuardarPartidas{
private:
    QString SlotsGuardado[3];
    int currentSlot;
    PlayerStats emptySave = {0,0,0,0,0,0};
public:
    GuardarPartidas();
    void save(const PlayerStats &datos, int slot );
    PlayerStats CargarPartida(int slot);
    bool* LeerPartidas();
    void saveCurrentSlot(const PlayerStats&);
    void cleanCurrentSlot();
    void setCurrentSlot(int slot);
};
#endif // GUARDARPARTIDA_H
