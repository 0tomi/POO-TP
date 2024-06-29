#include <string>
using namespace std;

class reglas{
    public:
    // constructores:
        reglas();
    // metodos:
        void resetReglas();

    private:
        int fechaMin, fechaMax; // va a ser solo el anio
        int duracionDeEstancia;
        string* tipoDeVisita;
        string* nacionalidad;
        string* EstadoCivil;

        int maxVisitas;
        int maxNacionalidad;
        int maxEstadosCivil;
};