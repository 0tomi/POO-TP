#ifndef PASAPORTEUI_H
#define PASAPORTEUI_H
#include "pasaporte.h"
#include "../NPC/npcui.h"
#include <QWidget>
#include "documentosui.h"
#include "../NPC/npcgenericoui.h"
namespace Ui {
class Pasaporteui;
}

class Pasaporteui : public DocumentosUI
{
    Q_OBJECT

public:
    explicit Pasaporteui(QWidget *parent = nullptr);
    ~Pasaporteui();
    void setDocumentacionInfo(Pasaporte * pasaporte, NPC * npc);
    void setDocumentacionInfo(Documentacion *documento) override;
private:
    Ui::Pasaporteui *ui;
    NPCGenericoUI * aux_npc;
};

#endif // PASAPORTEUI_H
