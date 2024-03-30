#include <iostream>
#include <fstream>
#include <string>


/*
    EJ6:  Dado un archivo de texto, con el formato:
        palabra: definición
    Realice una función que dada una palabra retorne la definición.
*/
using namespace std;

void convertir_min(string &text){
    for (int i = 0; i < text.length; i++)
        tolower(text[i]);
}

bool checkPalabra(string text, string buscar){
    convertir_min(text);
    convertir_min(buscar);
    buscar += ":";
    int busqueda = text.find(buscar);
    if (busqueda != -1)
        return true;
    return false;
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
