#include "npc.h"
#include <QDebug>

NPC::NPC(char Gen, int Type, bool newValidez){
    this->Genero = Gen;
    this->Tipo = Type;
    this->Validez = newValidez;

    if (newValidez)
        this->datosFalsos = nullptr;
    else this->datosFalsos = new QString;

    if (Type != 3)
        dialogo = "";

    for (int i = 0; i < 10; i++)
        documentos[i] = nullptr;
}

char NPC::getGenero(){
    return this->Genero;
}

Documentacion** NPC::getDocumentos(){
    return documentos;
}

int NPC::getTipo()
{
    return Tipo;
}

bool NPC::getValidez() const
{
    return Validez;
}

void NPC::addDocumento(Documentacion *newDoc, int Index)
{
  /*
    Codigos internos de documentacion: (El pase diplomatico no esta incluido, todavia)
    0: Pasaporte / Dni
    1: Estancia
    2: Pais de residencia   [EN DESARROLLO]
    3: Lista de acompaniantes
    4: <a desarrollar>
    5: <a desarrollar>
    6: <a desarrollar>
    7: <a desarrollar>
    8: <a desarrollar>
  */

    documentos[Index] = newDoc;
}

QString NPC::getDialogo() const
{
    return dialogo;
}

void NPC::setDialogo(const QString newDialogo)
{
    dialogo += newDialogo;
}

Estancia *NPC::getEstancia()
{
    return dynamic_cast<Estancia*>(documentos[1]);
}

ListaAcompaniantes * NPC::getListaAcompaniantes()
{
    return dynamic_cast<ListaAcompaniantes*>(documentos[3]);
}

Pasaporte *NPC::getPasaporte()
{
    return dynamic_cast<Pasaporte*>(documentos[0]);
}

QString NPC::getDatosFalsos()
{
    if (!datosFalsos)
        return "Documentacion valida";

    auto datos = *datosFalsos;
    return datos;
}

void NPC::setDatosFalsos(QString newDatosFalsos)
{
    if (!datosFalsos)
        return;
    // Si tiene datos falsos los colocamos aqui
    *datosFalsos += newDatosFalsos;
}

NPC::~NPC()
{
    for (int i = 0; i < 10; i++)
        delete documentos[i];
    if (datosFalsos)
        delete datosFalsos;
}
