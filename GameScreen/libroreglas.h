#ifndef LIBROREGLAS_H
#define LIBROREGLAS_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "../Documentos/documentosui.h"
#include "../AtributosComunes/atributoscomunes.h"
#include "../Reglas/reglas.h"
#include "../Reglas/reglasnivel1.h"
namespace Ui {
class LibroReglas;
}

class LibroReglas : public DocumentosUI
{
    Q_OBJECT

public:
    explicit LibroReglas(QWidget *parent = nullptr);
    ~LibroReglas();

private:
    Ui::LibroReglas *ui;
    AtributosComunes * atributos;
    ReglasNivel1 * rules;

    void setBotones();
    void mostrarPaginaAnterior();
    void mostrarPaginaSiguiente();
    void MoverIndice(int index);
    void setUpPagina1();
private slots:
    void IrAPagina1();

};

#endif // LIBROREGLAS_H
