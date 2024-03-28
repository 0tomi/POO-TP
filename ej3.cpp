#include <iostream>
#include <fstream>

using namespace std;
/*
	3) Escriba un programa que modifique un archivo de texto de forma que cada oración
    comience en una nueva línea.

    CC01: La consigna no aclara el nombre del archivo ni su directorio, 
          asi que se lo pedimos al usuario.
    CC02: Asumo que vendrá un archivo con puntos que indiquen el fin de una oración, y el objetivo
          del programa será hacer que comiencen en una nueva línea.
*/

int main(int argc, char const *argv[])
{
    string text;
    string direccion;
	cout << "Indique el nombre del archivo: ";
	getline(cin,direccion);
	direccion = "./" + direccion + ".txt";
    ifstream filei; filei.open(direccion);
    
    filei.close();
    ofstream file; file.open(direccion,ios::app);   
   
    file.close();
    return 0;
}
