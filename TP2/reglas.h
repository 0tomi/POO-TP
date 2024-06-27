#include <string>
using namespace std;

class reglasNivel1{
    public:
    // constructores:
        reglasNivel1();
    // metodos:
        void resetReglas();

    private:
        int fecha; // va a ser solo el anio
        int duracionDeEstancia;
        string* tipoDeVisita;
        string* nacionalidad;
        string* EstadoCivil;

        int maxVisitas;
        int maxNacionalidad;
        int maxEstadosCivil;
};