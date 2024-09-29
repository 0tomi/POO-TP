#ifndef GUARDARPARTIDA_H
#define GUARDARPARTIDA_H
#include <QMessageBox>
#include "PlayerStats.h"
#include <fstream>
#include <string>
using namespace std;
class GuardarPartidas{
private:
    string SlotsGuardado[3];
public:
    GuardarPartidas();
    void GuardarPartida(PlayerStats datos, int slot );
    PlayerStats CargarPartida(int slot);
    bool* LeerPartidas();
};
#endif // GUARDARPARTIDA_H
