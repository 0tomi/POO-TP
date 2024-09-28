#ifndef GENERADORNPC_H
#define GENERADORNPC_H

#include "../NPC/npccomun.h"
#include "generadorskin.h"
#include <QRandomGenerator>
#include <QString>

using namespace std;

class GeneradorNPC{
public:
    void setSeed(quint32 seed);
    GeneradorNPC(QRandomGenerator * generador);
    NPC* getNPCgenerico(int tipo , bool Validez, int nivel);
    void generarDialogos(NPC* npc, int nivel); // A dedesarrollar a futuro

    ~GeneradorNPC();
private:
    // Generador de skins
    GeneradorSkin generadorSkin;

    // Generador de Numeros
    QRandomGenerator* Random;

    int topeLinksCaras;
    int topeLinksRevolucionario;
    int topeLinksRefugiado;
    int topeLinksCejas;
    int topeLinksOjos;
    int topeLinksBocas;
    int topeLinksNariz;
    int topeLinksBarbas;

    // Sistema de dialogos:
    QString* DialogosRevolucionario;
    QString * DialogosRefugiado;
    QString * DialogosEstancia[3];
    QString * dialogosAcomps;

    int topeDialogosRev;
    int topeDialogosRef;
    int topeDialogosEstudiante;
    int topeDialogosTrabajador;
    int topeDialogosTurista;
    int topeDialogosAcomp;

    void GenerarDialogosNivel1(NPC* info);
    void GenerarDialogosNivel2(NPC* info);
    void GenerarDialogosNivel3(NPC* info);
    void GenerarDialogosNivel4(NPC* info);
    void GenerarDialogosNivel5(NPC* info);

    void SortearDialogo(NPC* info, QString * dialogos, int &tope);
    QString generarDialogosAcomps(int CantidadAcompaniantes);

    char generos[3] = {'M', 'H', 'X'};

    // Generar imagen falsa
    void GenerarImagenDocumentosFalsa(NPCcomun * NPCaCrear, int nivel);
};

#endif // GENERADORNPC_H
