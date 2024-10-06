#ifndef NUEVAESTANCIAUI_H
#define NUEVAESTANCIAUI_H

#include <QWidget>
#include <QLabel>
#include <QSoundEffect>
#include "documentosui.h"
#include "nuevaestancia.h"

namespace Ui {
class NuevaEstanciaUI;
}

class NuevaEstanciaUI : public DocumentosUI
{
    Q_OBJECT

public:
    explicit NuevaEstanciaUI(QWidget *parent = nullptr);
    virtual void setDocumentacionInfo(Documentacion *documento) override;
    virtual void Entrar() override;
    void setVolume(float vol);
    ~NuevaEstanciaUI();

private:
    QSoundEffect Sonidos[3]; // 0: Abierto, 1: Cerrado, // 2: Pasar pagina
    void setUpPaginaEstancia(Estancia* info);
    void pasarPagina(int pag);
    void setUpBotones();
    void resetearApariencia();
    void setUpPagina(const vector<QString>& Datos, QLabel* &LabelSetUp);
    Ui::NuevaEstanciaUI *ui;
};

#endif // NUEVAESTANCIAUI_H
