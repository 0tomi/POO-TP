#ifndef PASAPORTEUI_H
#define PASAPORTEUI_H

#include "pasaporte.h"
#include "../NPC/npcui.h"
#include <QWidget>
#include "documentosui.h"
#include "../NPC/npcgenericoui.h"

namespace Ui {
class PasaporteUI;
}

class PasaporteUI : public DocumentosUI
{
    Q_OBJECT

public:
    explicit PasaporteUI(QWidget *parent = nullptr);
    ~PasaporteUI();
    void setPasaporteInfo(Pasaporte * pasaporte, NPC * npc);
    void setDocumentacionInfo(Documentacion *documento) override;
    void setStandby();
    void setAprobado();
    void setRechazado();
private:
    Ui::PasaporteUI *ui;
    NPCGenericoUI * aux_npc;
};

#endif // PASAPORTEUI_H
