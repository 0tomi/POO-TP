#include "guardarpartida.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

GuardarPartidas::GuardarPartidas() {
    QDir directorio;
    if (directorio.mkpath(this->DireccionCarpeta)){
        qDebug() << "Carpeta con saves creada";
        SlotsGuardado[0] = DireccionCarpeta + "/slot1.dat";
        SlotsGuardado[1] = DireccionCarpeta + "/slot2.dat";
        SlotsGuardado[2] = DireccionCarpeta + "/slot3.dat";
        qDebug() << SlotsGuardado[0];
    } else{
        qDebug() << "Carpeta con saves no creada";
    }
}

void GuardarPartidas::save(PlayerStats &datos, int slot){
    emit Log("Guardando datos en: " + SlotsGuardado[slot]);
    if (slot < 0 || slot > 2)
        slot = 0;

    QFile file(SlotsGuardado[slot]);
    if (!file.open(QIODevice::WriteOnly)) {
        emit Log("Error: No se pudo abrir el archivo para escritura: " + SlotsGuardado[slot]);
        return;
    }

    file.write(reinterpret_cast<char*> (&datos), sizeof(PlayerStats));
    file.close();
    emit Log("Datos guardados exitosamente.");
}

PlayerStats GuardarPartidas::CargarPartida(int slot){
    QFile file(SlotsGuardado[slot]);
    PlayerStats stats;

    if (!file.open(QIODevice::ReadOnly)) {
        emit Log("Error: No se pudo abrir el siguiente archivo para su lectura: " + SlotsGuardado[slot]);
        return emptySave;
    }

    // Verificar si esta bien escrito el struct, sino lo sobreescribe
    auto TamanioStats = sizeof(PlayerStats);
    if (file.size() != TamanioStats) {
        emit Log("La estructura del archvio de guardado: " + SlotsGuardado[slot] + " no coincide con el tamaño esperado. Reiniciando los valores a 0.");
        file.close();

        return emptySave;
    }

    // Leer los datos del archivo
    file.read(reinterpret_cast<char*> (&stats), TamanioStats);
    file.close();

    return stats;
}

vector<bool> GuardarPartidas::LeerPartidas(){
    vector<bool> slots_disponibles;
    slots_disponibles.resize(3);
    for(int i=0; i<3; i++){
        if(CargarPartida(i).Nivel==0)
            slots_disponibles[i]=false;
        else slots_disponibles[i]=true;
    }
    return slots_disponibles;
}

void GuardarPartidas::saveCurrentSlot(PlayerStats &data)
{
    save(data, this->currentSlot);
}

void GuardarPartidas::cleanCurrentSlot()
{
    saveCurrentSlot(emptySave);
}

void GuardarPartidas::setCurrentSlot(int slot)
{
    currentSlot = slot;
}
