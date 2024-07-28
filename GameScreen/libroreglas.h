#ifndef LIBROREGLAS_H
#define LIBROREGLAS_H

#include <QWidget>
#include "../juego.h"
#include "../Documentos/documentosui.h"
#include <QString>

namespace Ui {
class libroreglas;
}

class libroreglas : public DocumentosUI
{
    Q_OBJECT

public:
    explicit libroreglas(Juego * datos, QWidget *parent = nullptr);
    ~libroreglas();
    void setUpLevel(int level);

private:
    Ui::libroreglas *ui;
    Reglas * reglas[5];

    void setDocumentacionInfo(Documentacion *documento) override;
    void setBotones();
    void IrPagAnterior();
    void IrPagSiguiente();
    void setDatosPag1();

    int CantidadPaginas;
    int PaginaActual;

    //para setear los campos
    void setPaises(ReglasNivel1 * datos);
    void setFechas(ReglasNivel1 * datos);
    void setEstadoCivil(ReglasNivel1 * datos);
    void setDuracionEstancia(ReglasNivel1 * datos);
    void setTipoDeVisita(ReglasNivel1 * datos);
};

#endif // LIBROREGLAS_H
