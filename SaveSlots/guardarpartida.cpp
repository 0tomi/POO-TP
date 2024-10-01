#include "guardarpartida.h"

GuardarPartidas::GuardarPartidas() {
    SlotsGuardado[0]=":/Resources/Partidas/slot1.dat";
    SlotsGuardado[1]=":/Resources/Partidas/slot2.dat";
    SlotsGuardado[2]=":/Resources/Partidas/slot3.dat";
}


void GuardarPartidas::GuardarPartida(PlayerStats &datos, int slot){
    ofstream archivoPartida(SlotsGuardado[slot], ios::out | ios::binary );
    if(archivoPartida.fail()){
        QMessageBox::critical(nullptr, "Error", "no se pudo guardar partida");
        return;

    }
    archivoPartida.write((char*)& datos, sizeof(datos));
    archivoPartida.close();

}

PlayerStats GuardarPartidas::CargarPartida(int slot){
    PlayerStats datos;
    ifstream archivoPartida(SlotsGuardado[slot], ios::binary | ios::in );
    if(archivoPartida.fail()){
        QMessageBox::critical(nullptr, "Error", "no se pudo cargar partida");
        return datos;
    }
    archivoPartida.read((char*)& datos, sizeof(datos));
    archivoPartida.close();
    return datos;
}
bool* GuardarPartidas::LeerPartidas(){
    bool* slots_disponibles=new bool[3];
    for(int i=0; i<3; i++){
        if(CargarPartida(i).Nivel==0){
            slots_disponibles[i]=true;
        }
        else slots_disponibles[i]=false;
    }
    return slots_disponibles;
}
