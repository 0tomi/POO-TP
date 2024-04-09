/*3) Escriba un programa que modifique un archivo de texto de forma que cada oración
comience en una nueva línea.
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream archivo;
    archivo.open("C:/Users/Usuario/Desktop/tp_poo/ejer3.txt");
    if (archivo.fail())
    {
        cout << "Error";
        return 1;
    }
    
    ofstream nuevo_archivo;
    nuevo_archivo.open("C:/Users/Usuario/Desktop/tp_poo/ejer3_oraciones_separadas.txt");
    if (nuevo_archivo.fail())
    {
        cout << "Error";
        return 1;
    }
    string lineas ;
    while (getline(archivo,lineas))
    {
        size_t pos;
        size_t inicio = 0;
        while ((pos = lineas.find_first_of(".?!",inicio)) != string::npos)
        {
            string oracion = lineas.substr(inicio, pos - inicio + 1);
            nuevo_archivo << oracion << endl;
            inicio = pos + 1;
        }
        if (inicio < lineas.size()) // Escribir la ultima parte de la linea si no termina con .?!
        {
            nuevo_archivo << lineas.substr(inicio) << endl;
        }
        
    }
    archivo.close();
    nuevo_archivo.close();
    
    return 0;
}
