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
    void setDocumentacion();
    virtual void Entrar()override;
public slots:
    void CaptarMensaje(QString dialogo);
private:
    Ui::TranscriptorDialogos *ui;
    QString DialogoRecibido;
};

#endif // TRANSCRIPTORDIALOGOS_H
