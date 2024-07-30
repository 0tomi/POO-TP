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
    virtual void Entrar() override;
    virtual void Sacar() override;

    bool getMostrando() const;

public slots:
    void CaptarMensaje(QString dialogo);
    void LimpiarDialogo();
    void MostrarOcultar();

protected:
    void PrepararAnimacionEntrada() override;
    void PrepararAnimacionSalida() override;

private:
    Ui::TranscriptorDialogos *ui;
    QString DialogoRecibido;
    bool Mostrando;
};

#endif // TRANSCRIPTORDIALOGOS_H
