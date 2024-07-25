#ifndef DOCSICONUI_H
#define DOCSICONUI_H

#include <QStackedWidget>
#include <QMouseEvent>
#include <QCursor>
#include <QPropertyAnimation>

namespace Ui {
class DocsIconUI;
}

class DocsIconUI : public QStackedWidget
{
    Q_OBJECT

public:
    explicit DocsIconUI(QWidget *parent = nullptr);
    ~DocsIconUI();

    virtual void Entrar();
    virtual void Sacar();

    bool getLibroAbierto() const;
    void BloquearDocumento();

signals:
    void Abierto();
    void Cerrado();
    void animacionEntrarTerminada();
    void animacionSalirTerminada();

public slots:
    void emitAbierto();
    void emitCerrado();
    void emitAnimacionEntrarTerminada();
    void emitAnimacionSalirTerminada();

protected:
    // Metodos sobreescritos de QT
    void mousePressEvent(QMouseEvent *event) override;

    bool LibroAbierto;
    QWidget * padre;

    // Animaciones
    QPropertyAnimation *animacionEntrada;
    void PrepararAnimacionEntrada();

    QPropertyAnimation *animacionSalida;
    void PrepararAnimacionSalida();

private:
    Ui::DocsIconUI *ui;
    void CerrarDocumento();
    bool BlockDocumento;
};

#endif // DOCSICONUI_H
