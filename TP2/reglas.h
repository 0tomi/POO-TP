#include <string>
using namespace std;

class reglas{
    public:
    // constructores:
        reglas(string* paises, int maxPaises, string* tipoVisitas, int maxVisita, string* EstadosCiviles, int maxEC);
        reglas(string* paises, int maxPaises, string* tipoVisitas, int maxVisita, int cantidadMinimaPaisesPermitidos);
    // metodos:
        void resetReglas(int cantidadMinimaPaisesPermitidos);

        // Getters
        int* getPaisesPermitidos(int &max);
        string* getEstadoCivilPermitido(int &max);
        string* getTipoVisitaPermitida(int &max);
        int getFechaMinPermitida();
        int getFechaMaxPermitida();
        int getDuracionEstanciaPermitida();

    private:
        // # Conjunto de elementos de los cuales obtendremos las reglas #
        string* paises;
        int maxPaises;
        
        string* tipoVisitas;
        int maxTiposVisitas;

        string* estadosCiviles;
        int maxEstadosCiviles;

        // # Conjunto de reglas #
        int fechaMin, fechaMax; // va a ser solo el anio
        int duracionDeEstanciaValida;
        int* paisesValidos;
        string* tipoDeVisitaValida;
        string* EstadoCivilValidos;

        // Tope de arrays:
        int maxPaisesPermitidos;
        int maxEstadosCivilPermitidos;
        int maxVisitasPermitidas;

        // # Metodos para setear reglas validas #
        void setFechasValidas();
        void setDuracionEstanciaValida(int max, int min);

        void setEstadoCivilValidos();
        void SeleccionarEstadosCivilesValidos(int CantidadEstadosValidos);

        void setTipoDeVisitaValidas();
        void SeleccionarVisitasValidas(int CantidadVisitasValidas);

        void setPaisesPermitidos(int cantidadMinimaPaisesPermitidos);
        bool checkRepetidos(int dato);
};