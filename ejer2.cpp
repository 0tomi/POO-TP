/*2) Escriba un programa que cuente cuántas veces está un carácter ingresado por el usuario
en cada línea de un archivo de texto.*/

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int main(int argc, char const *argv[])
{
    ifstream archivo;
    string lineas[999];
    int cant_lineas = 0, i = 0, cant_caracteres[999] = {0}; // cant_caracteres guarda cuantas veces aparece el caracter
    char caracter;

    archivo.open("C:/Users/Usuario/Desktop/tp_poo/ejer2.txt");
    if (archivo.fail())
    {
        cout << "Error al abrir el archivo";
        return 1;
    }

     while (getline(archivo,lineas[i])){
         i++;
         cant_lineas++;
     }
    
    cout << "Ingrese el caracter que desea buscar ";
    cin >> caracter;
    
    
     for (int j = 0; j < cant_lineas; j++)
     {
         for (size_t k = 0; k < lineas[j].length(); k++)
         {
             if(caracter == lineas[j].at(k)){
                 cant_caracteres[j]++;
             }
         }
         cout << "La cantidad de ocurrencias del caracter " << caracter << " en la linea " << j + 1 << " fue de " << cant_caracteres[j] <<  endl;
     }

    archivo.close();

    
    
    return 0;
}

