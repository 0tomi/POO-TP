#ifndef NPC_H
#define NPC_H

#include "../Documentos/documentacion.h"
#include <QString>

class NPC
{
public:
    enum Documento{
        pasaporte, estancia, paisDeResidencia,  listaAcompaniantes, nuevaEstancia, Radiografia
    };
    explicit NPC(char Genero, int Tipo, bool Validez);
    virtual ~NPC();

    virtual char getGenero();
    virtual Documentacion** getDocumentos();
    virtual Documentacion * getDocumento(Documento Tipo);
    virtual int getTipo();
    virtual bool getValidez() const;

    virtual void addDocumento(Documentacion *newDoc, int Index);

    QString getDialogo() const;
    void setDialogo(const QString newDialogo);

    void updateDatosFalsos();
    QString getDatosFalsos();
    void setDatosFalsos(QString newDatosFalsos);

protected:
    bool Validez;
    char Genero;
    int Tipo;
    const int MAX_Documentos = 6;
    Documentacion* documentos[6];
    QString dialogo;
    QString * datosFalsos;
};

#endif // NPC_H
