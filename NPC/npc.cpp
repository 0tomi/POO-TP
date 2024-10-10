#include "npc.h"
#include <QDebug>

NPC::NPC(char Gen, int Type, bool newValidez){
    this->Genero = Gen;
    this->Tipo = Type;
    this->Validez = newValidez;

    if (newValidez)
        this->datosFalsos = nullptr;
    else this->datosFalsos = new QString;

    if (this->Tipo == 3){
        this->datosFalsos = new QString;
        *datosFalsos = "No pueden pasar revolucionarios.\n";
    }

    if (Type != 3)
        dialogo = "";

    for (int i = 0; i < MAX_Documentos; i++)
        documentos[i] = nullptr;
}

char NPC::getGenero(){
    return this->Genero;
}

Documentacion** NPC::getDocumentos(){
    return documentos;
}

Documentacion * NPC::getDocumento(Documento Tipo)
{
    Documentacion * doc2return;
    switch (Tipo) {
    case pasaporte: doc2return = documentos[0];
        break;
    case estancia: doc2return = documentos[1];
        break;
    case paisDeResidencia: doc2return = documentos[2];
        break;
    case listaAcompaniantes: doc2return = documentos[3];
        break;
    case nuevaEstancia: doc2return = documentos[4];
        break;
    case Radiografia: doc2return = documentos[5];
        break;
    default: doc2return = nullptr;
    }
    return doc2return;
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
    2: Pais de residencia
    3: Lista de acompaniantes
    4: NuevaEstancia
    5: Radiografia
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
    for (int i = 0; i < MAX_Documentos; i++)
        delete documentos[i];
    if (datosFalsos)
        delete datosFalsos;
}
