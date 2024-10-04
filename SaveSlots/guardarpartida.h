#ifndef GUARDARPARTIDA_H
#define GUARDARPARTIDA_H
#include <QObject>
#include "PlayerStats.h"
#include <QString>
#include <QCoreApplication>
#include <QDir>

using namespace std;
class GuardarPartidas: public QObject{
    Q_OBJECT

public:
    GuardarPartidas();
    void save(const PlayerStats &datos, int slot );
    PlayerStats CargarPartida(int slot);
    bool* LeerPartidas();
    void saveCurrentSlot(const PlayerStats&);
    void cleanCurrentSlot();
    void setCurrentSlot(int slot);

signals:
    void Log(QString);

private:
    const QString BuildPath = QCoreApplication::applicationDirPath();
    const QString DireccionCarpeta = BuildPath + "/SavedGames";
    QString SlotsGuardado[3];
    int currentSlot;
    PlayerStats emptySave = {0,0,0,0,0,0};
};
#endif // GUARDARPARTIDA_H
