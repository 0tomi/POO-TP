#include "generadorNPC.h" // a futuro para que tengan las cosas de los npcs
#include <string>
using namespace std;

// Capaz que DNI y Estancia tengan que estar en archivos separados, pero no tengo idea
class DNI{

};

class Estancia{

};

class Documentacion{
    private:
    // dni
    // estancia
    public:
      bool valida;
};

class GeneradorDocumentacion{
    private:
        string urlCara;// variable que contendra imagen de la cara del npc (supongo que sera un string con una direccion donde este el png)
        string nombre; // no tengo idea si se usara string 
        char genero; // lo dejo como char pero tampoco tengo idea de q vamos a usar

    public:
        GeneradorDocumentacion(string urlCara, string nombre, char genero); // en ultima instancia se le puede pasar la clase NPC pero no esta definida   
        DNI CrearDNI();
        Estancia CrearEstancia();
};

