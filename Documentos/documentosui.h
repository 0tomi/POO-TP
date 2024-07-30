#ifndef DOCUMENTOSUI_H
#define DOCUMENTOSUI_H

#include "documentacion.h"
#include <QWidget>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QResizeEvent>

namespace Ui {
class DocumentosUI;
}

class DocumentosUI : public QWidget
{
    Q_OBJECT

public:
    explicit DocumentosUI(QWidget *parent = nullptr);
    virtual void setDocumentacionInfo(Documentacion *documento) = 0;
    virtual void Entrar();
    virtual void Sacar();
    virtual void Centrar();
    virtual void PausarAnimacionCentrar();
    ~DocumentosUI();

signals:
    void animacionEntrarTerminada();
    void animacionSalirTerminada();

protected:
    // Centrar documento
    QPropertyAnimation *animacionCentrar;

    // Animaciones
    QPropertyAnimation *animacionEntrada;
    virtual void PrepararAnimacionEntrada();

    QPropertyAnimation *animacionSalida;
    virtual void PrepararAnimacionSalida();

    // Mover en caso de hacer click
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    QPoint m_dragStartPosition;

    QWidget * padre;
private:
    Ui::DocumentosUI *ui;
};

#endif // DOCUMENTOSUI_H
