#include <string>
using namespace std;

class reglas{
    public:
    // constructores:
        reglas(string* paises, int maxPaises, string* tipoVisitas, int maxVisita);
        reglas(string* paises, int maxPaises, string* tipoVisitas, int maxVisita, int cantidadMinimaPaisesPermitidos);
    // metodos:
        void resetReglas(int cantidadMinimaPaisesPermitidos);

        // Getters
        int* getPaisesPermitidos(int &max);
        string* getEstadoCivilPermitido();
        string* getTipoVisitaPermitida();
        int getFechaMinPermitida();
        int getFechaMaxPermitida();
        int getDuracionEstanciaPermitida();

    private:
        // Paises
        string* paises;
        int maxPaises;

        // Visitas
        string* tipoVisitas;
        int maxTiposVisitas;

        // Atributos
        int fechaMin, fechaMax; // va a ser solo el anio
        int duracionDeEstanciaValida;
        int* paisesValidos;
        string* tipoDeVisitaValida;
        string* EstadoCivilValidos;
        // Tope de arrays:
        int maxPaisesPermitidos;
        int maxEstadosCivilPermitidos;
        int maxVisitasPermitidas;

        // Metodos Privados
        void setFechas();
        void setDuracionEstancia();
        void setTipoDeVisita();
        void setEstadoCivil();

        void setPaisesPermitidos(int cantidadMinimaPaisesPermitidos);
        bool checkRepetidos(int dato);
};