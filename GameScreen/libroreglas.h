#ifndef LIBROREGLAS_H
#define LIBROREGLAS_H

#include <QWidget>
#include "../Reglas/reglasnivel1.h"
#include "../AtributosComunes/atributoscomunes.h"
#include "../Documentos/documentosui.h"
#include "../lectorarchivos.h"
#include <QString>

namespace Ui {
class libroreglas;
}

class libroreglas : public QWidget
{
    Q_OBJECT

public:
    explicit libroreglas(QWidget *parent = nullptr);
    ~libroreglas();

private:
    Ui::libroreglas *ui;
    ReglasNivel1 * ruleslvl1;
    AtributosComunes * atributos;
    LectorArchivos * archi;
    //void setDocumentacionInfo(Documentacion *documento) override;
    void setBotones();
    void IrPagAnterior();
    void IrPagSiguiente();
    void setDatosPag1();

    //para setear los campos
    void setPaises();
    void setFechas();
    void setEstadoCivil();
    void setDuracionEstancia();
    void setTipoDeVisita();
};

#endif // LIBROREGLAS_H
