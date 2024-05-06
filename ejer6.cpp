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
string* incrementar_tamanio(string* vec, int cont){
    string* aux = new string[cont + 1];
    for (int i = 0; i < cont; i++)
    {
        aux[i] = vec[i];
    }
    delete[] vec;
    return aux;
}
int main(int argc, char const *argv[])
{
    ifstream archivo;
    string* palabras = new string[1];
    string* definiciones = new string[1];
    string palabra_a_buscar;
    int cont = 0;
    archivo.open("../ejer6.txt");
    if(archivo.fail()){
        cout << "Error al abrir el archivo";
        return 1;
    }
    while (getline(archivo,palabras[cont],':'))
    {
        getline(archivo,definiciones[cont]);
        cont++;
        palabras = incrementar_tamanio(palabras,cont);
        definiciones = incrementar_tamanio(definiciones,cont);
    }
    archivo.close();
    cout << "Ingrese la palabra que desea saber su definicion ";
    getline(cin,palabra_a_buscar);
    string mostrar_def = definicion(palabras,definiciones,palabra_a_buscar,cont);
    cout << mostrar_def;
    delete [] palabras;
    delete [] definiciones;
    return 0;
}
