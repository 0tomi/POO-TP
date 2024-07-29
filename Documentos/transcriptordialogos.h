#ifndef TRANSCRIPTORDIALOGOS_H
#define TRANSCRIPTORDIALOGOS_H

#include <QWidget>
#include "documentosui.h"

namespace Ui {
class TranscriptorDialogos;
}

class TranscriptorDialogos : public DocumentosUI
{
    Q_OBJECT

public:
    explicit TranscriptorDialogos(QWidget *parent = nullptr);
    ~TranscriptorDialogos();
    void setDocumentacionInfo(Documentacion *documento) override;
    virtual void Entrar()override;
    virtual void Sacar()override;
public slots:
    void CaptarMensaje(QString dialogo);
    void LimpiarDialogo();
private:
    Ui::TranscriptorDialogos *ui;
    QString DialogoRecibido;
};

#endif // TRANSCRIPTORDIALOGOS_H
