#include <string>
using namespace std;

class reglas{
    public:
    // constructores:
        reglas(string* paises, int maxPaises);
    // metodos:
        void resetReglas();

        // Getters
        string* getPaisesPermitidos();
        string* getEstadoCivilPermitido();
        string* getTipoVisitaPermitida();
        int getFechaMinPermitida();
        int getFechaMaxPermitida();
        int getDuracionEstanciaPermitida();

    private:
        // Paises
        string* paises;
        int maxPaises;

        // Atributos
        int fechaMin, fechaMax; // va a ser solo el anio
        int duracionDeEstancia;
        string* tipoDeVisita;
        string* nacionalidad;
        string* EstadoCivil;

        int maxVisitas;
        int maxNacionalidad;
        int maxEstadosCivil;

        // Metodos Privados
        void setFechas();
        void setDuracionEstancia();
        void setTipoDeVisita();
        void setPaisesPermitidos();
        void setEstadoCivil();
};