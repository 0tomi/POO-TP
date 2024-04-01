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
    for (unsigned int i = 0; i < text.size(); i++)
       text[i] = tolower(text[i]);
}

string retornarDefinicion(string palabra, string direccion){
    ifstream file; file.open(direccion);
    if (file.fail())
        return "No se pudo abrir el archivo con direccion " + direccion;
    string aux, linea;
    convertir_min(palabra);
    palabra += ":";
    file >> aux;
    file.ignore();
    while(getline(file,linea)){
        convertir_min(aux);
        if (aux == palabra)
            return linea;
        file >> aux;
        file.ignore();
    }
    file.close();
    return "Definicion no encontrada";
}

int main(int argc, char const *argv[])
{
    string direccion;
	string palabra;

	cout << "Indique el nombre del archivo con definiciones: ";
	getline(cin,direccion);
	direccion = "./" + direccion + ".txt";
    
	cout << "\nIndique palabra a buscar: ";
    cin >> palabra;
    cout << retornarDefinicion(palabra,direccion);

    return 0;
}
