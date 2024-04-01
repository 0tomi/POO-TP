/*6) Dado un archivo de texto, con el formato:
palabra: definición
Realice una función que dada una palabra retorne la definición.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string definicion(string palabras[], string definiciones[], string palabra_a_buscar, int cant_palabras){
    for (int i = 0; i < cant_palabras; i++)
    {
        if(palabras[i] == palabra_a_buscar)
        return definiciones[i];
        
    }
    return "La palabra que intentas buscar no existe";
}
int main(int argc, char const *argv[])
{
    ifstream archivo;
    int i = 0;
    string palabras[100], definiciones[100], palabra_a_buscar;
    archivo.open("C:/Users/Usuario/Desktop/tp_poo/ejer6.txt");
    if(archivo.fail()){
        cout << "Error al abrir el archivo";
        return 1;
    }

    while (getline(archivo,palabras[i],':')){
        getline(archivo, definiciones[i]);
        i++;
    }
    archivo.close();
    cout << "Ingrese la palabra a la que desea saber la definicion ";
    getline(cin, palabra_a_buscar);
    string mostrar_definicion = definicion(palabras,definiciones,palabra_a_buscar,i);

    cout << mostrar_definicion;
    
    return 0;
}
