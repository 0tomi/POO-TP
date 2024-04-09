/*2) Escriba un programa que cuente cuántas veces está un carácter ingresado por el usuario
en cada línea de un archivo de texto.*/

#include <iostream>
#include <fstream>
#include <string>


using namespace std;
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
    archivo.open("C:/Users/Usuario/Desktop/tp_poo/ejer2.txt");
    if(archivo.fail()){
        cout << "Error";
        return 1;
    }
    string* lineas = new string[1];
    int cont  = 0;
    while (getline(archivo,lineas[cont]))
    {
        cont++;
        lineas = incrementar_tamanio(lineas,cont);
    }
    int* cant_encuentros = new int[cont];
    
    
    char caracter_busqueda;

    cout << "Ingrese el caracter que desea buscar ";
    cin >> caracter_busqueda;
    for (int i = 0; i < cont; i++)
    {
        cant_encuentros[i] = 0;
        for (char c : lineas[i])
        {
            if (caracter_busqueda == c)
            {
                cant_encuentros[i]++;
            }
        }
        cout << "La cantidad de encuentros del caracter \"" << caracter_busqueda << "\" en la linea " << i + 1 << " fue de " << cant_encuentros[i] << endl;
    }
    delete[]lineas;
    delete[]cant_encuentros;
    
    return 0;
}

