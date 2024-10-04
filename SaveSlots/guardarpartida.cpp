#include "guardarpartida.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

GuardarPartidas::GuardarPartidas() {
    SlotsGuardado[0] = ":/SaveSlots/slot1.dat";
    SlotsGuardado[1] = ":/SaveSlots/slot2.dat";
    SlotsGuardado[2] = ":/SaveSlots/slot3.dat";
}

void GuardarPartidas::save(const PlayerStats &datos, int slot){
    QFile file(SlotsGuardado[slot]);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(nullptr, "Error", "No se pudo abrir el archivo para escribir: " + SlotsGuardado[slot]);
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_0);    // Version mas nueva locura

    // Escribimos los datos del struct en el archivo
    out << datos.Nivel << datos.Dificultad << datos.TotalSocialCredits
        << datos.Multas << datos.CantidadNPCsRechazados << datos.CantidadNPCsAceptados;

    file.close();
}

PlayerStats GuardarPartidas::CargarPartida(int slot){
    QFile file(SlotsGuardado[slot]);
    PlayerStats stats;

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "Error", "No se pudo abrir el archivo para leer partida:" + SlotsGuardado[slot]);
        return emptySave;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_0); // Versión moderna locura

    // Verificar si esta bien escrito el struct, sino lo sobreescribe
    if (file.size() != sizeof(PlayerStats)) {
        qWarning() << "La estructura no coincide con el tamaño esperado. Reiniciando los valores a 0.";
        file.close();

        save(emptySave, slot);
        return emptySave;
    }

    // Leer los datos del archivo
    in >> stats.Nivel >> stats.Dificultad >> stats.TotalSocialCredits
        >> stats.Multas >> stats.CantidadNPCsRechazados >> stats.CantidadNPCsAceptados;

    file.close();
    return stats;
}

bool* GuardarPartidas::LeerPartidas(){
    bool* slots_disponibles=new bool[3];
    for(int i=0; i<3; i++){
        if(CargarPartida(i).Nivel==0)
            slots_disponibles[i]=false;
        else slots_disponibles[i]=true;
    }
    return slots_disponibles;
}

void GuardarPartidas::saveCurrentSlot(const PlayerStats &data)
{
    save(data, currentSlot);
}

void GuardarPartidas::cleanCurrentSlot()
{
    saveCurrentSlot(emptySave);
}

void GuardarPartidas::setCurrentSlot(int slot)
{
    currentSlot = slot;
}
