#include <iostream>
#include <fstream>

using namespace std;
/*
	3) Escriba un programa que modifique un archivo de texto de forma que cada oracion
    comience en una nueva linea.

    CC01: La consigna no aclara el nombre del archivo ni su directorio, 
          asi que se lo pedimos al usuario.
    CC02: Asumo que vendra un archivo con puntos que indiquen el fin de una oracion, y el objetivo
          del programa sera hacer que comiencen en una nueva linea.
*/

int main(int argc, char const *argv[])
{
    string text = "", aux;
    string direccion;
	
	cout << "Indique el nombre del archivo: ";
	getline(cin,direccion);
	direccion = "./" + direccion + ".txt";
	
    ifstream filei; filei.open(direccion);
    if (filei.fail())
		return 404;
	else {			// esto va en el else así en caso de no estar, no se crea un archivo.
		getline(filei,aux,'.');
		while (!filei.eof()){
			text += aux + ".\n";
			getline(filei,aux,'.');
		}
		
		ofstream file; file.open(direccion);   
			file << text;
		file.close();
	}
	
	filei.close();
    return 0;
}
