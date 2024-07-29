#ifndef GENERADORNPC_H
#define GENERADORNPC_H

#include "../NPC/npccomun.h"
#include <string>
#include <QRandomGenerator>
#include <QString>

using namespace std;

class GeneradorNPC{
public:
    GeneradorNPC();
    NPC* getNPCgenerico(int tipo , bool Validez);
    NPC *getSimilarNPC(NPC* ejemplo); // A desarrollar a futuro
    void generarDialogos(NPC* npc, int nivel); // A dedesarrollar a futuro

    ~GeneradorNPC();
private:
    // Generador de Numeros
    QRandomGenerator* Random;

    // NPC que se va a generar
    NPC* NPC2create;

    // Metodos par armar las selecciones random
    QString getCaraRandom(char Genero);
    QString getCaraRevolucionarioRandom();
    QString getCaraRefugiadoRandom(char Genero);
    QString getCejasRandom();
    QString getOjosRandom();
    QString getBocaRandom();
    QString getNarizRandom();
    QString getBarbaRandom();

    // ArrayS con direcciones donde se encuentran las caras de los npcs
    QString* LinksCarasHombre;
    QString* LinksCarasMujer;
    int topeLinksCaras;

    QString* LinksCarasRevolucionario;
    int topeLinksRevolucionario;

    QString* LinksCarasRefugiadoHombre;
    QString* LinksCarasRefugiadoMujer;
    int topeLinksRefugiado;


    QString* LinksCejas;
    int topeLinksCejas;

    QString* LinksOjos;
    int topeLinksOjos;

    QString* LinksBocas;
    int topeLinksBocas;

    QString* LinksNariz;
    int topeLinksNariz;

    QString* LinksBarbas;
    int topeLinksBarbas;

    // Sistema de dialogos:
    QString* DialogosRevolucionario;
    int topeDialogosRev;
    QString * DialogosRefugiado;
    int topeDialogosRef;

    QString* DialogosEstudiante;
    int topeDialogosEstudiante;

    QString* DialogosTrabajador;
    int topeDialogosTrabajador;

    QString* DialogosTurista;
    int topeDialogosTurista;

    void GenerarDialogosNivel1(NPC* info);
    void GenerarDialogosNivel2(NPC* info);
    void GenerarDialogosNivel3(NPC* info);
    void GenerarDialogosNivel4(NPC* info);
    void GenerarDialogosNivel5(NPC* info);

    void SortearDialogo(NPC* info, QString * dialogos, int &tope);
    QString *obtenerTipoEstancia(int tipo, int &tope);

    char generos[3] = {'M', 'H', 'X'};
};

#endif // GENERADORNPC_H
