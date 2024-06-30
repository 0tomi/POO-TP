#ifndef NPC_H
#define NPC_H
#include "../Documentos/Documentacion.h"
class NPC{
public:
    NPC(string CaraURL, char Genero);
    void setDocumentacion(Documentacion* docs);
    
    string getCara();
    char getGenero();
    Documentacion* getDocumentos();
private:
    string CaraURL;
    char Genero;
    Documentacion* documentos;
};
#endif // NPC_H
