#ifndef LIBROREGLAS_H
#define LIBROREGLAS_H

#include <QWidget>
#include "../juego.h"
#include "../Documentos/documentosui.h"
#include <QString>
#include <QSoundEffect>
#include <QLabel>
#include "../lectorarchivos.h"

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
    void Entrar() override;
    void Sacar() override;
    void setVolume(float);

private:
    QSoundEffect moverLibro;
    QSoundEffect pasarPagina;
    Ui::libroreglas *ui;
    Juego* juego;
    // Datos de niveles:
    void setDatosPag1();
    void setDatosNivel2();
    void setDatosNivel3();
    void setDatosNivel4();
    void setDatosNivel5();
    void setDatos(const vector<QString>& lineas, QLabel* lugarDondeSeColocaElTexto);

    void setDocumentacionInfo(Documentacion *documento) override;
    void setBotones();
    void PasarPagina(int pag);
    void SaltarPagina(int pagina);

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
