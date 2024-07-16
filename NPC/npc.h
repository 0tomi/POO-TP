#ifndef NPC_H
#define NPC_H

#include "../Documentos/documentacion.h"
#include <QString>

class NPC
{
public:
    explicit NPC(char Genero, int Tipo, bool Validez);
    virtual ~NPC();

    virtual char getGenero();
    virtual Documentacion** getDocumentos();
    virtual int getTipo();
    virtual bool getValidez() const;

    virtual void addDocumento(Documentacion *newDoc, int Index);

    QString getDialogo() const;
    void setDialogo(const QString newDialogo);

protected:
    bool Validez;
    char Genero;
    int Tipo;
    Documentacion* documentos[10];
    QString dialogo;
};

#endif // NPC_H
