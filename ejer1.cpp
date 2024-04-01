/*1) Escriba un programa que indique cuántas líneas tiene un archivo de texto.*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream archivo;

    int cant_lineas = 0; // cantidad de lineas del archivo

    string leer_lineas;

    archivo.open("C:/Users/Usuario/Desktop/tp_poo/ejer1.txt");
    if(archivo.fail()){
        cout << "Error al abrir el archivo";
        return 1;
    }

    while (getline(archivo,leer_lineas)){
        cant_lineas++;
    }


    cout << "El archivo tiene " << cant_lineas << " lineas";
    archivo.close();
    return 0;
}


