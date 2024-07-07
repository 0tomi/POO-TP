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
    void Entrar(int X, int Y);
    void Sacar(int X);
    void Centrar(int X, int Y);
    ~DocumentosUI();

signals:
    void animacionEntrarTerminada();

protected:
    // Centrar documento
    QPropertyAnimation *animacionCentrar;

    // Animaciones
    QPropertyAnimation *animacionEntrada;
    void PrepararAnimacionEntrada(int X, int Y);

    QPropertyAnimation *animacionSalida;
    void PrepararAnimacionSalida(int X);

    // Mover en caso de hacer click
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    QPoint m_dragStartPosition;

private:
    Ui::DocumentosUI *ui;
};

#endif // DOCUMENTOSUI_H
