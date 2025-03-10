#ifndef GENERADORSKIN_H
#define GENERADORSKIN_H
#include <QString>
#include <QRandomGenerator>
#include "../NPC/skin.h"
#include <vector>
using namespace std;

class GeneradorSkin
{
public:
    void setSeed(quint32 seed);
    GeneradorSkin(QRandomGenerator * generador);
    ~GeneradorSkin();
    void Inicializar(int Nivel, int Dificultad);
    Skin getSkin(int TipoNPC, char Genero);
    Skin getSimilarSkin(Skin skinActual, char Genero, int nivel);
private:
    QRandomGenerator * qrand;
    QRandomGenerator randomCuerpos;
    QString pickSkinConGenero(vector <QString> listaSkins[], char Genero);
    QString pickSkin(vector <QString> &listaSkins);
    QString pickCuerpo(vector <QString> &listaSkins, int max);
    QString pickCuerpo(vector <QString> &listaSkins);

    vector <QString> LinksPelo[2];
    vector <QString> LinksCaras;     // Hombre y Mujer
    vector <QString> LinksCarasRevolucionario;
    vector <QString> LinksCarasRefugiado; // Hombre y Mujer
    vector <QString> LinksCejas;
    vector <QString> LinksOjos;
    vector <QString> LinksBocas;
    vector <QString> LinksNariz;
    vector <QString> LinksBarbas;
    vector <QString> LinksGorro;

    void LeerImagenes(vector <QString> &Links, QString RutaGenerica);
    int dificultad, nivel;
};

#endif // GENERADORSKIN_H
