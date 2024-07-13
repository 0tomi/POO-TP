#ifndef DNI_H
#define DNI_H
#include "../Documentos/documentosui.h"
#include "../Documentos/pasaporte.h"
#include "../NPC/npcui.h"
#include <QWidget>

namespace Ui {
class DNI;
}

class DNI : public DocumentosUI
{
    Q_OBJECT

public:
    explicit DNI(QWidget *parent = nullptr);
    ~DNI();
    void setDNIInfo(Pasaporte * dni, NPC * npc);
    void setDocumentacionInfo(Documentacion *documento) override;
private:
    Ui::DNI *ui;
    NPCUI* NPCenDocumento;
};

#endif // DNI_H
