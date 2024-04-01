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
    string parrafos[999], oraciones[999];
    int cant_parrafos = 0; 
    size_t posicion_inicial = 0;
    archivo.open("C:/Users/Usuario/Desktop/tp_poo/ejer3.txt") ;
    if (archivo.fail()){
        cout << "Error al abrir al archivo";
        return 1;
    }
    while (getline(archivo,parrafos[cant_parrafos]))
    {
        cant_parrafos++;
    }
    archivo.close();


    ofstream archivo_separado;
    archivo_separado.open("C:/Users/Usuario/Desktop/tp_poo/ejer3_oraciones_separadas.txt");
    if (archivo_separado.fail()){
        cout << "Error al abrir al archivo";
        return 1;
    }

    for (int i = 0; i < cant_parrafos; i++)
    {
        size_t posicion_final = parrafos[i].find_first_of(".!?", posicion_inicial);
        while (posicion_final != string::npos)
        {
             archivo_separado << parrafos[i].substr(posicion_inicial, posicion_final - posicion_inicial + 1) << endl;
             posicion_inicial += posicion_final + 1;
             posicion_final = parrafos[i].find_first_of(".!?", posicion_inicial);
        }

    }
    
    
    
    return 0;
}
